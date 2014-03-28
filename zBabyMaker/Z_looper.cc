#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <math.h>
#include <fstream>
#include <stdexcept>
#include <sstream>

#include "TTree.h"
#include "TChain.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "Math/VectorUtil.h"
#include "TProfile.h"
#include "TTreeCache.h"
#include "TDatabasePDG.h"

#include "../CORE/CMS2.h"
#ifndef __CINT__
#include "../CORE/utilities.h"
#include "../CORE/ssSelections.h"
#include "../CORE/electronSelections.h"
#include "../CORE/electronSelectionsParameters.h"
#include "../CORE/MITConversionUtilities.h"
#include "../CORE/muonSelections.h"
#include "../CORE/eventSelections.h"
#include "../CORE/ttbarSelections.h"
#include "../CORE/trackSelections.h"
#include "../CORE/metSelections.h"
#include "../CORE/jetSelections.h"
#include "../CORE/photonSelections.h"
#include "../CORE/triggerUtils.h"
#include "../CORE/triggerSuperModel.h"
#include "../CORE/mcSelections.h"
#include "../CORE/susySelections.h"
#include "../CORE/mcSUSYkfactor.h"
#include "../CORE/SimpleFakeRate.h"
#include "../CORE/MT2/MT2Utility.h"
#include "../CORE/MT2/MT2.h"

#include "../Tools/goodrun.h"
#include "../Tools/vtxreweight.h"
#include "../Tools/bTagEff_BTV.h"

#include "../CORE/jetcorr/FactorizedJetCorrector.h"
#include "../CORE/jetcorr/JetCorrectionUncertainty.h"
#endif

#include "Z_looper.h"
#include "../looperTools/histtools.h"
#include "../susy_xsecs/getZHGMSBCrossSection.cc"

using namespace tas;

enum metType   { e_tcmet = 0, e_tcmetNew = 1, e_pfmet = 2};
enum templateSource { e_QCD = 0, e_PhotonJet = 1 };

//--------------------------------------------------------------------

const bool  generalLeptonVeto    = true;
const bool  vetoTransition       = true;
const bool  debug                = false;
const bool  doGenSelection       = false;
bool  doTenPercent         = false;
bool  useOldIsolation      = false;
const bool  pt2020               = false;
const bool  useJson              = false;
const float lumi                 = 1.0; 

const char* jsonfilename         = "../jsons/Merged_190456-208686_8TeV_PromptReReco_Collisions12_goodruns.txt";

// 19.5 merged json from Dunser
// https://hypernews.cern.ch/HyperNews/CMS/get/susy-multilepton/277/1/2/1/1/1.html

//--------------------------------------------------------------------

Z_looper::Z_looper( string iteration = "" ) 
{
  iter                 = iteration;
  TFile * nsigEvtsHistFile = TFile::Open("../susy_xsecs/myMassDB_TChiZH.root","READ");
  nsigEvtsHist_ = (TH2F*) nsigEvtsHistFile -> Get("masses") -> Clone("nsigEvtsHist");
  nsigEvtsHistFile -> Close();  
};

float dRGenJet ( LorentzVector p4, bool isData, float ptcut = 20.0 ) {

  if( isData ) return -99;

  float mindr = 999.0;

  for( size_t i = 0 ; i < genjets_p4().size() ; i++){

    // require genjet pt > ptcut
    if( genjets_p4().at(i).pt() < ptcut ) continue;

    // dR(jet,genjet)
    float dr = ROOT::Math::VectorUtil::DeltaR( p4 , genjets_p4().at(i) );

    // store minimum dR
    if( dr < mindr ) mindr = dr;
  }

  return mindr;
}


int isGenQGLMatched ( LorentzVector p4, bool isData, float dR = 0.4 ) {

  if( isData ) return -99;

  //Start from the end that seems to have the decay products of the W first
        
  for (int igen = (genps_p4().size()-1); igen >-1; igen--) {

    float deltaR = ROOT::Math::VectorUtil::DeltaR( p4 , genps_p4().at(igen) );
    if ( deltaR > dR ) continue;

    int id     = genps_id().at(igen);
    int mothid = genps_id_mother().at(igen);
    // cout<<"status 3 particle ID "<<id<<" mother "<<mothid                                                                         
    //  <<" dR to jet "<<deltaR<<endl;

    // light quark from W
    if (abs(id)<6 && abs(mothid)==24)
      return (mothid>0) ? 2 : -2;

    // b quark from top
    if (abs(id)==5 && abs(mothid)==6)
      return (mothid>0) ? 1 : -1;

    // lepton: e, mu, or tau
    if (abs(id)==11 && abs(mothid)==24)
      return (mothid>0) ? 11 : -11;
    if (abs(id)==13 && abs(mothid)==24)
      return (mothid>0) ? 13 : -13;
    if (abs(id)==15 && abs(mothid)==24)
      return (mothid>0) ? 15 : -15;

    // gluon
    if (abs(id)==21) return 3;

    // light not from W
    if (abs(id)<6) return 4;

  }
  
  // no match
  return -9;
}

//--------------------------------------------------------------------

int getJetIndex( LorentzVector thisJet , FactorizedJetCorrector *jet_corrector_pfL1FastJetL2L3 ){

  for (unsigned int ijet = 0 ; ijet < pfjets_p4().size() ; ijet++) {

    if( fabs( pfjets_p4().at(ijet).eta() ) > 5.0 ) continue;

    //---------------------------------------------------------------------------
    // get total correction: L1FastL2L3 for MC, L1FastL2L3Residual for data
    //---------------------------------------------------------------------------
    
    jet_corrector_pfL1FastJetL2L3->setRho   ( cms2.evt_ww_rho_vor()           );
    jet_corrector_pfL1FastJetL2L3->setJetA  ( cms2.pfjets_area().at(ijet)     );
    jet_corrector_pfL1FastJetL2L3->setJetPt ( cms2.pfjets_p4().at(ijet).pt()  );
    jet_corrector_pfL1FastJetL2L3->setJetEta( cms2.pfjets_p4().at(ijet).eta() );
    double corr = jet_corrector_pfL1FastJetL2L3->getCorrection();
    
    LorentzVector vjet   = corr * pfjets_p4().at(ijet);

    if( fabs( vjet.pt() - thisJet.pt() ) < 0.1 && fabs( vjet.eta() - thisJet.eta() ) < 0.1 && fabs( vjet.phi() - thisJet.phi() ) < 0.1 ) return ijet;

  }

  cout << __FILE__ << " " << __LINE__ << " WARNING! should never get here!" << endl;
  cout << evt_run() << " " << evt_lumiBlock() << " " << evt_event() << endl;
  cout << thisJet.pt() << " " << thisJet.eta() << " " << thisJet.phi() << endl;

  return 0;
}

//--------------------------------------------------------------------

float getJetUnc( const float jetcorpt, const float jeteta , JetCorrectionUncertainty *pfUncertainty ){

  pfUncertainty->setJetEta(jeteta);
  pfUncertainty->setJetPt(jetcorpt);   // here you must use the CORRECTED jet pt
  return pfUncertainty->getUncertainty(true);
}

int getLeptonID( LorentzVector thisLepton ){

  for (unsigned int imu = 0 ; imu < mus_p4().size() ; imu++) {
    
    LorentzVector vmu   = mus_p4().at(imu);
    if( vmu.pt() < 10.0 ) continue;

    if( fabs( vmu.pt() - thisLepton.pt() ) < 0.001 && fabs( vmu.eta() - thisLepton.eta() ) < 0.001 && fabs( vmu.phi() - thisLepton.phi() ) < 0.001 ) return -13 * mus_charge().at(imu);
  }

  for (unsigned int iel = 0 ; iel < els_p4().size() ; iel++) {
    
    LorentzVector vel   = els_p4().at(iel);
    if( vel.pt() < 10.0 ) continue;

    if( fabs( vel.pt() - thisLepton.pt() ) < 0.001 && fabs( vel.eta() - thisLepton.eta() ) < 0.001 && fabs( vel.phi() - thisLepton.phi() ) < 0.001 ) return -11 * els_charge().at(iel);
  }

  cout << __FILE__ << " " << __LINE__ << " WARNING! should never get here! couldn't find matching lepton" << endl;
  cout << evt_run() << " " << evt_lumiBlock() << " " << evt_event() << endl;
  cout << thisLepton.pt() << " " << thisLepton.eta() << " " << thisLepton.phi() << endl;

  return 0;
}

pair<float, float> ScaleMET( pair<float, float> p_met, LorentzVector p4_dilep, double rescale = 1.0 ){
  float met = p_met.first;
  float metPhi = p_met.second;
  float metx = met*cos(metPhi);
  float mety = met*sin(metPhi);

  float lepx = p4_dilep.Px();
  float lepy = p4_dilep.Py();
      
  //hadronic component of MET (well, mostly), scaled
  float metHx = (metx + lepx)*rescale;
  float metHy = (mety + lepy)*rescale;
  float metNewx = metHx - lepx;
  float metNewy = metHy - lepy;
  float metNewPhi = atan2(metNewy, metNewx);
      
  pair<float, float> p_met2 = make_pair(sqrt(metNewx*metNewx + metNewy*metNewy), metNewPhi);
  return p_met2;
}


//--------------------------------------------------------------------

bool eventInList(char* list){

  ifstream myfile(list);

  unsigned long trun;
  unsigned long tlumi;
  unsigned long tevent;

  while( myfile.good() ){

    myfile >> trun >> tlumi >> tevent;

    if( trun==evt_run() && tlumi==evt_lumiBlock() && tevent==evt_event() ){
      cout << endl << endl;
      cout << "Found! " << trun << " " << tlumi << " " << tevent << endl;
      myfile.close();
      return true;
    }

  }

  myfile.close();
  return false;

}

//--------------------------------------------------------------------

float getGenMetCustom( const char* prefix ){

  int LSPID = 1000022;
  if( TString(prefix).Contains("ggmsb") ) LSPID = 1000039;

  float metx = 0;
  float mety = 0;

  // cout << "------------------------------------------------" << endl;
  // cout << "Calculating custom genmet" << endl;
  // cout << "LSPID " << LSPID << endl;

  int nLSP = 0;

  for ( size_t i = 0; i < genps_id().size() ; i++) {

    int id = abs( cms2.genps_id().at(i) );

    //cout << "Particle " << i << " ID " << id << " pt " << genps_p4().at(i).pt() << endl;

    if( id == 12 || id == 14 || id == 16 || id == LSPID ){

      //cout << "INVISIBLE " << i << " ID " << id << " pt " << genps_p4().at(i).pt() << endl;

      metx -= genps_p4().at(i).px();
      mety -= genps_p4().at(i).py();

      if( id == LSPID ) nLSP++;
    }
    
    if( genps_lepdaughter_id().at(i).size() > 0) {

      for(unsigned int j = 0; j < cms2.genps_lepdaughter_id().at(i).size(); j++) {

		int iddau = abs( genps_lepdaughter_id().at(i).at(j) );

		if( iddau == 12 || iddau == 14 || iddau == 16 ){

		  //cout << "INVISIBLE " << i << " daughter " << j << " ID " << id << " pt " << genps_lepdaughter_p4().at(i).at(j).pt() << endl;

		  metx -= genps_lepdaughter_p4().at(i).at(j).px();
		  mety -= genps_lepdaughter_p4().at(i).at(j).py();
		}
      }
    }
  }

  if( evt_isRealData() && (( TString(prefix).Contains("ggmsb") || 
					TString(prefix).Contains("sms") || 
					TString(prefix).Contains("T5") ) && 
				  nLSP != 2 )){
    cout << "ERROR!!!! FOUND " << nLSP << " LSP's <<<<---------------------------------" << endl;
    exit(0);
  }

  //cout << "------------------------------------------------" << endl;

  return sqrt( metx*metx + mety*mety );

}


//--------------------------------------------------------------------

double dRbetweenVectors(const LorentzVector &vec1, 
						const LorentzVector &vec2 ){ 

  double dphi = std::min(::fabs(vec1.Phi() - vec2.Phi()), 2 * M_PI - fabs(vec1.Phi() - vec2.Phi()));
  double deta = vec1.Eta() - vec2.Eta();
  return sqrt(dphi*dphi + deta*deta);
}

//--------------------------------------------------------------------

bool isOverlap( const LorentzVector& thisp4, const vector<LorentzVector>& p4vec, float dRthresh ){

  for (unsigned int i=0; i<p4vec.size(); ++i) {
    if (dRbetweenVectors(thisp4,p4vec.at(i)) < dRthresh) return true;
  }

  return false;
}

//--------------------------------------------------------------------

struct DorkyEventIdentifier {
  // this is a workaround for not having unique event id's in MC
  unsigned long int run, event,lumi;
  bool operator < (const DorkyEventIdentifier &) const;
  bool operator == (const DorkyEventIdentifier &) const;
};

//--------------------------------------------------------------------

bool DorkyEventIdentifier::operator < (const DorkyEventIdentifier &other) const
{
  if (run != other.run)
    return run < other.run;
  if (event != other.event)
    return event < other.event;
  if(lumi != other.lumi)
    return lumi < other.lumi;
  return false;
}

//--------------------------------------------------------------------

bool DorkyEventIdentifier::operator == (const DorkyEventIdentifier &other) const
{
  if (run != other.run)
    return false;
  if (event != other.event)
    return false;
  return true;
}

//--------------------------------------------------------------------

std::set<DorkyEventIdentifier> already_seen;

bool is_duplicate (const DorkyEventIdentifier &id) {
  std::pair<std::set<DorkyEventIdentifier>::const_iterator, bool> ret =
    already_seen.insert(id);
  return !ret.second;
}

//--------------------------------------------------------------------

bool isMuMuEvent(){

  if( evt_run() ==  146430 && evt_lumiBlock() ==        3  && evt_event() ==    460014 ) return true;
  if( evt_run() ==  147216 && evt_lumiBlock() ==       48  && evt_event() ==  35885648 ) return true;
  if( evt_run() ==  147217 && evt_lumiBlock() ==       75  && evt_event() ==  55188718 ) return true;
  if( evt_run() ==  148031 && evt_lumiBlock() ==      765  && evt_event() == 595250802 ) return true;
  if( evt_run() ==  147450 && evt_lumiBlock() ==       82  && evt_event() ==  29253181 ) return true;
  if( evt_run() ==  148029 && evt_lumiBlock() ==      534  && evt_event() == 414899947 ) return true;
  if( evt_run() ==  148862 && evt_lumiBlock() ==      350  && evt_event() == 522383338 ) return true;
  if( evt_run() ==  149181 && evt_lumiBlock() ==     1769  && evt_event() == 1675896175) return true;
  if( evt_run() ==  149182 && evt_lumiBlock() ==      167  && evt_event() == 145682218)  return true;
  if( evt_run() ==  149291 && evt_lumiBlock() ==      205  && evt_event() == 199787369)  return true;
  if( evt_run() ==  149291 && evt_lumiBlock() ==      232  && evt_event() == 235101408)  return true;
  if( evt_run() ==  149291 && evt_lumiBlock() ==      616  && evt_event() == 641847074)  return true;
  
  return false;
}

//--------------------------------------------------------------------

void printEvent(){

  cout << evt_dataset().at(0) << endl;
  cout << evt_run() << " " << evt_lumiBlock() << " " << evt_event() << endl;

}

//--------------------------------------------------------------------

float Z_looper::gluinoPairCrossSection( float gluinomass ){

  int   bin  = gg_xsec_hist->FindBin(gluinomass);
  float xsec = gg_xsec_hist->GetBinContent(bin);

  return xsec;
}

//--------------------------------------------------------------------

float getGMSBCrossSection( int mu ){

  float xsec = -1;

  if( mu ==110 ) xsec = 7.288;
  if( mu ==130 ) xsec = 3.764;
  if( mu ==150 ) xsec = 2.141;
  if( mu ==170 ) xsec = 1.304;
  if( mu ==190 ) xsec = 0.837;
  if( mu ==210 ) xsec = 0.558;
  if( mu ==230 ) xsec = 0.382;
  if( mu ==250 ) xsec = 0.271;
  if( mu ==270 ) xsec = 0.195;
  if( mu ==290 ) xsec = 0.142;
  if( mu ==310 ) xsec = 0.106;
  if( mu ==330 ) xsec = 0.0798;
  if( mu ==350 ) xsec = 0.0608;
  if( mu ==370 ) xsec = 0.0468;
  if( mu ==390 ) xsec = 0.0366;
  if( mu ==410 ) xsec = 0.0287;
      
  if( xsec < 0 ){
    cout << __FILE__ << " " << __LINE__ << " ERROR! couldn't find GMSB cross section for mu " << mu << endl;
  }

  return xsec;

}

//--------------------------------------------------------------------

void Z_looper::ScanChain (TChain* chain, const char* prefix, bool isData,
                          bool calculateTCMET, int my_nEvents, float kFactor){

  if( TString(prefix).Contains("53X") || TString(prefix).Contains("DY_Pythia") || TString(prefix).Contains("TChizh") ){
    useOldIsolation = false;
    cout << "53X sample: using NEW isolation" << endl;
  }


  // else{
  //   useOldIsolation = true;
  //   cout << "52X sample: using OLD isolation" << endl;
  // }

  float MCscalefactor = 1;

  // if( TString(prefix).Contains("zz2l2q_53X") ){
  //   MCscalefactor = 2.45 / 1.275;
  //   cout << "ZZJetsTo2L2Q: scale cross section by 2.45/1.275" << endl;
  // }

  if( TString(prefix).Contains("zjets_small_53X_slim") ){
    //MCscalefactor = 478.0 / 48.0;
    //cout << "DYJets: scale cross section by 478/48" << endl;
    MCscalefactor = 763.0 / 111.0;
    cout << "DYJets: scale cross section by 763/111" << endl;
  }

  // else if( TString(prefix).Contains("zjets_53X_slim") ){
  //   MCscalefactor = 478.0 / 457.0;
  //   cout << "DYJets: scale cross section by 478/457" << endl;
  // }

  isdata_ = isData ? 1 : 0;

  cout << "version : " << iter         << endl;
  cout << "json    : " << jsonfilename << endl;

  if( isData  ) doTenPercent = false;

  if( doTenPercent ) cout << "Processing 10% of MC" << endl;


  set_goodrun_file( jsonfilename );

  if( TString(prefix).Contains("sms") || TString(prefix).Contains("T5zz") ){
    set_vtxreweight_rootfile("../vtxreweighting/vtxreweight_Summer12MC_TChiwz_9p7fb_Zselection.root",true);
  }
  else if( TString(prefix).Contains("gmsb") ){
    set_vtxreweight_rootfile("../vtxreweighting/vtxreweight_Summer12MC_GMSB_9p7fb_Zselection.root",true);
  }
  else if( TString(prefix).Contains("massiveb") ){
    set_vtxreweight_rootfile("../vtxreweighting/vtxreweight_Summer12MC_PUS6.root",true);
  }
  else{
    set_vtxreweight_rootfile("../vtxreweighting/vtxreweight_Summer12MC_PUS10_19fb_Zselection.root",true);
  }

  // ofstream* ofile = new ofstream();
  // ofile->open(Form("%s_SNT.txt",prefix),ios::trunc);

  bookHistos();

  //------------------------------------------------------------------------------------------------------
  // load here the on-the-fly corrections/uncertainties L1FastL2L3 (MC) and L1FastL2L3Residual (DATA)
  // corrections are stored in jet_corrected_pfL1FastJetL2L3
  // uncertainties are stored in pfUncertainty
  //------------------------------------------------------------------------------------------------------

  std::vector<std::string> jetcorr_filenames_pfL1FastJetL2L3;
  FactorizedJetCorrector *jet_corrector_pfL1FastJetL2L3;

  jetcorr_filenames_pfL1FastJetL2L3.clear();

  string pfUncertaintyFile;

  // 42X ported to 52X
  //char* dataJEC = "GR_R_42_V23";
  //char* mcJEC   = "DESIGN42_V17";

  // new 52X
  // string dataJEC = "GR_R_52_V9";
  // string mcJEC   = "START52_V9B";

  // use for ETH pt40 jets
  string dataJEC = FT_53_V6_AN3;
  string mcJEC = FT_53_V6_AN3;

  if ( isData ) {
    // jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("jetCorrections/%s_AK5PF_L1FastJet.txt"    , dataJEC ));
    // jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("jetCorrections/%s_AK5PF_L2Relative.txt"   , dataJEC ));
    // jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("jetCorrections/%s_AK5PF_L3Absolute.txt"   , dataJEC ));
    // jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("jetCorrections/%s_AK5PF_L2L3Residual.txt" , dataJEC ));
    // pfUncertaintyFile = Form("jetCorrections/%s_AK5PF_Uncertainty.txt",dataJEC );

    jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("../jetCorrections/%s_L1FastJet_AK5PF.txt"    , dataJEC.c_str() ));
    jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("../jetCorrections/%s_L2Relative_AK5PF.txt"   , dataJEC.c_str() ));
    jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("../jetCorrections/%s_L3Absolute_AK5PF.txt"   , dataJEC.c_str() ));
    jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("../jetCorrections/%s_L2L3Residual_AK5PF.txt" , dataJEC.c_str() ));
    pfUncertaintyFile = Form("../jetCorrections/%s_Uncertainty_AK5PF.txt",dataJEC.c_str() );
  } 
  else {
    // jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("jetCorrections/%s_AK5PF_L1FastJet.txt"  , mcJEC ));
    // jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("jetCorrections/%s_AK5PF_L2Relative.txt" , mcJEC ));
    // jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("jetCorrections/%s_AK5PF_L3Absolute.txt" , mcJEC ));    
    // pfUncertaintyFile = Form("jetCorrections/%s_AK5PF_Uncertainty.txt",mcJEC );

    jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("../jetCorrections/%s_L1FastJet_AK5PF.txt"  , mcJEC.c_str() ));
    jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("../jetCorrections/%s_L2Relative_AK5PF.txt" , mcJEC.c_str() ));
    jetcorr_filenames_pfL1FastJetL2L3.push_back  (Form("../jetCorrections/%s_L3Absolute_AK5PF.txt" , mcJEC.c_str() ));    
    pfUncertaintyFile = Form("../jetCorrections/%s_Uncertainty_AK5PF.txt",mcJEC.c_str() );
  }

  jet_corrector_pfL1FastJetL2L3  = makeJetCorrector(jetcorr_filenames_pfL1FastJetL2L3);

  MetCorrector* myMetCorrector = new MetCorrector(jetcorr_filenames_pfL1FastJetL2L3);

  JetCorrectionUncertainty *pfUncertainty   = new JetCorrectionUncertainty( pfUncertaintyFile );

  //set stop cross section file
  gg_xsec_file = TFile::Open("../susy_xsecs/reference_xSec_mg2TeV.root");
  
  if( !gg_xsec_file->IsOpen() ){
    cout << "Error, could not open gluino cross section TFile, quitting" << endl;
    exit(0);
  }

  gg_xsec_hist        = (TH1D*) gg_xsec_file->Get("gluino");
    
  if( gg_xsec_hist == 0 ){
    cout << "Error, could not retrieve gg cross section hist, quitting" << endl;
    exit(0);
  }

  TFile* file_C1N2 = TFile::Open("../susy_xsecs/C1N2_8TeV_finer.root");
  TFile* file_N1N2 = TFile::Open("../susy_xsecs/N1N2_referencexSec.root");

  TH1F*  xsec_C1N2 = (TH1F*) file_C1N2->Get("C1N2_8TeV_NLO");
  TH1F*  xsec_N1N2 = (TH1F*) file_N1N2->Get("N1N2");

  //-----------------------
  // make a baby ntuple
  //-----------------------

  //stringstream babyfilename;
  //babyfilename << prefix << "_baby.root";
  string tpsuffix = "";
  if( doTenPercent ) tpsuffix = "_tenPercent";

  string ptsuffix = "";
  if( pt2020 ) ptsuffix = "_pt2020";

  string isosuffix = "";
  if( useOldIsolation ) isosuffix = "_oldIso";

  string jsonsuffix = "";
  if( isData && !useJson ) jsonsuffix = "_nojson";

  cout << "Writing baby ntuple " << Form("../output/%s/%s_baby%s%s%s%s.root" , iter.c_str() , prefix , tpsuffix.c_str() , ptsuffix.c_str() , isosuffix.c_str() , jsonsuffix.c_str() ) << endl;

  if( doGenSelection ) MakeBabyNtuple( Form("../output/%s/%s_gen_baby%s%s%s.root"  , iter.c_str() , prefix , tpsuffix.c_str() , ptsuffix.c_str() , isosuffix.c_str() ) );
  else MakeBabyNtuple( Form("../output/%s/%s_baby%s%s%s%s.root" , iter.c_str() , prefix , tpsuffix.c_str() , ptsuffix.c_str() , isosuffix.c_str() , jsonsuffix.c_str() ) );

  TObjArray *listOfFiles = chain->GetListOfFiles();

  unsigned int nEventsChain = 0;
  if(my_nEvents == -1) 
    my_nEvents = chain->GetEntries();
  nEventsChain = my_nEvents;
  unsigned int nEventsTotal = 0;

  //-----------------------  
  //pass fail counters
  //-----------------------

  float nGoodMu = 0;
  float nGoodEl = 0;
  float nGoodEM = 0;
  int nSkip_els_conv_dist = 0;

  int  nTot                 = 0;  //total number of events
  
  int   nGenPass60          = 0;  //number of events generated in sig window
  float nGenPass60_K        = 0;  //number of events generated in sig window
  int   nRecoPassGenPass60  = 0;  //number of events reconstructed in sig window which pass gen
  int   nRecoPassGenFail60  = 0;  //number of events reconstructed in sig window which fail gen

  int   nGenPass120         = 0;  //number of events generated in sig window
  float nGenPass120_K       = 0;  //number of events generated in sig window
  int   nRecoPassGenPass120 = 0;  //number of events reconstructed in sig window which pass gen
  int   nRecoPassGenFail120 = 0;  //number of events reconstructed in sig window which fail gen

  const int ncuts = 10;
  int nRecoPass_cut[ncuts];
  for( int icut = 0 ; icut < ncuts ; ++icut )
    nRecoPass_cut[icut] = 0;

  if(debug) cout << "Begin file loop" << endl;

  //------------------
  // file loop
  //------------------

  string thisFile = "blah";

  TIter fileIter(listOfFiles);
  TFile* currentFile = 0;
  while ((currentFile = (TFile*)fileIter.Next())){
    
    TFile* f = new TFile(currentFile->GetTitle());

    if( !f || f->IsZombie() ) {
      cout << "Skipping bad input file: " << currentFile->GetTitle() << endl;
      continue; //exit(1);                                                                                             
    }

    if( thisFile != (string)currentFile->GetTitle() ){
      thisFile = (string) currentFile->GetTitle();
      cout << "Running on: "<< thisFile << endl;
    }

    TTree *tree = (TTree*)f->Get("Events");

    //Matevz
    TTreeCache::SetLearnEntries(100);
    tree->SetCacheSize(128*1024*1024);

    cms2.Init(tree);

    unsigned int nEvents = tree->GetEntries();
 
    for (unsigned int event = 0 ; event < nEvents; ++event){
	  
      //Matevz
      tree->LoadTree(event);
      
      cms2.GetEntry(event);
      ++nEventsTotal;

      // if( cms2.evt_event() == 296071331 ){
      // 	cout << "FOUND EVENT" << endl;
      // 	cout << "numCharge     " << pfcands_charge().size() << endl;
      // 	cout << "nump4         " << pfcands_p4().size()     << endl;
      // }
      // else continue;

      if( pfcands_charge().size() != pfcands_p4().size() ){
	  	cout << "ERROR! pfcands_charge().size() " << pfcands_charge().size() << " pfcands_p4().size() " << pfcands_p4().size() << endl;
	  	cout << "SKIPPING " << evt_run() << " " << evt_lumiBlock() << " " << evt_event() << endl;
	  	continue;
      }

      //dumpDocLines();
      //cout << endl << endl;

      //if( !eventInList("../scripts/sync/DoubleEl_dz.txt" ) ) continue;

      if( doTenPercent ){
		if( !(nEventsTotal%10==0) ) continue;
      }

      // if( susyScan_Mmu() == 150 ){
      // 	dumpDocLines();
      // }
      // else{
      // 	continue;
      // }

      // if( TString(prefix).Contains("wzsms") ){
      // 	if( sparm_values().at(0) > 350 ) continue;
      // }

      nTot++;

      if( doGenSelection ){

		InitBabyNtuple();

		weight_ = cms2.evt_scale1fb();
	  
		if( doTenPercent )	  weight_ *= 10;
	
		if( TString(prefix).Contains("LM4") ) weight_ *= kfactorSUSY( "lm4" );
		if( TString(prefix).Contains("LM8") ) weight_ *= kfactorSUSY( "lm8" );

		eff0_   = GenWeight(isData,(char*)prefix,0);
		eff100_ = GenWeight(isData,(char*)prefix,100);
		eff200_ = GenWeight(isData,(char*)prefix,200);
		eff300_ = GenWeight(isData,(char*)prefix,300);
	  
		if(TString(prefix).Contains("T5zz") || TString(prefix).Contains("sms") || TString(prefix).Contains("gmsb") ){
		  mg_ = -1;//;sparm_mG();
		  ml_ = -1;//sparm_mL();
		  x_  = -1;//sparm_mf();
		}

		FillBabyNtuple();
		continue;
      }
    
      float ksusy = 1;
      if( TString(prefix).Contains("LM0")  ) ksusy = kfactorSUSY( "lm0"   );
      if( TString(prefix).Contains("LM1")  ) ksusy = kfactorSUSY( "lm1"   );
      if( TString(prefix).Contains("LM2")  ) ksusy = kfactorSUSY( "lm2"   );
      if( TString(prefix).Contains("LM3")  ) ksusy = kfactorSUSY( "lm3"   );
      if( TString(prefix).Contains("LM4")  ) ksusy = kfactorSUSY( "lm4"   );
      if( TString(prefix).Contains("LM5")  ) ksusy = kfactorSUSY( "lm5"   );
      if( TString(prefix).Contains("LM6")  ) ksusy = kfactorSUSY( "lm6"   );
      if( TString(prefix).Contains("LM7")  ) ksusy = kfactorSUSY( "lm7"   );
      if( TString(prefix).Contains("LM8")  ) ksusy = kfactorSUSY( "lm8"   );
      if( TString(prefix).Contains("LM9")  ) ksusy = kfactorSUSY( "lm9"   );
      if( TString(prefix).Contains("LM10") ) ksusy = kfactorSUSY( "lm10"  );
      if( TString(prefix).Contains("LM11") ) ksusy = kfactorSUSY( "lm11"  );
      if( TString(prefix).Contains("LM12") ) ksusy = kfactorSUSY( "lm12"  );
      if( TString(prefix).Contains("LM13") ) ksusy = kfactorSUSY( "lm13"  );

      if( PassGenSelection( isData ) > 60. ){
		nGenPass60++;
		nRecoPass_cut[0]++;
		nGenPass60_K += ksusy;
      }
      if( PassGenSelection( isData ) > 120. ){
		nGenPass120++;
		nRecoPass_cut[0]++;
		nGenPass120_K += ksusy;
      }

      if( !isData ){
	  	hresponse->Fill( gen_met() , evt_pfmet() / gen_met() );
      	hgenmet_all->Fill( gen_met() );
	  	if( evt_pfmet() > 60 ) hgenmet_pass->Fill( gen_met() );
      }

      // progress feedback to user
      if (nEventsTotal % 1000 == 0){
            
        // xterm magic from L. Vacavant and A. Cerri
        if (isatty(1)){
                
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
                 "\033[0m\033[32m <---\033[0m\015", (float)nEventsTotal/(nEventsChain*0.01));
          fflush(stdout);
        }
      }

      if( isData ) {
		DorkyEventIdentifier id = { evt_run(),evt_event(), evt_lumiBlock() };
		if (is_duplicate(id) )
		  continue;
      }
      
      //-----------------------------
      // good run+event selection
      //-----------------------------

      if( isData && useJson && !goodrun(cms2.evt_run(), cms2.evt_lumiBlock()) ) continue;
      if( !cleaning_goodVertexApril2011() )                                     continue;

      if( PassGenSelection( isData ) > 60. )   nRecoPass_cut[1]++;
      
      if(debug) cout << "Pass event selection" << endl;

      InitBabyNtuple();

      // event stuff
      strcpy(dataset_, cms2.evt_dataset().at(0).Data());
      run_    = cms2.evt_run();
      lumi_   = cms2.evt_lumiBlock();
      event_  = cms2.evt_event();

      weight_ = 1.;
      pthat_  = -1;
      xsec_   = 1.0;
	
	  vector<LorentzVector> genbquarks;
	  vector<LorentzVector> genleps;
	  vector<LorentzVector> gennus;
	  
      if( !isData ){

		weight_ = MCscalefactor * cms2.evt_scale1fb() * kFactor * lumi;
		xsec_   = MCscalefactor * cms2.evt_xsec_excl();

		if( doTenPercent )	  weight_ *= 10;

		if( TString(prefix).Contains("LM") ){
		  if( TString(prefix).Contains("LM0") ) weight_ *= kfactorSUSY( "lm0" );
		  if( TString(prefix).Contains("LM1") ) weight_ *= kfactorSUSY( "lm1" );
		  if( TString(prefix).Contains("LM2") ) weight_ *= kfactorSUSY( "lm2" );
		  if( TString(prefix).Contains("LM3") ) weight_ *= kfactorSUSY( "lm3" );
		  if( TString(prefix).Contains("LM4") ) weight_ *= kfactorSUSY( "lm4" );
		  if( TString(prefix).Contains("LM5") ) weight_ *= kfactorSUSY( "lm5" );
		  if( TString(prefix).Contains("LM6") ) weight_ *= kfactorSUSY( "lm6" );
		  if( TString(prefix).Contains("LM7") ) weight_ *= kfactorSUSY( "lm7" );
		  if( TString(prefix).Contains("LM8") ) weight_ *= kfactorSUSY( "lm8" );
		  if( TString(prefix).Contains("LM9") ) weight_ *= kfactorSUSY( "lm9" );
		}

		ngenels_  = 0;
		ngenmus_  = 0;
		ngentaus_ = 0;
		ngenleps_ = 0;
		ngennue_  = 0;
		ngennum_  = 0;
		ngennut_  = 0;
		ngennu_   = 0;
	  
		Bool_t foundwz = false;
		// Int_t nwzpartons = 0;

		try
		  {	
			size_t size = cms2.genps_id().size(); 
			for (size_t jj=0; jj<size; jj++) { 
			  Int_t pid = abs(cms2.genps_id().at(jj));

			  if ( pid == 11 ){
				ngenels_++; 
				genleps.push_back(cms2.genps_p4().at(jj));
			  }
			  if ( pid == 13 ){
				genleps.push_back(cms2.genps_p4().at(jj));
				ngenmus_++; 
			  }
			  if ( pid == 15 ) ngentaus_++; 
			  if ( pid == 12 ){
				gennus.push_back(cms2.genps_p4().at(jj));
				ngennue_++; 
			  }
			  if ( pid == 14 ){
				gennus.push_back(cms2.genps_p4().at(jj));
				ngennum_++; 
			  }
			  if ( pid == 16 ) ngennut_++; 
			  if ( pid == 23 ) {
				// ptzgen_ = genps_p4().at(igen).pt();
				foundwz = true;
				nwzpartons_  = 0;
			  }
		  
			  if (foundwz && ( pid == 1 || pid == 2 || pid == 3 || pid == 4 || pid == 5 || pid == 6 || pid == 21 ) ) {  
				nwzpartons_++;
			  }
		
			  if( pid == 1000023 && TString(prefix).Contains("TChizh_53X_scan") ){
				genchi20p4_ = &cms2.genps_p4().at(jj);
			  }
			  if( pid == 1000025 && TString(prefix).Contains("TChizh_53X_scan") ){
				genchi30p4_ = &cms2.genps_p4().at(jj);
			  }
			  if( pid == 1000022 && TString(prefix).Contains("TChizh_53X_scan") ){
				if( cms2.genps_id_mother().at(jj) == 1000023 ){ genchi10p4_2_ = &cms2.genps_p4().at(jj);	}
				if( cms2.genps_id_mother().at(jj) == 1000025 ){ genchi10p4_3_ = &cms2.genps_p4().at(jj);	}
			  }

			  //-------------------------------------------------------------
			  // loop over gen particles to find b quarks
			  //-------------------------------------------------------------
			  if ( abs(pid) == 5 ) {
				Float_t m2 = cms2.genps_p4().at(jj).M2();
				Float_t m  = m2 >= 0 ? sqrt(m2) : 0.0;
				if (m > 0.) {
				  ++ngenbs_;
				  genbquarks.push_back(cms2.genps_p4().at(jj));
				}
			  }
			}
	  	
			try
			  {
				if( genleps.size() == 1 ){
				  genlep1_ = &genleps.at(0);
				}
				else if( genleps.size() > 1 ){
				  genlep1_ = &genleps.at(0);
				  genlep2_ = &genleps.at(1);
				}
				if( gennus.size() == 1 ){
				  gennu1_ = &genleps.at(0);
				}
				else if( gennus.size() > 1 ){
				  gennu1_ = &gennus.at(0);
				  gennu2_ = &gennus.at(1);
				}

			  }
			catch (exception& e)	
			  {
				cout<<e.what()<<endl;
				cout<<"Problem before line: "<<__LINE__<<endl;
				cout<<"problem with getting genleps/nus vars."<<endl;
			  }

			ngenleps_ = ngenels_ + ngenmus_ + ngentaus_;
			ngennu_   = ngennue_ + ngennum_ + ngennut_;		
			pthat_  = cms2.genps_pthat();	

		  }
		catch (exception& e)	
		  {
			cout<<e.what()<<endl;
			cout<<"Problem before line: "<<__LINE__<<endl;
			cout<<"problem with getting gen vars."<<endl;
		  }
	 
	  }
		
		sort(genbquarks.begin(), genbquarks.end(), sortByPt);
		if( genbquarks.size() > 0 ){
		  genbquark1_ = &(genbquarks.at(0));
		}
		if( genbquarks.size() > 1 ){
		  genbquark2_ = &(genbquarks.at(1));
		}
		if( genbquarks.size() > 2 ){
		  genbquark3_ = &(genbquarks.at(2));
		}
		if( genbquarks.size() > 3 ){
		  genbquark4_ = &(genbquarks.at(3));
		}
		
	
	  mg_ = -1;
	  ml_ = -1; 
	  x_  = -1.;

	  genmetcustom_ = 0;


	try
	  {		  
	  
		if(!isData && (TString(prefix).Contains("T5zz") || TString(prefix).Contains("sms") || TString(prefix).Contains("gmsb") || TString(prefix).Contains("TChizh_53X_scan") ) ){

		  if     (TString(prefix).Contains("T5zz" ) ){
			mg_ = -1;//sparm_mG();
			ml_ = -1;//sparm_mL();
			x_  = -1;//sparm_mf();
			weight_ = lumi * gluinoPairCrossSection(mg_) * (1000./105000.);
		  }

		  else if( TString(prefix).Contains("wzsms") ){
			mg_ = cms2.sparm_values().at(0);
			ml_ = cms2.sparm_values().at(1);
			x_  = -999.;

			int   mgbin = xsec_C1N2->FindBin(mg_);
			float xsec  = xsec_C1N2->GetBinContent(mgbin);
			weight_ = lumi * xsec * (1000.0/100000.);
		  }

		  else if( TString(prefix).Contains("zzsms") ){
			mg_ = -1;//sparm_mN();
			ml_ = -1;//sparm_mL();
			x_  = -999;
			int bin = xsec_N1N2->FindBin(mg_);
			weight_ = lumi * xsec_N1N2->GetBinContent(bin) * (1.0/52600.);
		  }

		  else if( TString(prefix).Contains("TChizh_53X_scan") ){

			mg_ = -1;//sparm_mN();
			ml_ = -1;//sparm_mL();
			mg_     = cms2.sparm_values().at(0);
			ml_     = cms2.sparm_values().at(1);
			weight_ = 0.5 * lumi * getZHGMSBCrossSection( mg_ ) * (1000.0) / nsigEvtsHist_ -> GetBinContent( nsigEvtsHist_ -> FindBin( mg_, ml_ ) ); // /nevts);
			x_  = -999;

		  }

		  else if( TString(prefix).Contains("gmsb") ){

			mg_     = cms2.sparm_values().at(0);
			weight_ = lumi * getGMSBCrossSection( mg_ ) * (1000.0 / 300000.0);

			ml_ = -999;
			x_  = -999;
		  }
	
		  if( doTenPercent )	  weight_ *= 10;
		  //weight_ *= 10; // REMOVE

		  genmetcustom_ = getGenMetCustom(prefix);

		}	

	  }
	catch (exception& e)	
	  {
		cout<<e.what()<<endl;
		cout<<"Problem before line: "<<__LINE__<<endl;
		cout<<"problem with hyp_ll."<<endl;
	  }

	// calomet, pfmet, genmet
	met_       = cms2.evt_met();
	metphi_    = cms2.evt_metPhi();
	sumet_     = cms2.evt_sumet();

	pfmet_    = cms2.evt_pfmet();
	pfmetphi_ = cms2.evt_pfmetPhi();
	pfsumet_  = cms2.evt_pfsumet();
      
	vtxidx_   = firstGoodVertex();

	pfmett1_     = cms2.evt_pfmet_type1cor();
	pfmett1phi_  = cms2.evt_pfmetPhi_type1cor();
	
	std::pair<float, float> Type1PFMetPair = myMetCorrector->getCorrectedMET();
	pfmett1new_     = Type1PFMetPair.first;
	pfmett1newphi_  = Type1PFMetPair.second;

	if (!isData){
	  genmet_     = cms2.gen_met();
	  genmetphi_  = cms2.gen_metPhi();
	  gensumet_   = cms2.gen_sumEt();

	  qscale_ = genps_qScale();

	  //splice together the DY samples - if its madgraph, then we do nothing
	  if(TString(prefix).Contains("DY") && TString(evt_dataset().at(0)).Contains("madgraph") == false && TString(prefix).Contains("DY_Pythia") == false) {	
		bool doNotContinue = false;
		for(unsigned int i = 0; i < genps_p4().size(); i++){
		  if(abs(genps_id()[i]) == 23 && genps_p4()[i].M() > 50.)
			doNotContinue = true;
		}
		if(doNotContinue)
		  continue;	
	  }

	  //extract gen-level dilepton mass
	  if(TString(prefix).Contains("DY")){
		int nz = 0;
		for(unsigned int i = 0; i < genps_p4().size(); i++){
		  if(abs(genps_id()[i]) == 23){
			mllgen_ = genps_p4()[i].M();
			nz++;
		  }
		}
		if(nz != 1 ) cout << "ERROR NZ " << nz << endl;
	  }
	}
	      
	st_ = -1;

	if( !isData && TString(prefix).Contains("singletop") ){
	  if     ( TString(evt_dataset().at(0)).Contains("TuneZ2_s-")  ) st_ = 0;
	  else if( TString(evt_dataset().at(0)).Contains("TuneZ2_t-")  ) st_ = 1;
	  else if( TString(evt_dataset().at(0)).Contains("TuneZ2_tW-") ) st_ = 2;
	  else{
		cout << "Unrecognized single top sample " << evt_dataset().at(0) << endl;
	  }
	}
	
	vector<unsigned int> v_goodHyps;
	v_goodHyps.clear();

	int nHypPass = 0;

	VofP4 goodLeptons;
	vector<int> goodLeptonIDs;
	vector<int> goodMuonIndices;
	vector<int> goodPFMuonIndices;
	vector<bool>  killedJet;
	goodLeptons.clear();
	goodLeptonIDs.clear();
	killedJet.clear();
	goodMuonIndices.clear();
	goodPFMuonIndices.clear();

	nlep_ = 0;
	nmu_  = 0;
	nel_  = 0;
      
	eldup_ = 0;

	if( generalLeptonVeto ){
              
	  for( unsigned int iel = 0 ; iel < els_p4().size(); ++iel ){

		// if( nEventsTotal <= 100 ){
		// printf("RelValZEE:   %u\t%u\t%u\t%4.3f\t%4.3f\t%4.3f\t%u\t%4.3f\n", 
		//  	 evt_run() , evt_lumiBlock(), evt_event(), els_p4().at(iel).pt(), els_p4().at(iel).eta(), els_p4().at(iel).phi(), 
		//  	 passElectronSelection_ZMet2012_v1_NoIso(iel,true,true) , electronIsoValuePF2012_FastJetEffArea(iel) );
		//}

		// check for duplicate electrons
		bool foundDuplicate = false;
		for( unsigned int i2 = 0 ; i2 < goodLeptons.size() ; ++i2 ){
		  if( fabs( els_p4().at(iel).pt()  - goodLeptons.at(i2).pt()  ) < 0.001 &&
			  fabs( els_p4().at(iel).eta() - goodLeptons.at(i2).eta() ) < 0.001 &&
			  fabs( els_p4().at(iel).phi() - goodLeptons.at(i2).phi() ) < 0.001 ){
			eldup_ = 1;
			//cout << "WARNING! FOUND DUPLICATE ELECTRON " << evt_run() << " " << evt_lumiBlock() << " " << evt_event() << endl;
			foundDuplicate = true;
		  }
		}
		if( foundDuplicate ) continue;

		if( els_p4().at(iel).pt() < 10 )                                                             continue;
		if( ! passElectronSelection_ZMet2012_v3(iel,vetoTransition,vetoTransition,useOldIsolation) ) continue;

		goodLeptons.push_back( els_p4().at(iel) );
		goodLeptonIDs.push_back( els_charge().at(iel) * -11 );
		nlep_++;
		nel_++;
		killedJet.push_back( false );
	  }
              
	  for( unsigned int imu = 0 ; imu < mus_p4().size(); ++imu ){

		if( mus_p4().at(imu).pt() < 10 )           continue;
		if( !muonId( imu , ZMet2012_v1 ))          continue;//this is the correct line

		goodLeptons.push_back( mus_p4().at(imu) );
		goodLeptonIDs.push_back( mus_charge().at(imu) * -13 );
		nlep_++;
		nmu_++;
		killedJet.push_back( false );
		goodMuonIndices.push_back( imu );
		int ipf = mus_pfmusidx().at(imu);
		if( ipf < (int)pfmus_p4().size() && ipf >= 0 ){
		  goodPFMuonIndices.push_back( imu );
		}
	  }
      
	}

      
	for(unsigned int hypIdx = 0; hypIdx < hyp_p4().size(); ++hypIdx) {
      
	  if( debug ){
		cout << "hyp    " << hypIdx << endl;
		cout << "trig   " << passSUSYTrigger2012_v2( isData ) << endl;
		cout << "ptll   " << hyp_ll_p4()[hypIdx].pt() << endl;
		cout << "ptlt   " << hyp_lt_p4()[hypIdx].pt() << endl;
		cout << "mass   " << hyp_p4()[hypIdx].mass() << endl;
		if( abs(hyp_ll_id()[hypIdx]) == 13 )   cout << "muon ll " << muonId( hyp_ll_index()[hypIdx] , ZMet2012_v1 ) << endl;
		if( abs(hyp_lt_id()[hypIdx]) == 13 )   cout << "muon lt " << muonId( hyp_lt_index()[hypIdx] , ZMet2012_v1 ) << endl;
		if( abs(hyp_ll_id()[hypIdx]) == 11 )   cout << "ele ll  " << passElectronSelection_ZMet2012_v3(hyp_ll_index()[hypIdx],vetoTransition,vetoTransition,useOldIsolation) << endl;
		if( abs(hyp_lt_id()[hypIdx]) == 11 )   cout << "ele lt  " << passElectronSelection_ZMet2012_v3(hyp_lt_index()[hypIdx],vetoTransition,vetoTransition,useOldIsolation) << endl;
	  }

	  if( !passSUSYTrigger2012_v2( isData ) ) continue;

	  //OS, pt > (20,20) GeV, dilmass > 10 GeV
	  if( hyp_lt_id()[hypIdx] * hyp_ll_id()[hypIdx] > 0 )                             continue; 
	  //if( hyp_lt_id()[hypIdx] * hyp_ll_id()[hypIdx] < 0 )                             continue; // SAMESIGN: require SS leptons
	  if( TMath::Max( hyp_ll_p4()[hypIdx].pt() , hyp_lt_p4()[hypIdx].pt() ) < 20. )   continue;
	  if( TMath::Min( hyp_ll_p4()[hypIdx].pt() , hyp_lt_p4()[hypIdx].pt() ) < 10. )   continue;
	  if( pt2020 && TMath::Min( hyp_ll_p4()[hypIdx].pt() , hyp_lt_p4()[hypIdx].pt() ) < 20. )   continue;
	  //if( hyp_p4()[hypIdx].mass() < 10 )                                              continue;
      
	  //muon ID
	  if (abs(hyp_ll_id()[hypIdx]) == 13  && !( muonId( hyp_ll_index()[hypIdx] , ZMet2012_v1 )))   continue;
	  if (abs(hyp_lt_id()[hypIdx]) == 13  && !( muonId( hyp_lt_index()[hypIdx] , ZMet2012_v1 )))   continue;

	  // SAMESIGN: require dimuon
	  //if (hyp_type()[hypIdx] != 0) continue;

	  // SAMESIGN: require NominalSSv5 selection
	  //if (abs(hyp_ll_id()[hypIdx]) == 13  && !( muonId( hyp_ll_index()[hypIdx] , NominalSSv5 )))   continue;
	  //if (abs(hyp_lt_id()[hypIdx]) == 13  && !( muonId( hyp_lt_index()[hypIdx] , NominalSSv5 )))   continue;
              
	  //electron ID
	  if (abs(hyp_ll_id()[hypIdx]) == 11  && (! passElectronSelection_ZMet2012_v3(hyp_ll_index()[hypIdx],vetoTransition,vetoTransition,useOldIsolation)) ) continue;
	  if (abs(hyp_lt_id()[hypIdx]) == 11  && (! passElectronSelection_ZMet2012_v3(hyp_lt_index()[hypIdx],vetoTransition,vetoTransition,useOldIsolation)) ) continue;
        
	  nHypPass++;
	
	  v_goodHyps.push_back( hypIdx );
            
	}

	if( v_goodHyps.size() == 0 ) continue;

	nhyp_ = nHypPass;

	if(debug) cout << "Found good hyp" << endl;

	unsigned int hypIdx = selectBestZHyp(v_goodHyps);

	trkmet_      = cms2.trk_met().at(hypIdx);
	trkmetphi_   = cms2.trk_metPhi().at(hypIdx);
	trksumet_    = cms2.trk_sumet().at(hypIdx);
	minmet_      = TMath::Min(pfmet_,trkmet_);

	//-----------------------------
	// triggers
	//-----------------------------

	el27_  = passUnprescaledHLTTriggerPattern("HLT_Ele27_WP80_v")                                   ? 1 : 0;
	mm_    = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v")                                     ? 1 : 0;
	mmtk_  = passUnprescaledHLTTriggerPattern("HLT_Mu17_TkMu8_v")                                   ? 1 : 0;
	me_    = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") ? 1 : 0;
	em_    = passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") ? 1 : 0;
	mu_    = passUnprescaledHLTTriggerPattern("HLT_IsoMu24_v")                                      ? 1 : 0;
	mu21_  = passUnprescaledHLTTriggerPattern("HLT_IsoMu24_eta2p1_v")                               ? 1 : 0;
	ee_    = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") ? 1 : 0;

	if( PassGenSelection( isData ) > 60. )   nRecoPass_cut[2]++;

	if( !useOldIsolation ){
	  // check extra Z veto
	  extraz_ = ( samesign::makesExtraZ(hypIdx) ) ? 1 : 0;
	
	  // check extra Gamma* veto
	  extrag_ = ( samesign::makesExtraGammaStar(hypIdx) ) ? 1 : 0;
	}
	else{
	  extraz_ = -999;
	  extrag_ = -999;
	}

	leptype_ = 99;
	if (hyp_type()[hypIdx] == 3) leptype_ = 0;                           // ee
	if (hyp_type()[hypIdx] == 0) leptype_ = 1;                           // mm
	if (hyp_type()[hypIdx] == 1 || hyp_type()[hypIdx] == 2) leptype_=2;  // em
	if (leptype_ == 99) {
	  cout << "Skipping unknown dilepton type = " << hyp_type()[hypIdx] << endl;
	  continue;
	}

	trgeff_ = -1;
	if     ( leptype_ == 0 ) trgeff_ = 0.95; // ee
	else if( leptype_ == 1 ){
	  float eta1 = fabs( hyp_ll_p4().at(hypIdx).eta() );
	  float eta2 = fabs( hyp_lt_p4().at(hypIdx).eta() );
	  if( eta1 < 1.0 && eta2 < 1.0 ) trgeff_ = 0.90; // mm central
	  else                           trgeff_ = 0.81; // mm forward
	}
	else if( leptype_ == 2 ) trgeff_ = 0.93; // em

	dilmass_ = hyp_p4()[hypIdx].mass();

	if( leptype_ == 0 ) nGoodEl+=weight_;
	if( leptype_ == 1 ) nGoodMu+=weight_;
	if( leptype_ == 2 ) nGoodEM+=weight_;

	//--------------------------
	// leading lepton = ll
	//--------------------------
      
	int index1 = -1;
	int index2 = -1;
      
	ptll_ = hyp_ll_p4().at(hypIdx).pt();
	ptlt_ = hyp_lt_p4().at(hypIdx).pt();

	ssmu1_ = -1;
	ssmu2_ = -1;

	if( hyp_ll_p4().at(hypIdx).pt() > hyp_lt_p4().at(hypIdx).pt() ){
	
	  index1 = hyp_ll_index()[hypIdx];
	  index2 = hyp_lt_index()[hypIdx];
	
	  lep1_ = &hyp_ll_p4().at(hypIdx);
	  lep2_ = &hyp_lt_p4().at(hypIdx);
	  id1_  = hyp_ll_id()[hypIdx];
	  id2_  = hyp_lt_id()[hypIdx];
	
	  //save electron isolation
	  if( abs(id1_) == 11 )	lep1iso_ = electronIsoValuePF2012_FastJetEffArea_v3(index1, 0.3, 0, useOldIsolation);
	  if( abs(id2_) == 11 )	lep2iso_ = electronIsoValuePF2012_FastJetEffArea_v3(index2, 0.3, 0, useOldIsolation);

	  //save muon isolation
	  if( abs(id1_) == 13 )	lep1iso_ = muonIsoValuePF2012_deltaBeta(index1);
	  if( abs(id2_) == 13 )	lep2iso_ = muonIsoValuePF2012_deltaBeta(index2);

	  //save lepton Dz and D0
	  lep1D0_ = leptonD0(id1_, index1);
	  lep2D0_ = leptonD0(id2_, index2);
	  lep1Dz_ = leptonDz(id1_, index1);
	  lep2Dz_ = leptonDz(id2_, index2);

	  if( abs(id1_) == 13 ) ssmu1_ = muonId( index1 , NominalSSv5 ) ? 1 : 0;
	  if( abs(id2_) == 13 ) ssmu2_ = muonId( index2 , NominalSSv5 ) ? 1 : 0;
	}
      
	//--------------------------
	// leading lepton = lt
	//--------------------------
      
	else{
	
	  index1 = hyp_lt_index()[hypIdx];
	  index2 = hyp_ll_index()[hypIdx];
	
	  lep1_ = &hyp_lt_p4().at(hypIdx);
	  lep2_ = &hyp_ll_p4().at(hypIdx);
	  id1_  = hyp_lt_id()[hypIdx];
	  id2_  = hyp_ll_id()[hypIdx];
	
	  //save electron isolation
	  if( abs(id1_) == 11 )	lep1iso_ = electronIsoValuePF2012_FastJetEffArea_v3(index1, 0.3, 0, useOldIsolation);
	  if( abs(id2_) == 11 )	lep2iso_ = electronIsoValuePF2012_FastJetEffArea_v3(index2, 0.3, 0, useOldIsolation);

	  //save muon isolation
	  if( abs(id1_) == 13 )	lep1iso_ = muonIsoValuePF2012_deltaBeta(index1);
	  if( abs(id2_) == 13 )	lep2iso_ = muonIsoValuePF2012_deltaBeta(index2);

	  //save lepton Dz and D0
	  lep1D0_ = leptonD0(id1_, index1);
	  lep2D0_ = leptonD0(id2_, index2);
	  lep1Dz_ = leptonDz(id1_, index1);
	  lep2Dz_ = leptonDz(id2_, index2);

	  if( abs(id1_) == 13 ) ssmu1_ = muonId( index1 , NominalSSv5 ) ? 1 : 0;
	  if( abs(id2_) == 13 ) ssmu2_ = muonId( index2 , NominalSSv5 ) ? 1 : 0;	
	}

	dphill_ = acos( cos( (*lep1_).phi() - (*lep2_).phi() ) );
	drll_   = dRbetweenVectors( *lep1_ , *lep2_ );

	//muon ID
	if( !isData ){
	  zdilep_ = 1;
	
	  if (abs(id1_) == 13  && mus_mc3_motherid().at(index1) != 23 )  zdilep_ = 0;
	  if (abs(id2_) == 13  && mus_mc3_motherid().at(index2) != 23 )  zdilep_ = 0;
	
	  if (abs(id1_) == 11  && els_mc3_motherid().at(index1) != 23 )  zdilep_ = 0;
	  if (abs(id2_) == 11  && els_mc3_motherid().at(index2) != 23 )  zdilep_ = 0;
	
	  // cout << endl << endl;
	  // dumpDocLines();
	  // cout << "Lepton 1 pT " << lep1_->pt() << endl;
	  // cout << "Lepton 2 pT " << lep2_->pt() << endl;
	  // cout << "From Z?     " << zdilep_     << endl;
	}
	else{
	  zdilep_ = -1;
	}

	//----------------------------
	// matched PFMuons/PFElectrons
	//----------------------------

	el1tv_     = 0;
	el2tv_     = 0;
	el1nomu_   = 1;
	el2nomu_   = 1;
	el1nomuss_ = 1;
	el2nomuss_ = 1;

	int nmatched = 0;

	if( abs(id1_) == 13 ){

	  int ipf1 = mus_pfmusidx().at(index1);

	  if( ipf1 >= (int)pfmus_p4().size() ){
		cout << __FILE__ << " " << __LINE__ << " ERROR! matched pfmuon index " 
			 << ipf1 << " #PFMuons " << pfmus_p4().size() << endl;
		continue;
	  }

	  if( ipf1 >= 0 ){
		pflep1_ = &(pfmus_p4().at(ipf1));
		nmatched++;
	  }
	}

	else if( abs(id1_) == 11 ){

	  int ipf1 = els_pfelsidx().at(index1);

	  if( ipf1 >= (int) pfels_p4().size() ){
		cout << __FILE__ << " " << __LINE__ << " ERROR! matched pfelectron index " 
			 << ipf1 << " #PFElectrons " << pfels_p4().size() << endl;
		continue;
	  }

	  if( ipf1 >= 0 ){
		pflep1_ = &(pfels_p4().at(ipf1));
		nmatched++;
	  }

	  if( fabs(cms2.els_etaSC().at(index1)) >= 1.4442 && fabs(cms2.els_etaSC().at(index1)) <= 1.566 ) el1tv_ = 1;

	  if (!electronId_noMuon(index1)    ) el1nomu_   = 0; 
	  if (!electronId_noMuon_SS(index1) ) el1nomuss_ = 0; 

	}

	if( abs(id2_) == 13 ){

	  int ipf2 = mus_pfmusidx().at(index2);

	  if( ipf2 >= (int)pfmus_p4().size() ){
		cout << __FILE__ << " " << __LINE__ << " ERROR! matched pfmuon index " 
			 << ipf2 << " #PFMuons " << pfmus_p4().size() << endl;
		continue;
	  }

	  if( ipf2 >= 0 ){
		pflep2_ = &(pfmus_p4().at(ipf2));
		nmatched++;
	  }
	}

	else if( abs(id2_) == 11 ){

	  int ipf2 = els_pfelsidx().at(index2);

	  if( ipf2 >= (int)pfels_p4().size() ){
		cout << __FILE__ << " " << __LINE__ << " ERROR! matched pfelectron index " 
			 << ipf2 << " #PFElectrons " << pfels_p4().size() << endl;
		continue;
	  }

	  if( ipf2 >= 0 ){
		pflep2_ = &(pfels_p4().at(ipf2));
		nmatched++;
	  }

	  if( fabs(cms2.els_etaSC().at(index2)) >= 1.4442 && fabs(cms2.els_etaSC().at(index2)) <= 1.566 ) el2tv_ = 1;

	  if (!electronId_noMuon(index2)    ) el2nomu_   = 0; 
	  if (!electronId_noMuon_SS(index2) ) el2nomuss_ = 0; 
	}


	dilep_   = &hyp_p4().at(hypIdx);

	//---------------------------------------------
	// calculate JZB = | -MET - pTZ | - | pTZ |
	//---------------------------------------------

	float metx = evt_pfmet() * cos( evt_pfmetPhi() );
	float mety = evt_pfmet() * sin( evt_pfmetPhi() );

	float pzx  = hyp_p4().at(hypIdx).px();
	float pzy  = hyp_p4().at(hypIdx).py();

	float dx   = -1 * ( metx + pzx );
	float dy   = -1 * ( mety + pzy );

	jzb_ = sqrt( dx*dx + dy*dy ) - hyp_p4().at(hypIdx).pt();


	dilmasspf_ = -1;

	if( nmatched == 2 ){
	  LorentzVector dileppf_temp = *pflep1_ + *pflep2_;
	  dileppf_ = &dileppf_temp;
	  dilmasspf_ = (*pflep1_ + *pflep2_).mass();
	}

	float dilmass = hyp_p4().at(hypIdx).mass();

	ptgen1_ = -1;
	ptgen2_ = -1;

	eveto1_ = -1;
	hveto1_ = -1;
	eveto2_ = -1;
	hveto2_ = -1;

	if( abs(id1_) == 13 ){
	  eveto1_ = mus_iso_ecalvetoDep().at(index1);
	  hveto1_ = mus_iso_hcalvetoDep().at(index1);
	}

	if( abs(id2_) == 13 ){
	  eveto2_ = mus_iso_ecalvetoDep().at(index2);
	  hveto2_ = mus_iso_hcalvetoDep().at(index2);
	}


	if( !isData ){
	
	  if( abs(id1_) == 13 ){
		int mcid1   = mus_mc3idx().at(index1);
		if( mcid1 >=0 && mcid1 < (int)genps_p4().size() ){
		  ptgen1_   = genps_p4().at(mcid1).pt();
		}
	  }
	  else if( abs(id1_) == 11 ){
		int mcid1   = els_mc3idx().at(index1);
		if( mcid1 >=0 && mcid1 < (int)genps_p4().size() ){
		  ptgen1_   = genps_p4().at(mcid1).pt();
		}
	  }

	  if( abs(id2_) == 13 ){
		int mcid2   = mus_mc3idx().at(index2);
		if( mcid2 >=0 && mcid2 < (int)genps_p4().size() ){
		  ptgen2_   = genps_p4().at(mcid2).pt();
		}
	  }
	  else if( abs(id2_) == 11 ){
		int mcid2   = els_mc3idx().at(index2);
		if( mcid2 >=0 && mcid2 < (int)genps_p4().size() ){
		  ptgen2_   = genps_p4().at(mcid2).pt();
		}
	  }


	}

	//-------------------------
	// SAMESIGN: Z-veto
	//-------------------------
	/*
      nmuss_ = 0;

      int index3 = -1;

      for( unsigned int imu = 0 ; imu < mus_p4().size(); ++imu ){

	  if(  mus_p4().at(imu).pt() < 20.0     )       continue; // pT > 20 GeV
	  //if( !muonId( imu , NominalSSv5 )      )       continue; // NominalSSv5
	  if( !muonId( imu , ZMet2012_v1 )      )       continue; // ZMet2012_v1
	  if(  id1_ * mus_charge().at(imu) > 0  )       continue; // require SS

	  nmuss_++;

	  if(  abs(id1_)==13 && imu==index1     )       continue; // skip 1st lepton if its a muon
	  if(  abs(id2_)==13 && imu==index2     )       continue; // skip 2nd lepton if its a muon

	  index3 = imu;
      }

      m1_       = 999.0;
      m2_       = 999.0;
      m3_       = 999.0;
      zveto_    = 0;
      nextramu_ = 0;

      for( unsigned int imu = 0 ; imu < mus_p4().size(); ++imu ){

	  if(  abs(id1_)==13 && imu==index1     )       continue; // skip 1st lepton if its a muon
	  if(  abs(id2_)==13 && imu==index2     )       continue; // skip 2nd lepton if its a muon
	  if(  id1_ * mus_charge().at(imu) < 0  )       continue; // require OS
	  if(  mus_p4().at(imu).pt() < 20.0     )       continue; // pT > 20 GeV
	  if( !muonId( imu , ZMet2012_v1 )      )       continue; // looser ZMet2012_v1 selection

	  nextramu_++;

	  float mass1 = ( mus_p4().at(index1) + mus_p4().at(imu) ).mass();
	  float mass2 = ( mus_p4().at(index2) + mus_p4().at(imu) ).mass();

	  if( mass1 < 1e-4 ) cout << "ERROR! mass1 " << mass1 << endl;
	  if( mass2 < 1e-4 ) cout << "ERROR! mass2 " << mass2 << endl;

	  if( mass1 < 12.0                  ) zveto_ = 1;
	  if( mass2 < 12.0                  ) zveto_ = 1;

	  if( mass1 > 76.0 && mass1 < 106.0 ) zveto_ = 1;
	  if( mass2 > 76.0 && mass2 < 106.0 ) zveto_ = 1;

	  if( index3 > -1 ){
	  float mass3 = ( mus_p4().at(index3) + mus_p4().at(imu) ).mass();
	  if( mass3 < 1e-4 ) cout << "ERROR! mass3 " << mass2 << endl;
	  
	  if( mass3 < 12.0                  ) zveto_ = 1;
	  if( mass3 > 76.0 && mass3 < 106.0 ) zveto_ = 1;
	  
	  m3_ = mass3;
	  }

	  m1_ = mass1;
	  m2_ = mass2;

      }
	*/

	//-------------------------
	// 3-lepton stuff
	//-------------------------
      
	VofP4 goodExtraLeptons;

	if( nlep_ > 2 ){

	  // find extra leptons
	  // int   imax  = -1;
	  float maxpt = -1.;
	
	  for( int ilep = 0 ; ilep < (int)goodLeptons.size() ; ilep++ ){
		//if( dRbetweenVectors( *lep1_ , goodLeptons.at(ilep) ) < 0.00001 ) continue;
		//if( dRbetweenVectors( *lep2_ , goodLeptons.at(ilep) ) < 0.00001 ) continue;

		// skip lep1
		if( fabs( (*lep1_).pt()  - goodLeptons.at(ilep).pt()  ) < 0.001 &&
			fabs( (*lep1_).eta() - goodLeptons.at(ilep).eta() ) < 0.001 &&
			fabs( (*lep1_).phi() - goodLeptons.at(ilep).phi() ) < 0.001 ){
		  continue;
		}

		// skip lep2
		if( fabs( (*lep2_).pt()  - goodLeptons.at(ilep).pt()  ) < 0.001 &&
			fabs( (*lep2_).eta() - goodLeptons.at(ilep).eta() ) < 0.001 &&
			fabs( (*lep2_).phi() - goodLeptons.at(ilep).phi() ) < 0.001 ){
		  continue;
		}

		goodExtraLeptons.push_back( goodLeptons.at(ilep) );

		if( goodLeptons.at(ilep).pt() > maxpt ){
		  maxpt = goodLeptons.at(ilep).pt();
		  // imax = ilep;
		}

	  }

	
	  if( nlep_ != 2 + (int)goodExtraLeptons.size() ){

		cout << endl << endl;
		cout << "WARNING" << endl;
		cout << currentFile->GetTitle() << endl;
		cout << "run lumi event " << evt_run() << " " << evt_lumiBlock() << " " << evt_event() << endl;
		cout << "nleptons " << nlep_ << endl;
		cout << "extra leptons " << goodExtraLeptons.size() << endl;
	  
		for( int ilep = 0 ; ilep < (int)goodLeptons.size() ; ilep++ ){

		  cout << ilep << " " << goodLeptonIDs.at(ilep) << " " << goodLeptons.at(ilep).pt() << " " << goodLeptons.at(ilep).eta() << " " << goodLeptons.at(ilep).phi() << endl;

		  if( dRbetweenVectors( *lep1_ , goodLeptons.at(ilep) ) < 0.00001 ){
			cout << "lepton1" << endl;
			continue;
		  }
		  if( dRbetweenVectors( *lep2_ , goodLeptons.at(ilep) ) < 0.00001 ){
			cout << "lepton2" << endl;
			continue;
		  }

		  cout << "extra lepton" << endl;
	    
		}

	  }

	  sort(goodExtraLeptons.begin()  , goodExtraLeptons.end()  , sortByPt);

	  m13_ = -999;
	  m23_ = -999;
	  m14_ = -999;
	  m24_ = -999;
	  m34_ = -999;

	  if( goodExtraLeptons.size() > 0 ){
		lep3_ = &(goodExtraLeptons.at(0)); 
		id3_  = getLeptonID(goodExtraLeptons.at(0));
		m13_  = (*lep1_ + *lep3_).mass();
		m23_  = (*lep2_ + *lep3_).mass();
	  }
	  if( goodExtraLeptons.size() > 1 ){
		lep4_ = &(goodExtraLeptons.at(1)); 
		id4_  = getLeptonID(goodExtraLeptons.at(1));
		m14_  = (*lep1_ + *lep4_).mass();
		m24_  = (*lep2_ + *lep4_).mass();
		m34_  = (*lep3_ + *lep4_).mass();
	  }
	  if( goodExtraLeptons.size() > 2 ){
		lep5_ = &(goodExtraLeptons.at(2)); 
		id5_  = getLeptonID(goodExtraLeptons.at(2));
	  }
	  if( goodExtraLeptons.size() > 3 ){	  
		lep6_ = &(goodExtraLeptons.at(3)); 
		id6_  = getLeptonID(goodExtraLeptons.at(3));
	  }

	  // if( goodExtraLeptons.size() > 0 ){
	  // 	LorentzVector* pfmet_p4 = new LorentzVector( pfmet_ * cos(pfmetphi_) , pfmet_ * sin(pfmetphi_) ,      0      , pfmet_     );
		//w_ = &(*lep3_+*pfmet_p4);
	  // }
	}


	//-------------------------
	// met errors
	//-------------------------
      
	metError_         = getMetError( goodMuonIndices );
	metErrorC_        = getMetError_claudio( goodMuonIndices );

	float mom1 = hyp_ll_p4()[hypIdx].P();
	float mom2 = hyp_lt_p4()[hypIdx].P();
	if( mom2 > mom1 ){
	  mom1 = mom2;
	  mom2 = mom1;
	}

	float one_minus_cosalpha = (dilmass * dilmass) / (2 * mom1 * mom2 );
      
	dpdm_ = dilmass_ /( mom2 * one_minus_cosalpha );

	npfmuons_ = 0;
	nmatchedpfmuons_ = 0;

	for( unsigned int ipf = 0 ; ipf < pfmus_p4().size() ; ipf++ ){
	  if( pfmus_p4().at(ipf).pt()  < 20. )         continue;
	  if( fabs( pfmus_p4().at(ipf).eta() ) > 2.5 ) continue;
	  npfmuons_++;

	}
      
	if( abs( hyp_ll_id()[hypIdx] ) == 13 ){

	  int ipf_ll = mus_pfmusidx().at(hyp_ll_index().at(hypIdx));
	  if( ipf_ll >= (int)pfmus_p4().size() || ipf_ll < 0 ){
		//cout << "Error, pfmuon ll index out of range " << ipf_ll << endl;
		//printEvent();
		ptll_pf_ = -1;
	  }else{
		ptll_pf_ = pfmus_p4().at(ipf_ll).pt();
		nmatchedpfmuons_ ++;
		if( fabs( ptll_ - ptll_pf_ ) > 0.01 ){
		  //cout << "ERROR: " << ptll_ << " " << ptll_pf_ << endl;
		}
	  }

	  int muidx  = hyp_ll_index().at(hypIdx);
	  ptlltrk_   = mus_trk_p4().at(muidx).pt();
	  ptllgfit_  = mus_gfit_p4().at(muidx).pt();
	  pterrll_   = mus_ptErr().at(muidx);

	  if( !isData ){
		int mcid   = mus_mc3idx().at(muidx);
		//cout << "ll mcid " << mcid << endl;
		if( mcid >=0 && mcid < (int)genps_p4().size() ){
		  ptllgen_   = genps_p4().at(mcid).pt();
		}else{
		  //cout << "Error, ll MC index " << mcid << " size " << genps_p4().size() << endl;
		}
	  }
	}

	if( abs( hyp_lt_id()[hypIdx] ) == 13 ){

	  int ipf_lt = mus_pfmusidx()[hyp_lt_index()[hypIdx]];
	  if( ipf_lt >= (int)pfmus_p4().size() || ipf_lt < 0 ){
		ptlt_pf_ = -1;
		//cout << "Error, pfmuon lt index out of range " << ipf_lt << endl;
		//printEvent();
	  }else{
		ptlt_pf_ = pfmus_p4().at(ipf_lt).pt();
		nmatchedpfmuons_ ++;
		if( fabs( ptlt_ - ptlt_pf_ ) > 0.01 ){
		  //cout << "ERROR: " << ptlt_ << " " << ptlt_pf_ << endl;
		}
	  }

	  int muidx  = hyp_lt_index().at(hypIdx);
	  ptlttrk_   = mus_trk_p4().at(muidx).pt();
	  ptltgfit_  = mus_gfit_p4().at(muidx).pt();
	  pterrlt_   = mus_ptErr().at(muidx);

	  if( !isData ){
		int mcid   = mus_mc3idx().at(muidx);
		//cout << "lt mcid " << mcid << endl;
		if( mcid >=0 && mcid < (int)genps_p4().size() ){
		  ptltgen_   = genps_p4().at(mcid).pt();
		}else{
		  //cout << "Error, lt MC index " << mcid << " size " << genps_p4().size() <<endl;
		}
	  }

	}

	if( leptype_ == 1 && npfmuons_ >= 2 ){

	  int ipf_ll = mus_pfmusidx().at(hyp_ll_index().at(hypIdx));
	  int ipf_lt = mus_pfmusidx().at(hyp_lt_index().at(hypIdx));
	
	  //dilmasspf_ = -9999;
	
	  if( ipf_lt >= (int)pfmus_p4().size() || ipf_ll >= (int)pfmus_p4().size() ){
		cout << "Error, pfmuon out of range: SHOULDN'T GET HERE!!" << endl;
	  }else{
		//dilmasspf_ = ( pfmus_p4().at(ipf_ll) + pfmus_p4().at(ipf_lt) ).mass();
	  }
	}

	//pfjet matched to electron (ll)

	if( abs( hyp_ll_id()[hypIdx] ) == 11 ){
	  
	  float drjet_ll = 100;
	  int   ijet_ll  = -1;
	  
	  try
		{
		  for (unsigned int ijet = 0 ; ijet < pfjets_p4().size() ; ijet++) {
          
			LorentzVector vjet = pfjets_p4().at(ijet);
			LorentzVector vll  = hyp_ll_p4()[hypIdx];
          
			if( vjet.pt()  < 10  )             continue;
			if( fabs(vjet.eta()) > 3.0 )       continue;
          
			float dr = dRbetweenVectors(vjet, vll);
          
			if( dr < drjet_ll ){
			  drjet_ll    = dr;
			  ijet_ll     = ijet;
			}
		  }
      
		  if( ijet_ll >= 0 ){
			drjet_ll_   = drjet_ll;
			jetpt_ll_   = pfjets_p4().at(ijet_ll).pt();
			pfjetid_ll_ = passesPFJetID( ijet_ll ) ? 1 : 0;
		  }

		}
	  catch (exception& e)	
		{
		  cout<<e.what()<<endl;
		  cout<<"Problem before line: "<<__LINE__<<endl;
		  cout<<"problem with hyp_ll."<<endl;
		}
	}

	//pfjet matched to electron (lt)

	if( abs( hyp_lt_id()[hypIdx] ) == 11 ){

	  float drjet_lt = 100;
	  int   ijet_lt  = -1;

	  try
		{

		  for (unsigned int ijet = 0 ; ijet < pfjets_p4().size() ; ijet++) {
          
			LorentzVector vjet = pfjets_p4().at(ijet);
			LorentzVector vlt  = hyp_lt_p4()[hypIdx];
          
			if( vjet.pt()  < 10  )             continue;
			if( fabs(vjet.eta()) > 3.0 )       continue;
          
			float dr = dRbetweenVectors(vjet, vlt);
          
			if( dr < drjet_lt ){
			  drjet_lt    = dr;
			  ijet_lt     = ijet;
			}
		  }

		  if( ijet_lt >= 0 ){
			drjet_lt_   = drjet_lt;
			jetpt_lt_   = pfjets_p4().at(ijet_lt).pt();
			pfjetid_lt_ = passesPFJetID( ijet_lt ) ? 1 : 0;
		  }
		

		}
	  catch (exception& e)	
		{
		  cout<<e.what()<<endl;
		  cout<<"Problem before line: "<<__LINE__<<endl;
		  cout<<"problem with jets."<<endl;
	  }
	}      
	//---------------------
	// tcmet stuff
	//---------------------

	metStruct tcmetStruct = correctTCMETforHypMuons( hypIdx ,  
													 evt_tcmet() * cos( evt_tcmetPhi() ), 
													 evt_tcmet() * sin( evt_tcmetPhi() ), 
													 evt_tcsumet() );
        
	// out-of-the-box  tcmet stuff (corrected for hyp muons)
	tcmet_    = tcmetStruct.met;
	tcmetphi_ = tcmetStruct.metphi;
	tcsumet_  = tcmetStruct.sumet;   

	//sanity check
	//pair<float,float> p_tcmet = getMet( "tcMET"    , hypIdx);
	//float mytcmet = p_tcmet.first;
	//float mytcmet = evt_tcmet();

	//if( fabs( tcmet_ - mytcmet ) > 0.1 ) cout << "Warning! tcmet mismatch " << tcmet_ << " " << mytcmet << endl; 

	if( calculateTCMET ){
        
	  metStruct tcmetNewStruct = correctedTCMET();

	  tcmetNew_     = tcmetNewStruct.met;
	  tcmetphiNew_  = tcmetNewStruct.metphi;
	  tcsumetNew_   = tcmetNewStruct.sumet;
          

	  metStruct tcmetNewStruct_corr = correctTCMETforHypMuons( hypIdx ,  
															   tcmetNew_ * cos( tcmetphiNew_ ), 
															   tcmetNew_ * sin( tcmetphiNew_ ), 
															   tcsumetNew_ );
          
	  // Z_looper-level  tcmet stuff (corrected for hyp muons)
	  tcmetNew_    = tcmetNewStruct_corr.met;
	  tcmetphiNew_ = tcmetNewStruct_corr.metphi;
	  tcsumetNew_  = tcmetNewStruct_corr.sumet;   

	}else{
        
	  tcmetNew_    = -9999;
	  tcmetphiNew_ = -9999;
	  tcsumetNew_  = -9999;
       
	}

	nGoodVertex_   = 0;

	try
	  {

		for (size_t v = 0; v < cms2.vtxs_position().size(); ++v){
		  if(isGoodVertex(v)) nGoodVertex_++;
		}

		vtxweight_ = 1;
		if( !isData ){
		  vtxweight_ = vtxweight();
		}

		// electron energy scale stuff

		dilmasscor_  = dilmass_;
		tcmetcor_    = tcmet_;
		pfmetcor_    = pfmet_;

		if( leptype_ == 0 ){

		  if     ( fabs( etall_ ) < 1.474 && fabs( etalt_ ) < 1.479 ) ecaltype_ = 1; //EB-EB
		  else if( fabs( etall_ ) > 1.474 && fabs( etalt_ ) > 1.479 ) ecaltype_ = 2; //EE-EE
		  else                                                        ecaltype_ = 3; //EB-EE
        
		  if( isData ){

			LorentzVector vllcor;
			LorentzVector vltcor;

			float tcmetcor_x = tcmet_ * cos( tcmetphi_ );
			float tcmetcor_y = tcmet_ * sin( tcmetphi_ );

			float pfmetcor_x = pfmet_ * cos( pfmetphi_ );
			float pfmetcor_y = pfmet_ * sin( pfmetphi_ );
       
			//ll correction
			if( fabs( etall_ ) < 1.474 ){ //correct for EB electron
			  vllcor      = 1.01 * hyp_ll_p4().at(hypIdx);  
            
			  tcmetcor_x -= 0.01 * hyp_ll_p4().at(hypIdx).x();
			  tcmetcor_y -= 0.01 * hyp_ll_p4().at(hypIdx).y();

			  pfmetcor_x -= 0.01 * hyp_ll_p4().at(hypIdx).x();
			  pfmetcor_y -= 0.01 * hyp_ll_p4().at(hypIdx).y();
			}
			else{                         //correct for EE electron
			  vllcor      = 1.03 * hyp_ll_p4().at(hypIdx); 

			  tcmetcor_x -= 0.03 * hyp_ll_p4().at(hypIdx).x();
			  tcmetcor_y -= 0.03 * hyp_ll_p4().at(hypIdx).y();

			  pfmetcor_x -= 0.03 * hyp_ll_p4().at(hypIdx).x();
			  pfmetcor_y -= 0.03 * hyp_ll_p4().at(hypIdx).y();
			}

			//lt correction
			if( fabs( etalt_ ) < 1.474 ){ //correct for EB electron
			  vltcor      = 1.01 * hyp_lt_p4().at(hypIdx);  
            
			  tcmetcor_x -= 0.01 * hyp_lt_p4().at(hypIdx).x();
			  tcmetcor_y -= 0.01 * hyp_lt_p4().at(hypIdx).y();

			  pfmetcor_x -= 0.01 * hyp_lt_p4().at(hypIdx).x();
			  pfmetcor_y -= 0.01 * hyp_lt_p4().at(hypIdx).y();
			}
			else{                         //correct for EE electron
			  vltcor      = 1.03 * hyp_lt_p4().at(hypIdx); 

			  tcmetcor_x -= 0.03 * hyp_lt_p4().at(hypIdx).x();
			  tcmetcor_y -= 0.03 * hyp_lt_p4().at(hypIdx).y();

			  pfmetcor_x -= 0.03 * hyp_lt_p4().at(hypIdx).x();
			  pfmetcor_y -= 0.03 * hyp_lt_p4().at(hypIdx).y();
			}
          
			dilmasscor_  = ( vllcor + vltcor ).mass();
			tcmetcor_    = sqrt( tcmetcor_x * tcmetcor_x + tcmetcor_y * tcmetcor_y );
			pfmetcor_    = sqrt( pfmetcor_x * pfmetcor_x + pfmetcor_y * pfmetcor_y );
		  }
		}

	  }
	catch (exception& e)	
	  {
		cout<<e.what()<<endl;
		cout<<"Problem before line: "<<__LINE__<<endl;
		cout<<"problem with killed jets."<<endl;
	  }

         
	//jet stuff--------------------------------------------------------------------- 
        
	nJets_        = 0;
	nJetsUp_      = 0;
	nJetsDn_      = 0;
	sumJetPt_     = 0.;
	nJets40_      = 0;
	sumJetPt10_   = 0.;
	nbtags_       = 0;
	nbm_          = 0;
	nbl_          = 0;
	nJetsOld_     = 0;
	ht30_         = 0.0;
	ht40_         = 0.0;
	nbcsvm_       = 0;
	nbcsvl_       = 0;
	nbcsvlm_      = 0;
	nbcsvt_       = 0;
	njets40up_    = 0;
	njets40dn_    = 0;
	ht40up_       = 0.0;
	ht40dn_       = 0.0;

	LorentzVector jetSystem(0.,0.,0.,0.);        
	float maxcosdphi  = -99;
	//int   imaxcosdphi = -1;
	int   imaxjet     = -1;
	float maxpt       = -1;

	failjetid_ =  0;
	maxemf_    = -1;


	// //count JPT's
	// nJPT_ = 0;

	// for ( unsigned int ijet = 0 ; ijet < jpts_p4().size() ; ijet++ ) {
          
	//   LorentzVector vjet   = jpts_cor().at(ijet) * jpts_p4().at(ijet);
	//   LorentzVector vlt    = hyp_lt_p4().at(hypIdx);
	//   LorentzVector vll    = hyp_ll_p4().at(hypIdx);

	//   if( fabs( vjet.eta() ) > 2.5 )           continue;
	//   if( vjet.pt()  < 30.         )           continue;
	//   //if( !passesCaloJetID( vjet ) )           continue;

	//   if( generalLeptonVeto ){
	//     bool rejectJet = false;
	//     for( int ilep = 0 ; ilep < goodLeptons.size() ; ilep++ ){
	//       if( dRbetweenVectors( vjet , goodLeptons.at(ilep) ) < 0.4 ) rejectJet = true;  
	//     }
	//     if( rejectJet ) continue;
	//   }

	//   if( dRbetweenVectors(vjet, vll) < 0.4 ) continue;
	//   if( dRbetweenVectors(vjet, vlt) < 0.4 ) continue;

	//   nJPT_++;
	// } 
        
	try
	  {
		//reset killedJet vector
		for( int ilep = 0 ; ilep < (int)goodLeptons.size() ; ilep++ ){
		  killedJet.at( ilep ) = false;
		}
	  }
	catch (exception& e)	
	  {
		cout<<e.what()<<endl;
		cout<<"Problem before line: "<<__LINE__<<endl;
		cout<<"problem with killed jets."<<endl;
	  }

	VofP4 goodJets;
	VofP4 goodJetsUp;
	VofP4 goodJetsDn;
	VofP4 goodBJets;
	VofP4 goodTightBJets;

	goodJets.clear();
	goodJetsUp.clear();
	goodJetsDn.clear();
	goodBJets.clear();
	goodTightBJets.clear();

	nbvz_            = 0;
	btagweight_      = 1;    
	btagweightup_    = 1;
	npujets_         = 0;

	rho_ = cms2.evt_ww_rho_vor();

	float dmetx  = 0.0;
	float dmety  = 0.0;
	float jetptx = 0.0;
	float jetpty = 0.0;

	//-----------------------------------------------------------------------------
	// loop over pfjets pt > 30 GeV |eta| < 3.0, dR > 0.4 overlap removal, PFJetID
	//-----------------------------------------------------------------------------
	  
	  try
		{
		
		for (unsigned int ijet = 0 ; ijet < pfjets_p4().size() ; ijet++) {

		  if( fabs( pfjets_p4().at(ijet).eta() ) > 5.0 ) continue;

		  LorentzVector vjetold = pfjets_corL1FastL2L3().at(ijet) * pfjets_p4().at(ijet);

		  //---------------
		  // OFFICIAL JEC
		  //---------------

		  //---------------------------------------------------------------------------
		  // get total correction: L1FastL2L3 for MC, L1FastL2L3Residual for data
		  //---------------------------------------------------------------------------

		  jet_corrector_pfL1FastJetL2L3->setRho   ( cms2.evt_ww_rho_vor()           );
		  jet_corrector_pfL1FastJetL2L3->setJetA  ( cms2.pfjets_area().at(ijet)     );
		  jet_corrector_pfL1FastJetL2L3->setJetPt ( cms2.pfjets_p4().at(ijet).pt()  );
		  jet_corrector_pfL1FastJetL2L3->setJetEta( cms2.pfjets_p4().at(ijet).eta() );
		  double corr = jet_corrector_pfL1FastJetL2L3->getCorrection();

		  LorentzVector vjet   = corr * pfjets_p4().at(ijet);

		  // int leptonOverlap = 0;
		  // for( int ilep = 0 ; ilep < goodLeptons.size() ; ilep++ ){
		  //   if( dRbetweenVectors( vjet , goodLeptons.at(ilep) ) < 0.4 && goodLeptons.at(ilep).pt() > 20.0 ) leptonOverlap = 1;  
		  // }

		  // if( nEventsTotal <= 100 ){
		  //   if( pfjets_p4().at(ijet).pt() > 20.0 ){
		  //     printf("RelValZMM 53X:   %u\t%u\t%u\t%4.3f\t%4.3f\t%4.3f\t%4.3f\t%4.3f\t%u\t%u\t%4.3f\n", 
		  // 	   evt_run() , evt_lumiBlock(), evt_event(), pfjets_p4().at(ijet).pt() , corr , vjet.pt() , vjet.eta(), vjet.phi(), 
		  // 	   leptonOverlap , passesPFJetID(ijet) , cms2.evt_ww_rho_vor() );
		  //   }
		  // }

		  //---------------------------------------------------------------------------
		  // get JES uncertainty
		  //---------------------------------------------------------------------------
	
		  pfUncertainty->setJetEta(vjet.eta());
		  pfUncertainty->setJetPt(vjet.pt());   // here you must use the CORRECTED jet pt
		  double unc = pfUncertainty->getUncertainty(true);

		  LorentzVector vjetUp = corr * pfjets_p4().at(ijet) * ( 1 + unc );
		  LorentzVector vjetDn = corr * pfjets_p4().at(ijet) * ( 1 - unc );

		  //---------------------------------------------------------------------------
		  // store uncertainty vs. jet pt, for various bins (idiot check)
		  //---------------------------------------------------------------------------

		  float abseta = fabs( vjet.eta() );
		  if     ( abseta < 0.5                 ) hunc_eta1->Fill(vjet.pt(),unc);
		  else if( abseta > 0.5 && abseta < 1.0 ) hunc_eta2->Fill(vjet.pt(),unc);
		  else if( abseta > 1.0 && abseta < 1.5 ) hunc_eta3->Fill(vjet.pt(),unc);
		  else if( abseta > 1.5 && abseta < 2.0 ) hunc_eta4->Fill(vjet.pt(),unc);
		  else if( abseta > 2.0 && abseta < 2.5 ) hunc_eta5->Fill(vjet.pt(),unc);
		  else if( abseta > 2.5 && abseta < 3.0 ) hunc_eta6->Fill(vjet.pt(),unc);

		  //---------------------------------------------------------------------------
		  // lepton overlap removal
		  //---------------------------------------------------------------------------
          
		  LorentzVector vlt    = hyp_lt_p4().at(hypIdx);
		  LorentzVector vll    = hyp_ll_p4().at(hypIdx);
     
		  if( generalLeptonVeto ){
			bool rejectJet = false;
			for( size_t ilep = 0 ; ilep < goodLeptons.size() ; ilep++ ){
			  if( dRbetweenVectors( vjet , goodLeptons.at(ilep) ) < 0.4 && goodLeptons.at(ilep).pt() > 20.0 ) rejectJet = true;  
			}
			if( rejectJet ) continue;
		  }

		  if( dRbetweenVectors(vjet, vll) < 0.4 ) continue;
		  if( dRbetweenVectors(vjet, vlt) < 0.4 ) continue;

		  //---------------------------------------------------------------------------
		  // PFJetID
		  //---------------------------------------------------------------------------

		  if( !passesPFJetID(ijet) ){
			failjetid_ = 1;
			continue;
		  }

		  if( fabs( vjet.eta() ) > 3.0 ) continue;

		  if ( vjet.pt()   > 40. ){

			pt40jets_.push_back(vjet);
		    pt40mcfas_.push_back( pfjets_mcflavorAlgo().at(ijet) );
			pt40mcfps_.push_back( pfjets_mcflavorPhys().at(ijet) );
			pt40csvs_.push_back(  pfjets_combinedSecondaryVertexBJetTag().at(ijet) );

			nJets40_++;
			ht40_ += vjet.pt();
		  }

		  if ( vjetUp.pt()   > 40. ){
			njets40up_++;
			ht40up_ += vjet.pt();
		  }

		  if ( vjetDn.pt()   > 40. ){
			njets40dn_++;
			ht40dn_ += vjet.pt();
		  }

		  if( fabs( vjet.eta() ) > 2.5 ) continue;

		  float beta = pfjet_beta(ijet,2,0.5);

		  if( beta < 0.2 ){
			if( vjet.pt() > 30.0 ){
			  npujets_++;
			  pujets_.push_back(vjet);
			}
			continue;
		  }

		  //---------------------------------------------------------------------------
		  // jet passes: now store various quantities
		  //---------------------------------------------------------------------------

		  if( vjetold.pt() > 30 ) nJetsOld_++;

		  //--------------------
		  // OFFICIAL JEC
		  //--------------------

		  //------------------------------------------------------------------------------------------------------------
		  // MET correction quantities
		  // here we store 2 quantities:
		  // the delta(METx/y) you get by varying the jet with pT > 10 GeV by their uncertainties (dmetx,dmety
		  // the vector sum of pT > 10 GeV selected jets (jetptx,jetpty) --> use this to calculate unclustered energy
		  //------------------------------------------------------------------------------------------------------------

		  if( vjet.pt() > 10 ){
			dmetx  += vjetUp.px() - vjet.px();
			dmety  += vjetUp.py() - vjet.py();
			jetptx += vjet.px();
			jetpty += vjet.py();
		  }

		  if ( vjet.pt() > 10. ){
			sumJetPt10_ += vjet.pt();
		  }

		  if ( vjet.pt() > 15. ){
			sumJetPt_ += vjet.pt();
			jetSystem += vjet;

			float emfrac = pfjets_neutralEmE().at(ijet) / pfjets_p4().at(ijet).energy();
			if( emfrac > maxemf_ ) maxemf_ = emfrac;
		  }

		  if ( vjetUp.pt() > 20. ){
			nJetsUp_++;
			goodJetsUp.push_back( vjetUp );
		  }

		  if ( vjetDn.pt() > 20. ){
			nJetsDn_++;
			goodJetsDn.push_back( vjetDn );
		  }

		  if( vjet.pt() < 30. )                    continue;
          
		  if( vjet.pt() < 100.0 ){
			if( pfjets_trackCountingHighEffBJetTag().at(ijet) > 1.7 )  nbvz_++;
		  }

		  else{
			if( pfjets_trackCountingHighEffBJetTag().at(ijet) > 3.3 )  nbvz_++;
		  }

		  goodJets.push_back(vjet);

		  //find max jet pt
		  if( vjet.pt() > maxpt ){
			maxpt   = vjet.pt();
			imaxjet = ijet;
		  }
          
		  //find jet (anti-)aligned with tcmet
		  if( fabs( cos( tcmetphi_ - vjet.phi() ) ) > maxcosdphi ){
			maxcosdphi  = fabs( cos( tcmetphi_ - vjet.phi() ) );
			//imaxcosphi  = ijet;
			dphijetmet_ = fabs( tcmetphi_ - vjet.phi() );
			if( dphijetmet_ > TMath::Pi() ) dphijetmet_ = TMath::TwoPi() - dphijetmet_;
		  }

		  if( pfjets_trackCountingHighEffBJetTag().at(ijet) > 1.7 )  nbl_++;
		  if( pfjets_trackCountingHighEffBJetTag().at(ijet) > 3.3 )  nbm_++;

	
		  if(  pfjets_combinedSecondaryVertexBJetTag().at(ijet) > 0.244 ){
			nbcsvl_++;
		  }if( pfjets_combinedSecondaryVertexBJetTag().at(ijet) > 0.679 ){
			nbcsvm_++;
			goodBJets.push_back(vjet);
		  }
		  if( pfjets_combinedSecondaryVertexBJetTag().at(ijet) > 0.898 ){
			nbcsvt_++;
			goodTightBJets.push_back(vjet);
		  }

		  if( vjet.pt() < 100.0 ){
			if( pfjets_combinedSecondaryVertexBJetTag().at(ijet) > 0.244 )  nbcsvlm_++;
		  }

		  else{
			if( pfjets_combinedSecondaryVertexBJetTag().at(ijet) > 0.679 )  nbcsvlm_++;
		  }

		  //weight (scale factor) branches

		  if( !isData ) {

			const float pt      = pfjets_p4().at(ijet).pt();
			const float eta     = fabs( pfjets_p4().at(ijet).eta() );
			const float sfscale = 1.04; //recommendation to increase SF

			if( eta < 2.4 ) { //can't be mistagged if outside

			  //double getMisTagRate(double jet_pt, double jet_eta, string algo){
			  const float mt  = getMisTagRate            ( pt, eta, pt < 100 ? "TCHEL" : "TCHEM" );
			  const float mte = sfscale*getMisTagRate_Err( pt, eta, pt < 100 ? "TCHEL" : "TCHEM" );

			  //double getMisTagSF(double jet_pt, double jet_eta, string algo){
			  const float mtsf  = sfscale*getMisTagSF    ( pt, eta, pt < 100 ? "TCHEL" : "TCHEM" );
			  const float mtsfe = sfscale*getMisTagSF_Err( pt, eta, pt < 100 ? "TCHEL" : "TCHEM" );

			  btagweight_   *= (1-mt)/(1-mt/mtsf);                   //reset to 1 every event, so always just multiply
			  btagweightup_ *= (1-mt-mte)/(1-(mt+mte)/(mtsf+mtsfe)); //add error to mistag and SF
	    
			}
		  }

		  if ( vjet.pt()   > 30. ){
			ht30_ += vjet.pt();
			nJets_++;
		  }
		}

		//---------------
		// OFFICIAL JEC
		//---------------
      
		st30_ = ht30_ + pfmet_ + (*lep1_).pt() + (*lep2_).pt();
		st40_ = ht40_ + pfmet_ + (*lep1_).pt() + (*lep2_).pt();

		//---------------------------------------
		// now calculate METup and METdown
		//---------------------------------------

		float pfmetx = evt_pfmet() * cos( evt_pfmetPhi() );
		float pfmety = evt_pfmet() * sin( evt_pfmetPhi() );

		//--------------------------------------------------------
		// calculate unclustered energy x and y components
		// unclustered energy = -1 X ( MET + jets + leptons )
		//--------------------------------------------------------

		unclustered_x_ = -1 * ( pfmetx + jetptx );
		unclustered_y_ = -1 * ( pfmety + jetpty );

		for( size_t ilep = 0 ; ilep < goodLeptons.size() ; ilep++ ){
		  unclustered_x_ -= goodLeptons.at(ilep).px();
		  unclustered_y_ -= goodLeptons.at(ilep).py();
		}
      
		//------------------------------------------------------------------------------
		// now vary jets according to JEC uncertainty, vary unclustered energy by 10%
		//------------------------------------------------------------------------------

		float pfmetx_up = pfmetx - dmetx - 0.1 * unclustered_x_; 
		float pfmety_up = pfmety - dmety - 0.1 * unclustered_y_; 

		// pfmet DOWN
		pfmetUp_ = sqrt( pfmetx_up * pfmetx_up + pfmety_up * pfmety_up );

		float pfmetx_dn = pfmetx + dmetx + 0.1 * unclustered_x_; 
		float pfmety_dn = pfmety + dmety + 0.1 * unclustered_y_; 

		// pfmet UP
		pfmetDn_ = sqrt( pfmetx_dn * pfmetx_dn + pfmety_dn * pfmety_dn );

		unclustered_ = sqrt( pow(unclustered_x_,2) + pow(unclustered_y_,2));
       
		jetmax_pt_ = -1;

		if( imaxjet > -1 ){
		  jetmax_pt_       = pfjets_cor().at(imaxjet) * pfjets_p4().at(imaxjet).pt();
		  jetmax_dphimet_  = deltaPhi( pfjets_p4().at(imaxjet).phi() , tcmetphi_);
		}

		vecJetPt_ = jetSystem.pt();

	  }
	catch (exception& e)	
	  {
		cout<<e.what()<<endl;
		cout<<"Problem before line: "<<__LINE__<<endl;
		cout<<"problem with the jets."<<endl;
	  }

	//-------------------------------------------------------------
	// variables for lljj mass bump
	//-------------------------------------------------------------
try
  {
	sort(goodJets.begin()    , goodJets.end()    , sortByPt);
	sort(goodJetsUp.begin()  , goodJetsUp.end()  , sortByPt);
	sort(goodJetsDn.begin()  , goodJetsDn.end()  , sortByPt);
	sort(goodBJets.begin()   , goodBJets.end()   , sortByPt);

	if( goodJets.size()  > 0 ){
	  jet1_       = &(goodJets.at(0));
	  int jetidx1 = getJetIndex( goodJets.at(0) , jet_corrector_pfL1FastJetL2L3 );
	  tche1_      = pfjets_trackCountingHighEffBJetTag().at(jetidx1);
	  csv1_       = pfjets_combinedSecondaryVertexBJetTag().at(jetidx1);
	  jetunc1_    = getJetUnc( jet1_->pt(), jet1_->eta(), pfUncertainty );
	  jetgenb1_   = isOverlap( *jet1_, genbquarks, 0.4 );
	  jet1beta1_01_  = pfjet_beta(jetidx1,1,0.1);
	  jet1beta2_01_  = pfjet_beta(jetidx1,2,0.1);
	  jet1beta1_05_  = pfjet_beta(jetidx1,1,0.5);
	  jet1beta2_05_  = pfjet_beta(jetidx1,2,0.5);
	  jet1beta1_10_  = pfjet_beta(jetidx1,1,1.0);
	  jet1beta2_10_  = pfjet_beta(jetidx1,2,1.0);
	  jet1flav_      = isGenQGLMatched ( goodJets.at(0) , isData );
	  jet1drgen_     = dRGenJet ( goodJets.at(0) , isData );
	  if (!isData) {
		jet1mcfa_ = pfjets_mcflavorAlgo().at(jetidx1);
		jet1mcfp_ = pfjets_mcflavorPhys().at(jetidx1);
	  }
	}
	if( goodJets.size()  > 1 ){
	  jet2_       = &(goodJets.at(1));
	  int jetidx2 = getJetIndex( goodJets.at(1) , jet_corrector_pfL1FastJetL2L3 );
	  tche2_      = pfjets_trackCountingHighEffBJetTag().at(jetidx2);
	  csv2_       = pfjets_combinedSecondaryVertexBJetTag().at(jetidx2);
	  jetunc2_    = getJetUnc( jet2_->pt(), jet2_->eta(), pfUncertainty );
	  jetgenb2_   = isOverlap( *jet2_, genbquarks, 0.4 );
	  jet2beta1_01_  = pfjet_beta(jetidx2,1,0.1);
	  jet2beta2_01_  = pfjet_beta(jetidx2,2,0.1);
	  jet2beta1_05_  = pfjet_beta(jetidx2,1,0.5);
	  jet2beta2_05_  = pfjet_beta(jetidx2,2,0.5);
	  jet2beta1_10_  = pfjet_beta(jetidx2,1,1.0);
	  jet2beta2_10_  = pfjet_beta(jetidx2,2,1.0);
	  jet2flav_      = isGenQGLMatched ( goodJets.at(1) , isData );
	  jet2drgen_     = dRGenJet ( goodJets.at(1) , isData );
	  if (!isData) {
		jet2mcfa_ = pfjets_mcflavorAlgo().at(jetidx2);
		jet2mcfp_ = pfjets_mcflavorPhys().at(jetidx2);
	  }
	}
	if( goodJets.size()  > 2 ){
	  jet3_       = &(goodJets.at(2));
	  int jetidx3 = getJetIndex( goodJets.at(2) , jet_corrector_pfL1FastJetL2L3 );
	  tche3_      = pfjets_trackCountingHighEffBJetTag().at(jetidx3);
	  csv3_       = pfjets_combinedSecondaryVertexBJetTag().at(jetidx3);
	  jetunc3_    = getJetUnc( jet3_->pt(), jet3_->eta(), pfUncertainty );
	  jetgenb3_   = isOverlap( *jet3_, genbquarks, 0.4 );
	  jet3beta1_01_  = pfjet_beta(jetidx3,1,0.1);
	  jet3beta2_01_  = pfjet_beta(jetidx3,2,0.1);
	  jet3beta1_05_  = pfjet_beta(jetidx3,1,0.5);
	  jet3beta2_05_  = pfjet_beta(jetidx3,2,0.5);
	  jet3beta1_10_  = pfjet_beta(jetidx3,1,1.0);
	  jet3beta2_10_  = pfjet_beta(jetidx3,2,1.0);
	  jet3flav_      = isGenQGLMatched ( goodJets.at(2) , isData );
	  jet3drgen_     = dRGenJet ( goodJets.at(2) , isData );
	  if (!isData) {
		jet3mcfa_ = pfjets_mcflavorAlgo().at(jetidx3);
		jet3mcfp_ = pfjets_mcflavorPhys().at(jetidx3);
	  }
	}
	if( goodJets.size()  > 3 ){
	  jet4_       = &(goodJets.at(3));
	  int jetidx4 = getJetIndex( goodJets.at(3) , jet_corrector_pfL1FastJetL2L3 );
	  tche4_      = pfjets_trackCountingHighEffBJetTag().at(jetidx4);
	  csv4_       = pfjets_combinedSecondaryVertexBJetTag().at(jetidx4);
	  jetunc4_    = getJetUnc( jet4_->pt(), jet4_->eta(), pfUncertainty );
	  jetgenb4_   = isOverlap( *jet4_, genbquarks, 0.4 );
	  jet4beta1_01_  = pfjet_beta(jetidx4,1,0.1);
	  jet4beta2_01_  = pfjet_beta(jetidx4,2,0.1);
	  jet4beta1_05_  = pfjet_beta(jetidx4,1,0.5);
	  jet4beta2_05_  = pfjet_beta(jetidx4,2,0.5);
	  jet4beta1_10_  = pfjet_beta(jetidx4,1,1.0);
	  jet4beta2_10_  = pfjet_beta(jetidx4,2,1.0);
	  jet4flav_      = isGenQGLMatched ( goodJets.at(3) , isData );
	  jet4drgen_     = dRGenJet ( goodJets.at(3) , isData );
	  if (!isData) {
		jet4mcfa_ = pfjets_mcflavorAlgo().at(jetidx4);
		jet4mcfp_ = pfjets_mcflavorPhys().at(jetidx4);
	  }
	}

	  }
	catch (exception& e)	
	  {
		cout<<e.what()<<endl;
		cout<<"Problem before line: "<<__LINE__<<endl;
		cout<<"problem with the jet vars for jets 1-4."<<endl;
	  }

try
  {
	if( goodJets.size()  > 4 ){
	  jet5_       = &(goodJets.at(4));
	  int jetidx5 = getJetIndex( goodJets.at(4) , jet_corrector_pfL1FastJetL2L3 );
	  tche5_      = pfjets_trackCountingHighEffBJetTag().at(jetidx5);
	  csv5_       = pfjets_combinedSecondaryVertexBJetTag().at(jetidx5);
	  jetunc5_    = getJetUnc( jet5_->pt(), jet5_->eta(), pfUncertainty );
	  jetgenb5_   = isOverlap( *jet5_, genbquarks, 0.4 );
	}
	if( goodJets.size()  > 5 ){
	  jet6_       = &(goodJets.at(5));
	  int jetidx6 = getJetIndex( goodJets.at(5) , jet_corrector_pfL1FastJetL2L3 );
	  tche6_      = pfjets_trackCountingHighEffBJetTag().at(jetidx6);
	  csv6_       = pfjets_combinedSecondaryVertexBJetTag().at(jetidx6);
	  jetunc6_    = getJetUnc( jet6_->pt(), jet6_->eta(), pfUncertainty );
	  jetgenb6_   = isOverlap( *jet6_, genbquarks, 0.4 );
	}
	if( goodJets.size()  > 6 ){
	  jet7_       = &(goodJets.at(6));
	  int jetidx7 = getJetIndex( goodJets.at(6) , jet_corrector_pfL1FastJetL2L3 );
	  tche7_      = pfjets_trackCountingHighEffBJetTag().at(jetidx7);
	  csv7_       = pfjets_combinedSecondaryVertexBJetTag().at(jetidx7);
	  jetunc7_    = getJetUnc( jet7_->pt(), jet7_->eta(), pfUncertainty );
	  jetgenb7_   = isOverlap( *jet7_, genbquarks, 0.4 );
	}
	if( goodJets.size()  > 7 ){
	  jet8_       = &(goodJets.at(7));
	  int jetidx8 = getJetIndex( goodJets.at(7) , jet_corrector_pfL1FastJetL2L3 );
	  tche8_      = pfjets_trackCountingHighEffBJetTag().at(jetidx8);
	  csv8_       = pfjets_combinedSecondaryVertexBJetTag().at(jetidx8);
	  jetunc8_    = getJetUnc( jet8_->pt(), jet8_->eta(), pfUncertainty );
	  jetgenb8_   = isOverlap( *jet8_, genbquarks, 0.4 );
	}

	  }
	catch (exception& e)	
	  {
		cout<<e.what()<<endl;
		cout<<"Problem before line: "<<__LINE__<<endl;
		cout<<"problem with the jet vars for jets 5-8."<<endl;
	  }

try
  {
	// if( goodJets.size()  > 0 ) jet1_   = &(goodJets.at(0));
	// if( goodJets.size()  > 1 ) jet2_   = &(goodJets.at(1));
	// if( goodJets.size()  > 2 ) jet3_   = &(goodJets.at(2));
	// if( goodJets.size()  > 3 ) jet4_   = &(goodJets.at(3));
	// if( goodJets.size()  > 4 ) jet5_   = &(goodJets.at(4));
	// if( goodJets.size()  > 5 ) jet6_   = &(goodJets.at(5));
	// if( goodJets.size()  > 6 ) jet7_   = &(goodJets.at(6));
	// if( goodJets.size()  > 7 ) jet8_   = &(goodJets.at(7));

	// check for subtreshold jets that pass pt cut with JEC variation
	// -- save up to 2
	int nsubthresh = int(goodJetsUp.size() - goodJets.size());
	if (nsubthresh > 0) {
	  // loop over goodJetsUp to find the highest pt jets NOT in goodJets
	  int nfoundsubthresh = 0;
	  for (unsigned int iup=0; iup<goodJetsUp.size(); ++iup) {
		if (isOverlap(goodJetsUp.at(iup), goodJets, 0.1)) continue;
		if (nfoundsubthresh == 0) subthreshjetup1_ = &(goodJetsUp.at(iup));
		else if (nfoundsubthresh == 1) subthreshjetup2_ = &(goodJetsUp.at(iup));
		++nfoundsubthresh;
		if ( (nfoundsubthresh == nsubthresh) || (nfoundsubthresh > 1) ) break;
	  }
	}

	if( goodBJets.size() > 0 ) bjet1_  = &(goodBJets.at(0));
	if( goodBJets.size() > 1 ) bjet2_  = &(goodBJets.at(1));
	if( goodBJets.size() > 2 ) bjet3_  = &(goodBJets.at(2));
	if( goodBJets.size() > 3 ) bjet4_  = &(goodBJets.at(3));

	mjj_ = -1;

	if( goodJets.size() >= 2 ){
	  lljj_     = ( *lep1_ + *lep2_ + *jet1_ + *jet2_ ).mass();
	  jj_       = ( *jet1_ + *jet2_          ).mass();
	  l1jj_     = ( *lep1_ + *jet1_ + *jet2_ ).mass();
	  l2jj_     = ( *lep2_ + *jet1_ + *jet2_ ).mass();
	  j1ll_     = ( *jet1_ + *lep1_ + *lep2_ ).mass();
	  j2ll_     = ( *jet2_ + *lep1_ + *lep2_ ).mass();
	  l1j1_     = ( *lep1_ + *jet1_          ).mass();
	  l2j2_     = ( *lep2_ + *jet2_          ).mass();
	  l1j2_     = ( *lep1_ + *jet2_          ).mass();
	  l2j1_     = ( *lep2_ + *jet1_          ).mass();
	  mjj_      = ( *jet1_ + *jet2_          ).mass();
	}
      
	mjjup_ = -1;
	mjjdn_ = -1;

	if( goodJetsUp.size() >= 2 ) mjjup_ = ( goodJetsUp.at(0) + goodJetsUp.at(1) ).mass();
	if( goodJetsDn.size() >= 2 ) mjjdn_ = ( goodJetsDn.at(0) + goodJetsDn.at(1) ).mass();

	mbb_ = -1;
	if( goodBJets.size() > 1 ) mbb_ = ( *bjet1_ + *bjet2_ ).mass();

	  }
	catch (exception& e)	
	  {
		cout<<e.what()<<endl;
		cout<<"Problem before line: "<<__LINE__<<endl;
		cout<<"problem with the rest of the jet vars."<<endl;
	  }

	//-------------------------
	// M(l,b) variables
	//-------------------------
	try
	  {
		if( goodBJets.size() > 0 ){
		  mlb1_    = 9999;
		  mlb2_    = 9999;
		  drblmin_ = 9999;

		  for( size_t i = 0 ; i < goodBJets.size() ; ++i ){
			float m1 = ( *lep1_ + goodBJets.at(i) ).mass();
			float m2 = ( *lep2_ + goodBJets.at(i) ).mass();

			if( m1 < mlb1_ ) mlb1_ = m1;
			if( m2 < mlb2_ ) mlb2_ = m2;

			float dr1 = dRbetweenVectors( *lep1_ , goodBJets.at(i) );
			float dr2 = dRbetweenVectors( *lep2_ , goodBJets.at(i) );

			if( dr1 < drblmin_ ) drblmin_ = dr1;
			if( dr2 < drblmin_ ) drblmin_ = dr2;

		  }
		}

		else{
		  mlb1_    = -1;
		  mlb2_    = -1;
		  drblmin_ = -1;
		}

		if( goodBJets.size() == 2 ){
		  float m10 = ( *lep1_ + goodBJets.at(0) ).mass();
		  float m11 = ( *lep1_ + goodBJets.at(1) ).mass();
		  float m20 = ( *lep2_ + goodBJets.at(0) ).mass();
		  float m21 = ( *lep2_ + goodBJets.at(1) ).mass();

		  mlbmin_ = m10;
		  if( m11 < mlbmin_ ) mlbmin_ = m11;
		  if( m20 < mlbmin_ ) mlbmin_ = m20;
		  if( m21 < mlbmin_ ) mlbmin_ = m21;
		}

		else{
		  mlbmin_ = -1;
		}

		if( goodTightBJets.size() > 0 ){
		  mlbt1_ = 9999;
		  mlbt2_ = 9999;

		  for( size_t i = 0 ; i < goodTightBJets.size() ; ++i ){
			float m1 = ( *lep1_ + goodTightBJets.at(i) ).mass();
			float m2 = ( *lep2_ + goodTightBJets.at(i) ).mass();

			if( m1 < mlbt1_ ) mlbt1_ = m1;
			if( m2 < mlbt2_ ) mlbt2_ = m2;
		  }
		}

		else{
		  mlbt1_ = -1;
		  mlbt2_ = -1;
		}

		if( goodTightBJets.size() == 2 ){
		  float m10 = ( *lep1_ + goodTightBJets.at(0) ).mass();
		  float m11 = ( *lep1_ + goodTightBJets.at(1) ).mass();
		  float m20 = ( *lep2_ + goodTightBJets.at(0) ).mass();
		  float m21 = ( *lep2_ + goodTightBJets.at(1) ).mass();

		  mlbtmin_ = m10;
		  if( m11 < mlbtmin_ ) mlbtmin_ = m11;
		  if( m20 < mlbtmin_ ) mlbtmin_ = m20;
		  if( m21 < mlbtmin_ ) mlbtmin_ = m21;
		}

		else{
		  mlbtmin_ = -1;
		}
      
		mt2_ = MT2( evt_pfmet() , evt_pfmetPhi() , hyp_ll_p4().at(hypIdx) , hyp_lt_p4().at(hypIdx) , 0. , false );
		mt2j_ = -1;

		if( nJets_ > 1){
		  mt2j_ = MT2J( evt_pfmet() , evt_pfmetPhi() , hyp_ll_p4().at(hypIdx) , hyp_lt_p4().at(hypIdx), goodJets );
		}

	  }
	catch (exception& e)	
	  {
		cout<<e.what()<<endl;
		cout<<"problem with the mt2j or mlb vars."<<endl;
	  }
	
	//---------------------------------------------
	// Look for gen Z, ttbar in relevant samples
	//---------------------------------------------
	try
	  {

		if ( !isData && (TString(prefix).Contains("zjets") || TString(prefix).Contains("ttbar")) ) {
		  int ntops = 0;
		  for (unsigned int igen = 0; igen < cms2.genps_id().size(); ++igen) {
			int id = cms2.genps_id().at(igen);
			if ( (id == 23) && TString(prefix).Contains("zjets") ) {
			  genz_ = &(cms2.genps_p4().at(igen));
			  break;
			} else if ( (id == 6) && TString(prefix).Contains("ttbar") ) {
			  gent_ = &(cms2.genps_p4().at(igen));
			  ++ntops;
			} else if ( (id == -6) && TString(prefix).Contains("ttbar") ) {
			  gentbar_ = &(cms2.genps_p4().at(igen));
			  ++ntops;
			}
		  } // loop over genps

		  if (TString(prefix).Contains("ttbar")) {
			// make sure we only found 2 tops
			if (ntops == 2 && gent_ && gentbar_) {
			  LorentzVector ttpair = *gent_ + *gentbar_;
			  genttbar_ = &ttpair;
			} else {
			  cout << __FILE__ << " " << __LINE__ << " ERROR! found " << ntops << " tops instead of 2!" << endl;
			}
		  }
		} // if zjets or ttbar
  
		if( cms2.evt_isRealData() ) {
		  ecallaser_ = passECALLaserFilter();
		  csc_       = passCSCBeamHaloFilter();
		  hbhe_      = cms2.evt_hbheFilter();
		  hcallaser_ = passHCALLaserFilter();
		  ecaltp_    = passECALDeadCellFilter();
		  trkfail_   = passTrackingFailureFilter();
		  eebadsc_   = passeeBadScFilter();
		  hbhenew_   = passHBHEFilter();
		}else{
		  ecallaser_ = 1;
		  csc_       = 1;
		  hbhe_      = 1;
		  hcallaser_ = 1;
		  ecaltp_    = 1;
		  trkfail_   = 1;
		  eebadsc_   = 1;
		  hbhenew_   = 1;
		}

		//-------------------------
		// Taus
		//-------------------------

		Int_t indexTauMax = -1;
		Float_t ptTauMax = 0.0;

		for (unsigned int itau=0; itau < taus_pf_p4().size(); itau++) {
		  if(taus_pf_p4().at(itau).pt()<20) continue;
		  // bool  isLeadLepton = 
		  if( dRbetweenVectors( taus_pf_p4().at(itau) , *lep1_ ) < 0.4 ) continue;
		  if( dRbetweenVectors( taus_pf_p4().at(itau) , *lep2_ ) < 0.4 ) continue;
		  // if(isLeadLepton) continue;
		  if(!taus_pf_byDecayModeFinding().at(itau)) continue;
	  
		  // isolation Medium ; pt > 20    
		  if(taus_pf_byMediumIsolationMVA2().at(itau)) {
			if(taus_pf_p4().at(itau).pt()>ptTauMax) {
			  ptTauMax = taus_pf_p4().at(itau).pt();
			  indexTauMax = itau;
			}	
		  }
	  
		  if(indexTauMax!=-1) {
			if(taus_pf_pfcandIndicies().at(indexTauMax).size()>0) {
			  int leadingPtCand_index=(taus_pf_pfcandIndicies().at(indexTauMax)).at(0);
			  pfTau_leadPtcand_= &(pfcands_p4().at(leadingPtCand_index));
			  pfTau_leadPtcandID_= pfcands_particleId().at(leadingPtCand_index);
			}
		  }
		}

	  }
	catch (exception& e)	
	  {
		cout<<e.what()<<endl;
		cout<<"problem with the tau or mlbmetfilter vars."<<endl;
	  }

	//-------------------------
	// fill histos and ntuple
	//-------------------------
	try
	  {
		FillBabyNtuple();
	  }
	catch (exception& e)	
	  {
		cout<<e.what()<<endl;
		cout<<"problem with FillBabyNtuple()."<<endl;
	  }

	//-----------------------
	//signal region selection
	//-----------------------

	if( dilmass_ < 81. || dilmass_ > 101. )    continue;
	if( PassGenSelection( isData ) > 60. )   nRecoPass_cut[3]++;

	if( leptype_ == 2 )                        continue;
	if( PassGenSelection( isData ) > 60. )   nRecoPass_cut[4]++;

	if( nJets_ < 2 )                           continue;
	if( PassGenSelection( isData ) > 60. )   nRecoPass_cut[5]++;

	if( pfmet_ < 60 )                          continue;
	if( PassGenSelection( isData ) > 60. )   nRecoPass_cut[6]++;

	if( leptype_ == 0 ){
	  if( jetpt_ll_ - ptll_ < -5  ) continue; 
	  if( jetpt_lt_ - ptlt_ < -5  ) continue; 
	}
	if( PassGenSelection( isData ) > 60. )   nRecoPass_cut[7]++;
      

	if( pfmet_ > 60 ){
	  if( PassGenSelection( isData ) > 60. ) nRecoPassGenPass60++;
	  else                           nRecoPassGenFail60++;
	}
	if( pfmet_ > 120 ){
	  if( PassGenSelection( isData ) > 120. ) nRecoPassGenPass120++;
	  else                            nRecoPassGenFail120++;
	}
 
	if( nHypPass > 1 && isData ) 
	  cout << "Found " << nHypPass << " hypotheses passing selection" << endl;


  } // end loop over events

  delete f;
} // end loop over files

if( nSkip_els_conv_dist > 0 ){
  cout << "Skipped " << nSkip_els_conv_dist << " events due to nan in els_conv_dist branch" << endl;
 }

if (nEventsChain != nEventsTotal)
  std::cout << "ERROR: number of events from files is not equal to total number of events" << std::endl;

cout << endl;
cout << "-------------------------------------------------------" << endl;
cout << "Sample : " << prefix << " selected events:" << endl;
cout << "ee     : " << nGoodEl << endl;
cout << "mm     : " << nGoodMu << endl;
cout << "em     : " << nGoodEM << endl;
cout << "-------------------------------------------------------" << endl;
cout << endl;

CloseBabyNtuple();

already_seen.clear();

// make histos rootfile
TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
rootdir->cd();
 saveHist( Form("../output/%s/%s.root", iter.c_str() , prefix ) );
deleteHistos();
  
} // end ScanChain

//--------------------------------------------------------------------

float Z_looper::deltaPhi( float phi1 , float phi2){
  float dphi = fabs( phi1 - phi2 );
  if( dphi > TMath::Pi() ) dphi = TMath::TwoPi() - dphi;
  return dphi;
}

//--------------------------------------------------------------------

float Z_looper::leptonD0(const int id, const int idx)
{
    const int vtxidx = firstGoodVertex();
    if (vtxidx < 0)
    {
        std::cout << "[dy::leptonD0] WARNING - first good vertex index < 0.  Returning bogus value 999999" << std::endl;
        return 999999.0;
    }
    if (abs(id)==13)
    {
        const int trkidx = tas::mus_trkidx().at(idx);
        if (trkidx >= 0)
        {
            return trks_d0_pv(trkidx, vtxidx).first;
        }
    }
    else if (abs(id)==11)
    {
        const int gsfidx = tas::els_gsftrkidx().at(idx);
        if (gsfidx >= 0) 
        {
            return gsftrks_d0_pv(gsfidx, vtxidx).first;
        }
    }

    // return bogus for non electon/muon
    return -999999.0;
}

//--------------------------------------------------------------------

float Z_looper::leptonDz(const int id, const int idx)
{
    const int vtxidx = firstGoodVertex();
    if (vtxidx < 0)
    {
        std::cout << "[dy::leptonDz] WARNING - first good vertex index < 0.  Returning bogus value 999999" << std::endl;
        return 999999.0;
    }
    if (abs(id)==13)
    {
        const int trkidx = tas::mus_trkidx().at(idx);
        if (trkidx >= 0)
        {
            return trks_dz_pv(trkidx, vtxidx).first;
        }
    }
    else if (abs(id)==11)
    {
        const int gsfidx = tas::els_gsftrkidx().at(idx);
        if (gsfidx >= 0)
        {
            return gsftrks_dz_pv(gsfidx, vtxidx).first;
        }
    }

    // return bogus for non electon/muon
    return -999999.0;
}

//--------------------------------------------------------------------

void Z_looper::fillUnderOverFlow(TH1F *h1, float value, float weight){

  float min = h1->GetXaxis()->GetXmin();
  float max = h1->GetXaxis()->GetXmax();

  if (value > max) value = h1->GetBinCenter(h1->GetNbinsX());
  if (value < min) value = h1->GetBinCenter(1);

  h1->Fill(value, weight);

}

//--------------------------------------------------------------------

void Z_looper::InitBabyNtuple (){

  pujets_.clear();
  pt40jets_.clear();
  pt40csvs_.clear();

  pt40mcfas_.clear();
  pt40mcfps_.clear();

  jet1flav_     = -9999;
  jet2flav_     = -9999;
  jet3flav_     = -9999;
  jet4flav_     = -9999;

  ngenbs_ = 0;
  
  jet1drgen_    = -9999.0;
  jet2drgen_    = -9999.0;
  jet3drgen_    = -9999.0;
  jet4drgen_    = -9999.0;

  jet1beta1_01_ = -1;
  jet2beta1_01_ = -1;
  jet3beta1_01_ = -1;
  jet4beta1_01_ = -1;

  jet1beta2_01_ = -1;
  jet2beta2_01_ = -1;
  jet3beta2_01_ = -1;
  jet4beta2_01_ = -1;

  jet1beta1_05_ = -1;
  jet2beta1_05_ = -1;
  jet3beta1_05_ = -1;
  jet4beta1_05_ = -1;

  jet1beta2_05_ = -1;
  jet2beta2_05_ = -1;
  jet3beta2_05_ = -1;
  jet4beta2_05_ = -1;

  jet1beta1_10_ = -1;
  jet2beta1_10_ = -1;
  jet3beta1_10_ = -1;
  jet4beta1_10_ = -1;

  jet1beta2_10_ = -1;
  jet2beta2_10_ = -1;
  jet3beta2_10_ = -1;
  jet4beta2_10_ = -1;

  vtxidx_    = -1;

  //electron-matched jet stuff
  drjet_ll_       = -999999.;
  jetpt_ll_       = -999999.;
  pfjetid_ll_     = -999999;
  drjet_lt_       = -999999.;
  jetpt_lt_       = -999999.;
  pfjetid_lt_     = -999999;

  // event stuff
  run_          = -999999;
  goodrun_      = -999999;
  memset(dataset_, '\0', 500);
  lumi_         = -999999;
  event_        = -999999;
  weight_       = -999999.;
  vtxweight_    = -999999.;
  pthat_        = -999999.;
  nGoodVertex_  = -999999;
  leptype_      = -999999;
  ecaltype_     = -999999;

  // genmet stuff
  genmet_     = -999999.;
  genmetphi_  = -999999.;
  gensumet_   = -999999.;

  // pfmet stuff
  pfmet_     = -999999.;
  pfmetphi_  = -999999.;
  pfsumet_   = -999999.;

  //pfmuon stuff
  npfmuons_         = -999999;
  nmatchedpfmuons_  = -999999;
  ptll_pf_   =  -1.;
  ptlt_pf_   =  -1.;

  // calomet stuff
  met_          = -999999.;
  metphi_       = -999999.;
  sumet_        = -999999.;

  // muon-corrected calomet stuff
  mumet_        = -999999.;
  mumetphi_     = -999999.;
  musumet_      = -999999.;

  // calomet stuff
  mujesmet_     = -999999.;
  mujesmetphi_  = -999999.;
  mujessumet_   = -999999.;

  // tcmet stuff
  dphixmet_     = -999999.;
  metPar_       = -999999.;
  metPerp_      = -999999.;

  tcmet_        = -999999.;
  tcmetcor_     = -999999.;
  pfmetcor_     = -999999.;
  tcmetphi_     = -999999.;
  tcsumet_      = -999999.;

  tcmetNew_     = -999999.;
  tcsumetNew_   = -999999.;
  tcmetphiNew_  = -999999.;

  nJets_        = -999999;
  sumJetPt_     = -999999;
  vecJetPt_     = -999999;
  nJets40_      = -999999;
  sumJetPt10_   = -999999;
  ht30_         = -999999.;
  ht40_         = -999999.;
  nbcsvl_       = -999999;
  nbcsvlm_      = -999999;
  nbcsvm_       = -999999;
  nbcsvt_       = -999999;
  jzb_          = -999999.;

  nbtags_       = -999999;
  nbl_          = -999999;
  nbm_          = -999999;
  dphijetmet_   = -999999;

  //leading jet stuff
  jetmax_pt_        = -999999;
  jetmax_dphimet_   = -999999;

  metError_         = -999999;
  metErrorC_        = -999999;
  dpdm_             = -999999;

  //Z stuff
  passz_           = -999999;
  pdgid_           = -999999;
  ptll_            = -999999;
  ptlt_            = -999999;
  pterrll_         = -999999;
  pterrlt_         = -999999;
  ptlltrk_         = -999999;
  ptllgen_         = -999999;
  ptltgen_         = -999999;
  ptlttrk_         = -999999;
  ptllgfit_        = -999999;
  ptltgfit_        = -999999;
  idll_            = -999999;
  idlt_            = -999999;
  etall_           = -999999;
  etalt_           = -999999;
  phill_           = -999999;
  philt_           = -999999;
  dilmass_         = -999999.;
  dilmasspf_       = -999999.;
  dilmasscor_      = -999999.;
  dilpt_           = -999999.;
  flagll_          = -999999;
  flaglt_          = -999999;
  failjetid_       = -999999;
  maxemf_          = -999999.;
  id1_             = -99;
  id2_             = -99;
  id3_             = -99;
  id4_             = -99;
  id5_             = -99;
  id6_             = -99;

  bptx_        =  -999999;
  bsc_         =  -999999;
  beamhalo_    =  -999999;
  goodvtx_     =  -999999;
  goodtrks_    =  -999999;

  lljj_		= -1;
  jj_		= -1;
  l1jj_		= -1;
  l2jj_		= -1;
  j1ll_		= -1;
  j2ll_		= -1;
  l1j1_		= -1;
  l2j2_		= -1;
  l1j2_		= -1;
  l2j1_		= -1;
  dilep_	= 0;
  dileppf_	= 0;
  genlep1_		= 0;
  genlep2_		= 0;
  gennu1_		= 0;
  gennu2_		= 0;

  pfTau_leadPtcand_ = 0;
  pfTau_leadPtcandID_ = -1;

  jet1_		= 0;
  jet2_		= 0;
  jet3_		= 0;
  jet4_		= 0;
  jet5_		= 0;
  jet6_		= 0;
  jet7_		= 0;
  jet8_		= 0;
  subthreshjetup1_ = 0;
  subthreshjetup2_ = 0;
  bjet1_	= 0;
  bjet2_	= 0;
  bjet3_   	= 0;
  bjet4_   	= 0;
  genbquark1_	= 0;
  genbquark2_	= 0;
  genbquark3_  	= 0;
  genbquark4_  	= 0;
  genchi30p4_	= 0;
  genchi20p4_	= 0;
  genchi10p4_3_  	= 0;
  genchi10p4_2_  	= 0;
  lep1_		= 0;
  lep2_		= 0;
  pflep1_	= 0;
  pflep2_	= 0;
  lep3_         = 0;
  lep4_         = 0;
  lep5_         = 0;
  lep6_         = 0;
  w_            = 0;
  genz_         = 0;
  gent_         = 0;
  gentbar_      = 0;
  genttbar_     = 0;

  lep1iso_		= -999.9;
  lep2iso_		= -999.9;
  lep1D0_		= -999.9;
  lep2D0_		= -999.9;
  lep1Dz_		= -999.9;
  lep2Dz_		= -999.9;

  jet1mcfa_		= -1;
  jet2mcfa_		= -1;
  jet3mcfa_		= -1;
  jet4mcfa_		= -1;

  jet1mcfp_		= -1;
  jet2mcfp_		= -1;
  jet3mcfp_		= -1;
  jet4mcfp_		= -1;

  tche1_   = -1;
  tche2_   = -1;
  tche3_   = -1;
  tche4_   = -1;
  tche5_   = -1;
  tche6_   = -1;
  tche7_   = -1;
  tche8_   = -1;

  csv1_   = -99;
  csv2_   = -99;
  csv3_   = -99;
  csv4_   = -99;
  csv5_   = -99;
  csv6_   = -99;
  csv7_   = -99;
  csv8_   = -99;

  jetunc1_   = -1;
  jetunc2_   = -1;
  jetunc3_   = -1;
  jetunc4_   = -1;
  jetunc5_   = -1;
  jetunc6_   = -1;
  jetunc7_   = -1;
  jetunc8_   = -1;

  jetgenb1_   = -1;
  jetgenb2_   = -1;
  jetgenb3_   = -1;
  jetgenb4_   = -1;
  jetgenb5_   = -1;
  jetgenb6_   = -1;
  jetgenb7_   = -1;
  jetgenb8_   = -1;

  mllgen_  = -999.;
  qscale_  = -999.;
}

//--------------------------------------------------------------------

void Z_looper::bookHistos(){

  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  rootdir->cd();

  vector <string> pttitle;
  pttitle.push_back("all jets");
  pttitle.push_back("1 jet");
  pttitle.push_back("2 jet");
  pttitle.push_back("3 jet");
  pttitle.push_back("#geq 4 jet");
  // char* pttitle[5]={"all jets","1 jet","2 jet","3 jet","#geq 4 jet"};

  for( int iJ = 0 ; iJ < 5 ; iJ++ ){
    hptz[iJ] = new TH1F(Form("hptz_%i",iJ),pttitle.at(iJ).c_str(),200,0,200);
    hptz[iJ]->GetXaxis()->SetTitle("Z p_{T} (GeV)");
  }

  hunc_eta1 = new TH2F("hunc_eta1","",100,0,100,200,0,0.2);
  hunc_eta2 = new TH2F("hunc_eta2","",100,0,100,200,0,0.2);
  hunc_eta3 = new TH2F("hunc_eta3","",100,0,100,200,0,0.2);
  hunc_eta4 = new TH2F("hunc_eta4","",100,0,100,200,0,0.2);
  hunc_eta5 = new TH2F("hunc_eta5","",100,0,100,200,0,0.2);
  hunc_eta6 = new TH2F("hunc_eta6","",100,0,100,200,0,0.2);

  hunc_eta1->GetXaxis()->SetTitle("jet p_{T} [GeV]");
  hunc_eta1->GetYaxis()->SetTitle("uncertainty (|#eta| 0.0-0.5)");
  hunc_eta2->GetXaxis()->SetTitle("jet p_{T} [GeV]");
  hunc_eta2->GetYaxis()->SetTitle("uncertainty (|#eta| 0.5-1.0)");
  hunc_eta3->GetXaxis()->SetTitle("jet p_{T} [GeV]");
  hunc_eta3->GetYaxis()->SetTitle("uncertainty (|#eta| 1.0-1.5)");
  hunc_eta4->GetXaxis()->SetTitle("jet p_{T} [GeV]");
  hunc_eta4->GetYaxis()->SetTitle("uncertainty (|#eta| 1.5-2.0)");
  hunc_eta5->GetXaxis()->SetTitle("jet p_{T} [GeV]");
  hunc_eta5->GetYaxis()->SetTitle("uncertainty (|#eta| 2.0-2.5)");
  hunc_eta6->GetXaxis()->SetTitle("jet p_{T} [GeV]");
  hunc_eta6->GetYaxis()->SetTitle("uncertainty (|#eta| 2.5-3.0)");

  hgenmet_all  = new TH1F("hgenmet_all","",100,0,200);
  hgenmet_pass = new TH1F("hgenmet_pass","",100,0,200);
  hresponse    = new TProfile("hresponse","",100,0,200,0,2);

  hgenmet_all->Sumw2();
  hgenmet_pass->Sumw2();

  Int_t maxmet = 200;

  metObserved     = new TH1F("metObserved", "Observed MET",maxmet,0,maxmet);
  metPredicted    = new TH1F("metPredicted","Predicted MET",maxmet,0,maxmet);
  metObserved->Sumw2();
  metPredicted->Sumw2();

  metObserved_sf  = new TH1F("metObserved_sf", "Observed MET (SF)",maxmet,0,maxmet);
  metPredicted_sf = new TH1F("metPredicted_sf","Predicted MET (SF)",maxmet,0,maxmet);
  metObserved_sf->Sumw2();
  metPredicted_sf->Sumw2();

  metObserved_df  = new TH1F("metObserved_df", "Observed MET (DF)",maxmet,0,maxmet);
  metPredicted_df = new TH1F("metPredicted_df","Predicted MET (DF)",maxmet,0,maxmet);
  metObserved_df->Sumw2();
  metPredicted_df->Sumw2();

  metObserved_ee  = new TH1F("metObserved_ee", "Observed MET (ee)",maxmet,0,maxmet);
  metPredicted_ee = new TH1F("metPredicted_ee","Predicted MET (ee)",maxmet,0,maxmet);
  metObserved_ee->Sumw2();
  metPredicted_ee->Sumw2();

  metObserved_mm  = new TH1F("metObserved_mm", "Observed MET (#mu#mu)",maxmet,0,maxmet);
  metPredicted_mm = new TH1F("metPredicted_mm","Predicted MET (#mu#mu)",maxmet,0,maxmet);
  metObserved_mm->Sumw2();
  metPredicted_mm->Sumw2();

  metParObserved  = new TH1F("metParObserved", "Observed MET (Parallel)",1000,-maxmet,maxmet);
  metParPredicted = new TH1F("metParPredicted","Predicted MET (Parallel)",1000,-maxmet,maxmet);
  metParObserved->Sumw2();
  metParPredicted->Sumw2();

  metPerpObserved  = new TH1F("metPerpObserved", "Observed MET (Perpendicular)",maxmet,0,maxmet);
  metPerpPredicted = new TH1F("metPerpPredicted","Predicted MET (Perpendicular)",maxmet,0,maxmet);
  metPerpObserved->Sumw2();
  metPerpPredicted->Sumw2();

  // for( int iJetBin = 0 ; iJetBin < nJetBins ; iJetBin++ ){

  //   metObserved_njets[iJetBin]  = new TH1F(Form("metObserved_njets%i",iJetBin), Form("Observed MET NJets %i", iJetBin),maxmet,0,maxmet);
  //   metPredicted_njets[iJetBin] = new TH1F(Form("metPredicted_njets%i",iJetBin),Form("Predicted MET NJets %i",iJetBin),maxmet,0,maxmet);
    
  //   metObserved_njets[iJetBin] ->Sumw2();
  //   metPredicted_njets[iJetBin]->Sumw2();
  // }

  vector <string> leptype;
  leptype.push_back("ee");  
  leptype.push_back("mm");  
  leptype.push_back("em");  
  leptype.push_back("all");  
  // char* leptype[4]   = {"ee", "mm", "em", "all"};

  vector <string> jetbin;
  jetbin.push_back("0j");  
  jetbin.push_back("1j");  
  jetbin.push_back("geq2j");  
  jetbin.push_back("allj");  
  // char* jetbin[4]    = {"0j", "1j", "geq2j", "allj"};

  vector <string> leptype_title;
  leptype_title.push_back("ee");  
  leptype_title.push_back("#mu#mu");  
  leptype_title.push_back("e#mu");  
  leptype_title.push_back("all leptons");  
  // char* leptype_title[4]   = {"ee", "#mu#mu", "e#mu", "all leptons"};

  vector <string> jetbin_title;
  jetbin_title.push_back("0 jets");  
  jetbin_title.push_back("1 jet");  
  jetbin_title.push_back("#geq 2 jets");  
  jetbin_title.push_back("all jets");  
  // char* jetbin_title[4]    = {"0 jets", "1 jet", "#geq 2 jets", "all jets"};

  for (int i = 0; i < 4; i++) {
   
    hdilMass[i] = new TH1F(Form("hdilMass_%s",leptype.at(i).c_str()),  leptype_title.at(i).c_str(),   150,0,300);
    hdilMass[i]->GetXaxis()->SetTitle("M(ll) (GeV)");
 
    for (int j = 0; j < 4; j++) {

      string suffix       = Form("%s_%s", leptype.at(i).c_str(), jetbin.at(j).c_str() );
      string suffix_title = Form("%s %s", leptype_title.at(i).c_str(), jetbin_title.at(j).c_str() );
    
      htcmet[i][j]    = new TH1F(Form("htcmet_%s",suffix.c_str()),    suffix_title.c_str(), 100,0,100);
      htcmetNew[i][j] = new TH1F(Form("htcmetNew_%s",suffix.c_str()), suffix_title.c_str(), 100,0,100);
      hpfmet[i][j]    = new TH1F(Form("hpfmet_%s",suffix.c_str()),    suffix_title.c_str(), 100,0,100);
      htcmet[i][j]->GetXaxis()->SetTitle("tcmet (GeV)");
      htcmetNew[i][j]->GetXaxis()->SetTitle("tcmetNew (GeV)");
      hpfmet[i][j]->GetXaxis()->SetTitle("pfmet (GeV)");
    }
  }
  
}
 
//--------------------------------------------------------------------

void Z_looper::MakeBabyNtuple (const char* babyFileName)
{

  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  rootdir->cd();

  babyFile_ = new TFile(Form("%s", babyFileName), "RECREATE");
  babyFile_->cd();
  babyTree_ = new TTree("T1", "A Baby Ntuple");

  //event stuff
  babyTree_->Branch("rho",          &rho_,          "rho/F"          );
  babyTree_->Branch("vtxidx",       &vtxidx_,       "vtxidx/I"       );
  babyTree_->Branch("zdilep",       &zdilep_,       "zdilep/I"       );
  babyTree_->Branch("dataset",      &dataset_,      "dataset[500]/C" );
  babyTree_->Branch("run",          &run_,          "run/I"          );
  babyTree_->Branch("xsec",         &xsec_,         "xsec/F"         );
  babyTree_->Branch("ssmu1",        &ssmu1_,        "ssmu1/I"        );
  babyTree_->Branch("ssmu2",        &ssmu2_,        "ssmu2/I"        );
  babyTree_->Branch("eldup",        &eldup_,        "eldup/I"        );
  babyTree_->Branch("btagweight",   &btagweight_,   "btagweight/F"   );
  babyTree_->Branch("btagweightup", &btagweightup_, "btagweightup/F" );
  babyTree_->Branch("ht30",         &ht30_,         "ht30/F"         );
  babyTree_->Branch("ht40",         &ht40_,         "ht40/F"         );
  babyTree_->Branch("ht40up",       &ht40up_,       "ht40up/F"       );
  babyTree_->Branch("ht40dn",       &ht40dn_,       "ht40dn/F"       );
  babyTree_->Branch("nbcsvl",       &nbcsvl_,       "nbcsvl/I"       );
  babyTree_->Branch("nbcsvlm",      &nbcsvlm_,      "nbcsvlm/I"      );
  babyTree_->Branch("nbcsvm",       &nbcsvm_,       "nbcsvm/I"       );
  babyTree_->Branch("nbcsvt",       &nbcsvt_,       "nbcsvt/I"       );
  babyTree_->Branch("nbvz",         &nbvz_,         "nbvz/I"         );
  babyTree_->Branch("nbvzres",      &nbvzres_,      "nbvzres/I"      );
  babyTree_->Branch("jzb",          &jzb_,          "jzb/F"          );
  babyTree_->Branch("mjj",          &mjj_,          "mjj/F"          );
  babyTree_->Branch("mbb",          &mbb_,          "mbb/F"          );
  babyTree_->Branch("mjjup",        &mjjup_,        "mjjup/F"        );
  babyTree_->Branch("mjjdn",        &mjjdn_,        "mjjdn/F"        );
  babyTree_->Branch("nlep",         &nlep_,         "nlep/I"         );
  babyTree_->Branch("nel",          &nel_,          "nel/I"          );
  babyTree_->Branch("nmu",          &nmu_,          "nmu/I"          );
  babyTree_->Branch("st",           &st_,           "st/I"           );
  babyTree_->Branch("goodrun",      &goodrun_,      "goodrun/I"      );
  babyTree_->Branch("lumi",         &lumi_,         "lumi/I"         );
  babyTree_->Branch("event",        &event_,        "event/I"        );
  babyTree_->Branch("failjetid",    &failjetid_,    "failjetid/I"    );
  babyTree_->Branch("unc",          &unclustered_,  "unc/F"          );
  babyTree_->Branch("uncx",         &unclustered_y_,"uncx/F"         );
  babyTree_->Branch("uncy",         &unclustered_y_,"uncy/F"         );
  babyTree_->Branch("maxemf",       &maxemf_,       "maxemf/F"       );
  babyTree_->Branch("trgeff",       &trgeff_,       "trgeff/F"       );
  babyTree_->Branch("nvtx",         &nGoodVertex_,  "nvtx/I"         );
  babyTree_->Branch("weight",       &weight_,       "weight/F"       );
  babyTree_->Branch("vtxweight",    &vtxweight_,    "vtxweight/F"    );
  babyTree_->Branch("pthat",        &pthat_,        "pthat/F"        );
  babyTree_->Branch("mllgen",       &mllgen_,       "mllgen/F"       );
  babyTree_->Branch("qscale",       &qscale_,       "qscale/F"       );
  babyTree_->Branch("mg",           &mg_,           "mg/I"           );
  babyTree_->Branch("ml",           &ml_,           "ml/I"           );
  babyTree_->Branch("x",            &x_,            "x/F"            );
  babyTree_->Branch("ptgen1",       &ptgen1_,       "ptgen1/F"       );
  babyTree_->Branch("ptgen2",       &ptgen2_,       "ptgen2/F"       );
  babyTree_->Branch("eff0",         &eff0_,         "eff0/F"         );
  babyTree_->Branch("eff100",       &eff100_,       "eff100/F"       );
  babyTree_->Branch("eff200",       &eff200_,       "eff200/F"       );
  babyTree_->Branch("eff300",       &eff300_,       "eff300/F"       );
  babyTree_->Branch("eveto1",       &eveto1_,       "eveto1/F"       );
  babyTree_->Branch("hveto1",       &hveto1_,       "hveto1/F"       );
  babyTree_->Branch("eveto2",       &eveto2_,       "eveto2/F"       );
  babyTree_->Branch("hveto2",       &hveto2_,       "hveto2/F"       );
  babyTree_->Branch("ngenels",      &ngenels_,      "ngenels/I"      );
  babyTree_->Branch("ngenmus",      &ngenmus_,      "ngenmus/I"      );
  babyTree_->Branch("ngentaus",     &ngentaus_,     "ngentaus/I"     );
  babyTree_->Branch("ngenleps",     &ngenleps_,     "ngenleps/I"     );

  babyTree_->Branch("jet1flav",        &jet1flav_,        "jet1flav/I"        );
  babyTree_->Branch("jet2flav",        &jet2flav_,        "jet2flav/I"        );
  babyTree_->Branch("jet3flav",        &jet3flav_,        "jet3flav/I"        );
  babyTree_->Branch("jet4flav",        &jet4flav_,        "jet4flav/I"        );

  babyTree_->Branch("ngenbs",       &ngenbs_,       "ngenbs/I"       );

  babyTree_->Branch("jet1drgen",       &jet1drgen_,       "jet1drgen/F"       );
  babyTree_->Branch("jet2drgen",       &jet2drgen_,       "jet2drgen/F"       );
  babyTree_->Branch("jet3drgen",       &jet3drgen_,       "jet3drgen/F"       );
  babyTree_->Branch("jet4drgen",       &jet4drgen_,       "jet4drgen/F"       );

  babyTree_->Branch("jet1beta1_01",    &jet1beta1_01_,    "jet1beta1_01/F"    );
  babyTree_->Branch("jet2beta1_01",    &jet2beta1_01_,    "jet2beta1_01/F"    );
  babyTree_->Branch("jet3beta1_01",    &jet3beta1_01_,    "jet3beta1_01/F"    );
  babyTree_->Branch("jet4beta1_01",    &jet4beta1_01_,    "jet4beta1_01/F"    );

  babyTree_->Branch("jet1beta2_01",    &jet1beta2_01_,    "jet1beta2_01/F"    );
  babyTree_->Branch("jet2beta2_01",    &jet2beta2_01_,    "jet2beta2_01/F"    );
  babyTree_->Branch("jet3beta2_01",    &jet3beta2_01_,    "jet3beta2_01/F"    );
  babyTree_->Branch("jet4beta2_01",    &jet4beta2_01_,    "jet4beta2_01/F"    );

  babyTree_->Branch("jet1beta1_05",    &jet1beta1_05_,    "jet1beta1_05/F"    );
  babyTree_->Branch("jet2beta1_05",    &jet2beta1_05_,    "jet2beta1_05/F"    );
  babyTree_->Branch("jet3beta1_05",    &jet3beta1_05_,    "jet3beta1_05/F"    );
  babyTree_->Branch("jet4beta1_05",    &jet4beta1_05_,    "jet4beta1_05/F"    );

  babyTree_->Branch("jet1beta2_05",    &jet1beta2_05_,    "jet1beta2_05/F"    );
  babyTree_->Branch("jet2beta2_05",    &jet2beta2_05_,    "jet2beta2_05/F"    );
  babyTree_->Branch("jet3beta2_05",    &jet3beta2_05_,    "jet3beta2_05/F"    );
  babyTree_->Branch("jet4beta2_05",    &jet4beta2_05_,    "jet4beta2_05/F"    );

  babyTree_->Branch("jet1beta1_10",    &jet1beta1_10_,    "jet1beta1_10/F"    );
  babyTree_->Branch("jet2beta1_10",    &jet2beta1_10_,    "jet2beta1_10/F"    );
  babyTree_->Branch("jet3beta1_10",    &jet3beta1_10_,    "jet3beta1_10/F"    );
  babyTree_->Branch("jet4beta1_10",    &jet4beta1_10_,    "jet4beta1_10/F"    );

  babyTree_->Branch("jet1beta2_10",    &jet1beta2_10_,    "jet1beta2_10/F"    );
  babyTree_->Branch("jet2beta2_10",    &jet2beta2_10_,    "jet2beta2_10/F"    );
  babyTree_->Branch("jet3beta2_10",    &jet3beta2_10_,    "jet3beta2_10/F"    );
  babyTree_->Branch("jet4beta2_10",    &jet4beta2_10_,    "jet4beta2_10/F"    );

  babyTree_->Branch("nwzpartons",      &nwzpartons_,      "nwzpartons/I"      );

  babyTree_->Branch("ngennue",      &ngennue_,      "ngennue/I"      );
  babyTree_->Branch("ngennum",      &ngennum_,      "ngennum/I"      );
  babyTree_->Branch("ngennut",      &ngennut_,      "ngennut/I"      );
  babyTree_->Branch("ngennu",       &ngennu_,       "ngennu/I"       );

  babyTree_->Branch("mlb1",         &mlb1_,         "mlb1/F"         );
  babyTree_->Branch("mlb2",         &mlb2_,         "mlb2/F"         );
  babyTree_->Branch("mlbt1",        &mlbt1_,        "mlbt1/F"        );
  babyTree_->Branch("mlbt2",        &mlbt2_,        "mlbt2/F"        );

  babyTree_->Branch("mlbmin",       &mlbmin_,       "mlbmin/F"       );
  babyTree_->Branch("mlbtmin",      &mlbtmin_,      "mlbtmin/F"      );

  babyTree_->Branch("mt2",          &mt2_,          "mt2/F"          );
  babyTree_->Branch("mt2j",         &mt2j_,         "mt2j/F"         );

  babyTree_->Branch("el27"     ,    &el27_     ,    "el27/I"        );
  babyTree_->Branch("mm"       ,    &mm_       ,    "mm/I"          );
  babyTree_->Branch("mmtk"     ,    &mmtk_     ,    "mmtk/I"        );
  babyTree_->Branch("me"       ,    &me_       ,    "me/I"          );
  babyTree_->Branch("em"       ,    &em_       ,    "em/I"          );
  babyTree_->Branch("mu"       ,    &mu_       ,    "mu/I"          );
  babyTree_->Branch("mu21"     ,    &mu21_     ,    "mu21/I"        );
  babyTree_->Branch("ee"       ,    &ee_       ,    "ee/I"          );

  babyTree_->Branch("m13"      ,    &m13_      ,    "m13/F"         );
  babyTree_->Branch("m23"      ,    &m23_      ,    "m23/F"         );
  babyTree_->Branch("m14"      ,    &m14_      ,    "m14/F"         );
  babyTree_->Branch("m24"      ,    &m24_      ,    "m24/F"         );
  babyTree_->Branch("m34"      ,    &m34_      ,    "m34/F"         );

  //electron-matched jet stuff
  babyTree_->Branch("drjetll",      &drjet_ll_,     "drjetll/F"     );
  babyTree_->Branch("jetptll",      &jetpt_ll_,     "jetptll/F"     );
  babyTree_->Branch("pfjetidll",    &pfjetid_ll_,   "pfjetidll/I"   );
  babyTree_->Branch("drjetlt",      &drjet_lt_,     "drjetlt/F"     );
  babyTree_->Branch("jetptlt",      &jetpt_lt_,     "jetptlt/F"     );
  babyTree_->Branch("pfjetidlt",    &pfjetid_lt_,   "pfjetidlt/I"   );

  babyTree_->Branch("id1",          &id1_,          "id1/I"         );
  babyTree_->Branch("id2",          &id2_,          "id2/I"         );
  babyTree_->Branch("id3",          &id3_,          "id3/I"         );
  babyTree_->Branch("id4",          &id4_,          "id4/I"         );
  babyTree_->Branch("id5",          &id5_,          "id5/I"         );
  babyTree_->Branch("id6",          &id6_,          "id6/I"         );
  babyTree_->Branch("el1tv",        &el1tv_,        "el1tv/I"       );
  babyTree_->Branch("el2tv",        &el2tv_,        "el2tv/I"       );

  babyTree_->Branch("el1nomu",      &el1nomu_,      "el1nomu/I"     );
  babyTree_->Branch("el2nomu",      &el2nomu_,      "el2nomu/I"     );
  babyTree_->Branch("el1nomuss",    &el1nomuss_,    "el1nomuss/I"   );
  babyTree_->Branch("el2nomuss",    &el2nomuss_,    "el2nomuss/I"   );

  babyTree_->Branch("tche1",        &tche1_,        "tche1/F"       );
  babyTree_->Branch("tche2",        &tche2_,        "tche2/F"       );
  babyTree_->Branch("tche3",        &tche3_,        "tche3/F"       );
  babyTree_->Branch("tche4",        &tche4_,        "tche4/F"       );
  babyTree_->Branch("tche5",        &tche5_,        "tche5/F"       );
  babyTree_->Branch("tche6",        &tche6_,        "tche6/F"       );
  babyTree_->Branch("tche7",        &tche7_,        "tche7/F"       );
  babyTree_->Branch("tche8",        &tche8_,        "tche8/F"       );

  babyTree_->Branch("csv1",         &csv1_,         "csv1/F"       );
  babyTree_->Branch("csv2",         &csv2_,         "csv2/F"       );
  babyTree_->Branch("csv3",         &csv3_,         "csv3/F"       );
  babyTree_->Branch("csv4",         &csv4_,         "csv4/F"       );
  babyTree_->Branch("csv5",         &csv5_,         "csv5/F"       );
  babyTree_->Branch("csv6",         &csv6_,         "csv6/F"       );
  babyTree_->Branch("csv7",         &csv7_,         "csv7/F"       );
  babyTree_->Branch("csv8",         &csv8_,         "csv8/F"       );

  babyTree_->Branch("jetunc1",     &jetunc1_,     "jetunc1/F"   );
  babyTree_->Branch("jetunc2",     &jetunc2_,     "jetunc2/F"   );
  babyTree_->Branch("jetunc3",     &jetunc3_,     "jetunc3/F"   );
  babyTree_->Branch("jetunc4",     &jetunc4_,     "jetunc4/F"   );
  babyTree_->Branch("jetunc5",     &jetunc5_,     "jetunc5/F"   );
  babyTree_->Branch("jetunc6",     &jetunc6_,     "jetunc6/F"   );
  babyTree_->Branch("jetunc7",     &jetunc7_,     "jetunc7/F"   );
  babyTree_->Branch("jetunc8",     &jetunc8_,     "jetunc8/F"   );

  babyTree_->Branch("jetgenb1",     &jetgenb1_,     "jetgenb1/I"   );
  babyTree_->Branch("jetgenb2",     &jetgenb2_,     "jetgenb2/I"   );
  babyTree_->Branch("jetgenb3",     &jetgenb3_,     "jetgenb3/I"   );
  babyTree_->Branch("jetgenb4",     &jetgenb4_,     "jetgenb4/I"   );
  babyTree_->Branch("jetgenb5",     &jetgenb5_,     "jetgenb5/I"   );
  babyTree_->Branch("jetgenb6",     &jetgenb6_,     "jetgenb6/I"   );
  babyTree_->Branch("jetgenb7",     &jetgenb7_,     "jetgenb7/I"   );
  babyTree_->Branch("jetgenb8",     &jetgenb8_,     "jetgenb8/I"   );

  //met stuff
  babyTree_->Branch("pfmett1new",      &pfmett1new_,      "pfmett1new/F"    );
  babyTree_->Branch("pfmett1newphi",   &pfmett1newphi_,   "pfmett1newphi/F" );
  babyTree_->Branch("minmet",       &minmet_,       "minmet/F"     );
  babyTree_->Branch("trkmet",       &trkmet_,       "trkmet/F"     );
  babyTree_->Branch("trkmetphi",    &trkmetphi_,    "trkmetphi/F"  );
  babyTree_->Branch("trksumet",     &trksumet_,     "trksumet/F"   );
  babyTree_->Branch("pfmet",        &pfmet_,        "pfmet/F"      );
  babyTree_->Branch("pfmett1",      &pfmett1_,      "pfmett1/F"    );
  babyTree_->Branch("pfmett1phi",   &pfmett1phi_,   "pfmett1phi/F" );
  babyTree_->Branch("pfmetup",      &pfmetUp_,      "pfmetup/F"    );
  babyTree_->Branch("pfmetdn",      &pfmetDn_,      "pfmetdn/F"    );
  babyTree_->Branch("pfmetphi",     &pfmetphi_,     "pfmetphi/F"   );
  babyTree_->Branch("pfsumet",      &pfsumet_,      "pfsumet/F"    );
  babyTree_->Branch("met",          &met_,          "met/F"        );
  babyTree_->Branch("metphi",       &metphi_,       "metphi/F"     );
  babyTree_->Branch("sumet",        &sumet_,        "sumet/F"      );
  babyTree_->Branch("mumet",        &mumet_,        "mumet/F"      );
  babyTree_->Branch("mumetphi",     &mumetphi_,     "mumetphi/F"   );
  babyTree_->Branch("musumet",      &musumet_,      "musumet/F"    );
  babyTree_->Branch("mujesmet",     &mujesmet_,     "mujesmet/F"      );
  babyTree_->Branch("mujesmetphi",  &mujesmetphi_,  "mujesmetphi/F"   );
  babyTree_->Branch("mujessumet",   &mujessumet_,   "mujessumet/F"    );
  babyTree_->Branch("genmet",       &genmet_,       "genmet/F"   );
  babyTree_->Branch("genmetcustom", &genmetcustom_, "genmetcustom/F"   );
  babyTree_->Branch("genmetphi",    &genmetphi_,    "genmetphi/F");
  babyTree_->Branch("gensumet",     &gensumet_,     "gensumet/F" );
  babyTree_->Branch("dphixmet",     &dphixmet_,     "dphixmet/F"    );
  babyTree_->Branch("metpar",       &metPar_,       "metpar/F"      );
  babyTree_->Branch("metperp",      &metPerp_,      "metperp/F"     );
  babyTree_->Branch("tcmet",        &tcmet_,        "tcmet/F"      );
  babyTree_->Branch("tcmetphi",     &tcmetphi_,     "tcmetphi/F"   );
  babyTree_->Branch("tcsumet",      &tcsumet_,      "tcsumet/F"    );
  babyTree_->Branch("tcmetNew",     &tcmetNew_,     "tcmetNew/F"      );
  babyTree_->Branch("tcmetphiNew",  &tcmetphiNew_,  "tcmetphiNew/F"   );
  babyTree_->Branch("tcsumetNew",   &tcsumetNew_,   "tcsumetNew/F"    );
  babyTree_->Branch("tcmetcor",     &tcmetcor_,     "tcmetcor/F");  
  babyTree_->Branch("pfmetcor",     &pfmetcor_,     "pfmetcor/F");  

  //jet stuff
  babyTree_->Branch("njets",          &nJets_,            "njets/I"       );
  babyTree_->Branch("njetsold",       &nJetsOld_,         "njetsold/I"    );
  babyTree_->Branch("njetsres",       &nJetsRes_,         "njetsRes/I"    );
  babyTree_->Branch("njetsup",        &nJetsUp_,          "njetsup/I"     );
  babyTree_->Branch("njetsdn",        &nJetsDn_,          "njetsdn/I"     );
  babyTree_->Branch("njpt",           &nJPT_,             "njpt/I"        );
  babyTree_->Branch("njets40",        &nJets40_,          "njets40/I"     );
  babyTree_->Branch("njets40up",      &njets40up_,        "njets40up/I"   );
  babyTree_->Branch("njets40dn",      &njets40dn_,        "njets40dn/I"   );
  babyTree_->Branch("sumjetpt",       &sumJetPt_,         "sumjetpt/F"    );
  babyTree_->Branch("sumjetpt10",     &sumJetPt10_,       "sumjetpt10/F"  );
  babyTree_->Branch("vecjetpt",       &vecJetPt_,         "vecjetpt/F"    );
  babyTree_->Branch("nbtags",         &nbtags_,           "nbtags/I");
  babyTree_->Branch("nbl",            &nbl_,              "nbl/I");
  babyTree_->Branch("nbm",            &nbm_,              "nbm/I");
  babyTree_->Branch("ndphijetmet",    &dphijetmet_,       "dphijetmet/F");
  babyTree_->Branch("maxjetpt",       &jetmax_pt_,        "maxjetpt/F");
  babyTree_->Branch("maxjetdphimet",  &jetmax_dphimet_,   "maxjetdphimet/F");
                         
  //Z stuff
  babyTree_->Branch("leptype",               &leptype_,               "leptype/I");
  babyTree_->Branch("ecaltype",              &ecaltype_,              "ecaltype/I");
  babyTree_->Branch("passz",                 &passz_,                 "passz/I");  
  babyTree_->Branch("pdgid",                 &pdgid_,                 "pdgid/I");  
  babyTree_->Branch("dpdm",                  &dpdm_,                  "dpdm/F");  
  babyTree_->Branch("meterror",              &metError_,              "metError/F");  
  babyTree_->Branch("meterrorc",             &metErrorC_,             "metErrorc/F");  
  babyTree_->Branch("ptll",                  &ptll_,                  "ptll/F");  
  babyTree_->Branch("ptlt",                  &ptlt_,                  "ptlt/F");  
  babyTree_->Branch("pterrll",               &pterrll_,               "pterrll/F");  
  babyTree_->Branch("pterrlt",               &pterrlt_,               "pterrlt/F");  
  babyTree_->Branch("ptlltrk",               &ptlltrk_,               "ptlltrk/F");  
  babyTree_->Branch("ptlttrk",               &ptlttrk_,               "ptlttrk/F");  
  babyTree_->Branch("ptllgfit",              &ptllgfit_,              "ptllgfit/F");  
  babyTree_->Branch("ptltgfit",              &ptltgfit_,              "ptltgfit/F");  
  babyTree_->Branch("ptllpf",                &ptll_pf_,               "ptllpf/F");  
  babyTree_->Branch("ptltpf",                &ptlt_pf_,               "ptltpf/F");  
  babyTree_->Branch("ptllgen",               &ptllgen_,               "ptllgen/F");  
  babyTree_->Branch("ptltgen",               &ptltgen_,               "ptltgen/F");  
  babyTree_->Branch("npfmuons",              &npfmuons_,              "npfmuons/I");  
  babyTree_->Branch("nmatchedpfmuons",       &nmatchedpfmuons_,       "nmatchedpfmuons/I");  
  babyTree_->Branch("idll",                  &idll_,                  "idll/I");  
  babyTree_->Branch("idlt",                  &idlt_,                  "idlt/I");  
  babyTree_->Branch("etall",                 &etall_,                 "etall/F");  
  babyTree_->Branch("etalt",                 &etalt_,                 "etalt/F");  
  babyTree_->Branch("phill",                 &phill_,                 "phill/F");  
  babyTree_->Branch("philt",                 &philt_,                 "philt/F");  
  babyTree_->Branch("dilmass",               &dilmass_,               "dilmass/F");  
  babyTree_->Branch("dilmasspf",             &dilmasspf_,             "dilmasspf/F");  
  babyTree_->Branch("dilmasscor",            &dilmasscor_,            "dilmasscor/F");  
  babyTree_->Branch("dilpt",                 &dilpt_,                 "dilpt/F");  
  babyTree_->Branch("flagll",                &flagll_,                "flagll/I");  
  babyTree_->Branch("flaglt",                &flaglt_,                "flaglt/I");  
  babyTree_->Branch("isdata",                &isdata_,                "isdata/I");  

  babyTree_->Branch("lljj",                  &lljj_,                  "lljj/F");  
  babyTree_->Branch("jj"  ,                  &jj_  ,                  "jj/F"  );  
  babyTree_->Branch("l1jj",                  &l1jj_,                  "l1jj/F");  
  babyTree_->Branch("l2jj",                  &l2jj_,                  "l2jj/F");  
  babyTree_->Branch("j1ll",                  &j1ll_,                  "j1ll/F");  
  babyTree_->Branch("j2ll",                  &j2ll_,                  "j2ll/F");  

  babyTree_->Branch("l1j1",                  &l1j1_,                  "l1j1/F");  
  babyTree_->Branch("l2j2",                  &l2j2_,                  "l2j2/F");  
  babyTree_->Branch("l1j2",                  &l1j2_,                  "l1j2/F");  
  babyTree_->Branch("l2j1",                  &l2j1_,                  "l2j1/F");  

  babyTree_->Branch("lep1iso" ,              &lep1iso_,               "lep1iso/F");  
  babyTree_->Branch("lep2iso" ,              &lep2iso_,               "lep2iso/F");  
  babyTree_->Branch("lep1D0" ,               &lep1D0_,                "lep1D0/F");  
  babyTree_->Branch("lep2D0" ,               &lep2D0_,                "lep2D0/F");  
  babyTree_->Branch("lep1Dz" ,               &lep1Dz_,                "lep1Dz/F");  
  babyTree_->Branch("lep2Dz" ,               &lep2Dz_,                "lep2Dz/F");  

  babyTree_->Branch("dilep"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &dilep_	);
  babyTree_->Branch("dileppf" , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &dileppf_	);
  babyTree_->Branch("w"       , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &w_ 	);

  babyTree_->Branch("lep1"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &lep1_	);
  babyTree_->Branch("lep2"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &lep2_	);
  babyTree_->Branch("lep3"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &lep3_	);
  babyTree_->Branch("lep4"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &lep4_	);
  babyTree_->Branch("lep5"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &lep5_	);
  babyTree_->Branch("lep6"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &lep6_	);
  babyTree_->Branch("pflep1"  , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &pflep1_	);
  babyTree_->Branch("pflep2"  , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &pflep2_	);

  babyTree_->Branch("genlep1" , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genlep1_	);
  babyTree_->Branch("genlep2" , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genlep2_	);
  babyTree_->Branch("gennu1"  , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &gennu1_	);
  babyTree_->Branch("gennu2"  , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &gennu2_	);

  babyTree_->Branch("pfTau_leadPtcand"  , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &pfTau_leadPtcand_	);
  babyTree_->Branch("pfTau_leadPtcandID",        &pfTau_leadPtcandID_,        "pfTau_leadPtcandID/I");

  babyTree_->Branch("jet1"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &jet1_	);
  babyTree_->Branch("jet2"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &jet2_	);
  babyTree_->Branch("jet3"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &jet3_	);
  babyTree_->Branch("jet4"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &jet4_	);
  babyTree_->Branch("jet5"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &jet5_	);
  babyTree_->Branch("jet6"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &jet6_	);
  babyTree_->Branch("jet7"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &jet7_	);
  babyTree_->Branch("jet8"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &jet8_	);
  babyTree_->Branch("subthreshjetup1", "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &subthreshjetup1_ );
  babyTree_->Branch("subthreshjetup2", "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &subthreshjetup2_ );

  babyTree_->Branch("jet1mcfa"    , &jet1mcfa_	, "jet1mcfa/I" );
  babyTree_->Branch("jet2mcfa"    , &jet2mcfa_	, "jet2mcfa/I" );
  babyTree_->Branch("jet3mcfa"    , &jet3mcfa_	, "jet3mcfa/I" );
  babyTree_->Branch("jet4mcfa"    , &jet4mcfa_	, "jet4mcfa/I" );

  babyTree_->Branch("jet1mcfp"    , &jet1mcfp_	, "jet1mcfp/I" );
  babyTree_->Branch("jet2mcfp"    , &jet2mcfp_	, "jet2mcfp/I" );
  babyTree_->Branch("jet3mcfp"    , &jet3mcfp_	, "jet3mcfp/I" );
  babyTree_->Branch("jet4mcfp"    , &jet4mcfp_	, "jet4mcfp/I" );

  babyTree_->Branch("bjet1"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &bjet1_	);
  babyTree_->Branch("bjet2"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &bjet2_	);
  babyTree_->Branch("bjet3"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &bjet3_	);
  babyTree_->Branch("bjet4"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &bjet4_	);

  babyTree_->Branch("genchi30p4"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genchi30p4_	);
  babyTree_->Branch("genchi20p4"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genchi20p4_	);
  babyTree_->Branch("genchi10p4_3"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genchi10p4_3_	);
  babyTree_->Branch("genchi10p4_2"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genchi10p4_2_	);

  babyTree_->Branch("genbquark1"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genbquark1_	);
  babyTree_->Branch("genbquark2"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genbquark2_	);
  babyTree_->Branch("genbquark3"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genbquark3_	);
  babyTree_->Branch("genbquark4"   , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genbquark4_	);
  babyTree_->Branch("genz"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genz_	);
  babyTree_->Branch("gent"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &gent_	);
  babyTree_->Branch("gentbar" , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &gentbar_	);
  babyTree_->Branch("genttbar", "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &genttbar_  );

  babyTree_->Branch("csc"       ,  &csc_       ,  "csc/I");  
  babyTree_->Branch("hbhe"      ,  &hbhe_      ,  "hbhe/I");  
  babyTree_->Branch("hbhenew"   ,  &hbhenew_   ,  "hbhenew/I");  
  babyTree_->Branch("hcallaser" ,  &hcallaser_ ,  "hcallaser/I");  
  babyTree_->Branch("ecallaser" ,  &ecallaser_ ,  "ecallaser/I");  
  babyTree_->Branch("ecaltp"    ,  &ecaltp_    ,  "ecaltp/I");  
  babyTree_->Branch("trkfail"   ,  &trkfail_   ,  "trkfail/I");  
  babyTree_->Branch("eebadsc"   ,  &eebadsc_   ,  "eebadsc/I");  

  babyTree_->Branch("drll"      ,  &drll_      ,  "drll/F"    );  
  babyTree_->Branch("dphill"    ,  &dphill_    ,  "dphill/F"  );  
  babyTree_->Branch("drblmin"   ,  &drblmin_   ,  "drblmin/F" );  
  babyTree_->Branch("st30"      ,  &st30_      ,  "st30/F"    );  
  babyTree_->Branch("st40"      ,  &st40_      ,  "st40/F"    );  

  babyTree_->Branch("m1"        ,  &m1_        ,  "m1/F"        );  
  babyTree_->Branch("m2"        ,  &m2_        ,  "m2/F"        );  
  babyTree_->Branch("m3"        ,  &m3_        ,  "m3/F"        );  
  babyTree_->Branch("zveto"     ,  &zveto_     ,  "zveto/I"     );  
  babyTree_->Branch("nextramu"  ,  &nextramu_  ,  "nextramu/I"  );  
  babyTree_->Branch("nhyp"      ,  &nhyp_      ,  "nhyp/I"      );  
  babyTree_->Branch("nmuss"     ,  &nmuss_     ,  "nmuss/I"     );  
  babyTree_->Branch("extraz"    ,  &extraz_    ,  "extraz/I"    );  
  babyTree_->Branch("extrag"    ,  &extrag_    ,  "extrag/I"    );  

  babyTree_->Branch("pujets"    , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >", &pujets_ );
  babyTree_->Branch("pt40jets"  , "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >", &pt40jets_ );

  babyTree_->Branch("pt40csvs"  , "std::vector< Float_t >", &pt40csvs_ );
  babyTree_->Branch("pt40mcfas" , "std::vector< Float_t >", &pt40mcfas_ );
  babyTree_->Branch("pt40mcfps" , "std::vector< Float_t >", &pt40mcfps_ );
  babyTree_->Branch("npujets"   ,  &npujets_   ,  "npujets/I"   );
}

//--------------------------------------------------------------------

void Z_looper::FillBabyNtuple ()
{
  babyTree_->Fill();
}

//--------------------------------------------------------------------

void Z_looper::CloseBabyNtuple ()
{
  babyFile_->cd();
  babyTree_->Write();
  babyFile_->Close();
}

//--------------------------------------------------------------------

void Z_looper::fillHistos(TH1F *h1[4],float value, float weight, int myType)
{

  fillUnderOverFlow(h1[myType], value, weight);      
  fillUnderOverFlow(h1[3],      value, weight);      
}

//--------------------------------------------------------------------

void Z_looper::fillHistos(TH1F *h1[4][4],float value, float weight, int myType, int nJetsIdx)
{

  if( nJetsIdx > 2 ) nJetsIdx = 2;

  fillUnderOverFlow(h1[myType][nJetsIdx], value, weight);      
  fillUnderOverFlow(h1[myType][3],        value, weight);      
  fillUnderOverFlow(h1[3][nJetsIdx],      value, weight);      
  fillUnderOverFlow(h1[3][3],             value, weight);      
}

//--------------------------------------------------------------------

float Z_looper::getMetError(  vector<int> goodMuonIndices ){

  //error is zero if no muons
  if( goodMuonIndices.size() == 0 ) return 0.;

  float metError = 0.;

  float met_x = evt_pfmet() * cos( evt_pfmetPhi() );
  float met_y = evt_pfmet() * sin( evt_pfmetPhi() );
  float met   = evt_pfmet();

  //loop over all muons in goodMuonIndices (pt > 20 GeV, |eta| < 2.4, OSZ_v1)
  for( unsigned int i = 0 ; i < goodMuonIndices.size() ; ++i ){
    int imu = goodMuonIndices.at(i);

    //calculate uncertainties in muon x,y momentum components
    //I am assuming that dpx = dpt * cos(phi)
    float dpx = cos( mus_p4().at(imu).phi() ) * mus_ptErr().at(imu);
    float dpy = sin( mus_p4().at(imu).phi() ) * mus_ptErr().at(imu);

    //check how much met changes when I alter the muon pt by (dpx,dpy)
    float metxprime = met_x + dpx;
    float metyprime = met_y + dpy;
    float metprime  = sqrt( metxprime * metxprime + metyprime * metyprime );
    float dmet      = metprime - met;

    //sum the errors from each muon in quadrature
    metError += dmet * dmet;
    
  }

  metError = sqrt( metError );

  return metError;
}

//--------------------------------------------------------------------

float Z_looper::getMetError_claudio(  vector<int> goodMuonIndices ){
   
  //error is zero if no muons
  if( goodMuonIndices.size() == 0 ) return 0.;
  

  float met_x = evt_pfmet() * cos( evt_pfmetPhi() );
  float met_y = evt_pfmet() * sin( evt_pfmetPhi() );
  float met   = evt_pfmet();

  float metError = 0.;

  //loop over all muons in goodMuonIndices (pt > 20 GeV, |eta| < 2.4, OSZ_v1)
  for( unsigned int i = 0 ; i < goodMuonIndices.size() ; ++i ){
    int imu = goodMuonIndices.at(i);
 
    float phi  = mus_p4().at(imu).phi();
    float dpt  = mus_ptErr().at(imu);
    float dmet = ( ( cos(phi) * met_x + sin(phi) * met_y ) * dpt ) / met;
    metError += dmet * dmet;
  
  }
  
  metError = sqrt(metError);
  
  return metError;
  
}

//--------------------------------------------------------------------

float Z_looper::PassGenSelection( bool isData ){
  
  if( isData ) return -999.;

  return -9999.;

  //---------------------------------------------
  // does this event pass the analysis selection?
  //---------------------------------------------
  
  // mc leptons
  std::vector<unsigned int> mcLeptonIndices;
  int nGoodLep = 0;
  for (size_t i = 0; i < cms2.genps_id().size(); ++i){
    
    //electron or muon
    if (!(abs(cms2.genps_id()[i]) == 11 || abs(cms2.genps_id()[i]) == 13))      continue;

    //pt > 20 GeV, |eta| < 2.5
    if ( cms2.genps_p4()[i].Pt() < 20.0 || fabs(cms2.genps_p4()[i].Eta()) > 2.5) continue;

    nGoodLep++;
    mcLeptonIndices.push_back(i);
  }

  if( nGoodLep < 2 ) return -1.;

  //look for OS pt > 20,20 GeV pair Z mass veto
  bool foundPair = false;

  for( unsigned int i = 0 ; i < mcLeptonIndices.size() ; ++i ){
    unsigned int ilep = mcLeptonIndices.at(i);
    for( unsigned int j = i + 1 ; j < mcLeptonIndices.size() ; ++j ){
      unsigned int jlep = mcLeptonIndices.at(j);

	  //OS
	  if ( cms2.genps_id()[ilep] * cms2.genps_id()[jlep] > 0 )                            continue;

	  //SF
	  if ( abs( cms2.genps_id()[ilep] ) != abs( cms2.genps_id()[jlep] ) )                 continue;

	  //Z mass 81-101 GeV
	  float dilmass = ( cms2.genps_p4()[ilep] + cms2.genps_p4()[jlep] ).mass();
	  if( dilmass < 81.0 || dilmass > 101. ) continue;
	
	  //found OS pair!
	  foundPair = true;
	     
	}
  }

  if( !foundPair ) return -2.;
   
  // mc jets
    
  int nGoodJet   = 0;
  float sumJetPt = 0.;
  for (size_t j = 0; j < cms2.evt_ngenjets(); ++j) 
    {
	  if (cms2.genjets_p4()[j].Pt() < 30.0)       continue;
	  if (fabs(cms2.genjets_p4()[j].Eta()) > 3.0) continue;
	  bool clean = true;
	  for ( size_t i = 0; i < mcLeptonIndices.size(); ++i) 
        {
		  if (ROOT::Math::VectorUtil::DeltaR(cms2.genjets_p4()[j], cms2.genps_p4()[mcLeptonIndices[i]]) < 0.4) {
			clean = false;
			break;
		  }
        }
	  if (clean){
		nGoodJet ++;
		sumJetPt += genjets_p4()[j].Pt();
	  }
    }
    
  if( nGoodJet < 2          ) return -3.;

  //hooray! return met
  return cms2.gen_met();
    
}


double fitf (double* x, double* par) {
  double arg = 0;
  if (par[2] != 0)
    arg = (x[0] - par[1])/par[2];
  
  double fitval = 0.5 * par[0] * (TMath::Erf(arg) + 1);
  return fitval;
}

float Z_looper::GenWeight( bool isData , char* prefix, int metcut ){
  
  if( isData ) return 0.;

  //---------------------------------------------
  // does this event pass the analysis selection?
  //---------------------------------------------
  
  // mc leptons
  std::vector<unsigned int> mcLeptonIndices;
  int nGoodLep = 0;
  for (size_t i = 0; i < cms2.genps_id().size(); ++i){
    
    //electron or muon
    if (!(abs(cms2.genps_id()[i]) == 11 || abs(cms2.genps_id()[i]) == 13))      continue;

    //pt > 20 GeV, |eta| < 2.5
    if ( cms2.genps_p4()[i].Pt() < 20.0 || fabs(cms2.genps_p4()[i].Eta()) > 2.5) continue;

    nGoodLep++;
    mcLeptonIndices.push_back(i);
  }

  if( nGoodLep < 2 ) return 0.;

  //look for OS pt > 20,20 GeV pair Z mass veto
  bool foundPair = false;
  int lep1idx = -1;
  int lep2idx = -1;

  for( unsigned int i = 0 ; i < mcLeptonIndices.size() ; ++i ){
    unsigned int ilep = mcLeptonIndices.at(i);
    for( unsigned int j = i + 1 ; j < mcLeptonIndices.size() ; ++j ){
      unsigned int jlep = mcLeptonIndices.at(j);

	  //OS
	  if ( cms2.genps_id()[ilep] * cms2.genps_id()[jlep] > 0 )                            continue;

	  //SF
	  if ( abs( cms2.genps_id()[ilep] ) != abs( cms2.genps_id()[jlep] ) )                 continue;

	  //Z mass 81-101 GeV
	  float dilmass = ( cms2.genps_p4()[ilep] + cms2.genps_p4()[jlep] ).mass();
	  if( dilmass < 81.0 || dilmass > 101. ) continue;
	
	  //found OS pair!
	  foundPair = true;
	  lep1idx = ilep;
	  lep2idx = jlep;

	}
  }

  if( !foundPair ) return 0.;
   
  // mc jets
    
  int nGoodJet   = 0;

  // float sumJetPt = 0.;
  // for (size_t j = 0; j < cms2.evt_ngenjets(); ++j) 
  // {
  //     if (cms2.genjets_p4()[j].Pt() < 30.0)       continue;
  //     if (fabs(cms2.genjets_p4()[j].Eta()) > 3.0) continue;
  //     bool clean = true;
  //     for ( size_t i = 0; i < mcLeptonIndices.size(); ++i) 
  //     {
  //         if (ROOT::Math::VectorUtil::DeltaR(cms2.genjets_p4()[j], cms2.genps_p4()[mcLeptonIndices[i]]) < 0.4) {
  //             clean = false;
  //             break;
  //         }
  //     }
  //     if (clean){
  // 	  nGoodJet ++;
  // 	  sumJetPt += genjets_p4()[j].Pt();
  // 	}
  // }

  for (unsigned int gidx = 0; gidx < cms2.genps_status().size(); gidx++){

	if (cms2.genps_status().at(gidx) != 3)
	  continue;

	if ((abs(cms2.genps_id().at(gidx)) < 1 || abs(cms2.genps_id().at(gidx)) > 5) && abs(cms2.genps_id().at(gidx)) != 21)
	  continue;

	if (fabs(cms2.genps_p4().at(gidx).eta()) > 3.0)
	  continue;

	if (cms2.genps_p4().at(gidx).pt() < 30.)
	  continue;
      
	nGoodJet++;
  }

  if( nGoodJet < 2 ) return 0.;

  // pass selection, now calculate weight

  int lep1id = abs( genps_id()[lep1idx] );
  int lep2id = abs( genps_id()[lep2idx] );

  float trgeff = 1;
  if( lep1id == 11 && lep2id == 11 ) trgeff = 1.00;   //ee
  if( lep1id == 13 && lep2id == 13 ) trgeff = 0.90;   //mm
  if( lep1id == 13 && lep2id == 11 ) trgeff = 0.95;   //em
  if( lep1id == 11 && lep2id == 13 ) trgeff = 0.95;   //em
    
  float lep1eff = 1;
  float lep2eff = 1;

  float pt1 = genps_p4()[lep1idx].Pt();
  float pt2 = genps_p4()[lep2idx].Pt();


  float isodeg = 1.00;

  if     ( !isData && TString(prefix).Contains("LM4") ) isodeg = 0.95;
  else if( !isData && TString(prefix).Contains("LM8") ) isodeg = 0.90;
  else if( !isData && TString(prefix).Contains("T5zz")) isodeg = 0.95;
  else{
	cout << "Error, unrecognized prefix " << prefix << ", quitting" << endl;
	exit(0);
  }

  // electron
  if ( lep1id == 11 ){

	if( pt1 > 60 ){
	  lep1eff *= 0.93;    // ID efficiency
	  lep1eff *= 0.97;    // iso efficiency
	  lep1eff *= isodeg;  // LM4 iso degradation
	}

	else{
	  lep1eff *= (pt1-20) * 0.00250 + 0.83; // ID efficiency
	  lep1eff *= (pt1-20) * 0.00225 + 0.88; // iso efficiency
	  lep1eff *= isodeg;                    // LM4 iso degradation
	}
  }

  // muon
  else if( lep1id == 13 ){

	lep1eff *= 0.91;      // ID efficiency

	if( pt1 > 60 ){
	  lep1eff *= 0.97;    // iso efficiency
	  lep1eff *= isodeg;  // LM4 iso degradation
	}

	else{
	  lep1eff *= (pt1-20) * 0.003 + 0.85;   // iso efficiency
	  lep1eff *= isodeg;                    // LM4 iso degradation
	}
  }

  // electron
  if ( lep2id == 11 ){

	if( pt2 > 60 ){
	  lep2eff *= 0.93;    // ID efficiency
	  lep2eff *= 0.97;    // iso efficiency
	  lep2eff *= isodeg;  // LM4 iso degradation
	}

	else{
	  lep2eff *= (pt2-20) * 0.00250 + 0.83; // ID efficiency
	  lep2eff *= (pt2-20) * 0.00225 + 0.88; // iso efficiency
	  lep2eff *= isodeg;                    // LM4 iso degradation
	}
  }

  // muon
  else if( lep2id == 13 ){

	lep2eff *= 0.91;      // ID efficiency

	if( pt2 > 60 ){
	  lep2eff *= 0.97;    // iso efficiency
	  lep2eff *= isodeg;  // LM4 iso degradation
	}

	else{
	  lep2eff *= (pt2-20) * 0.003 + 0.85;   // iso efficiency
	  lep2eff *= isodeg;                    // LM4 iso degradation
	}
  }


  TF1* erf = new TF1("erf", fitf, 0, 600, 3);
    
  float meteff = 1;

  if( metcut == 0 ){
	meteff = 1;
  }

  else if( metcut == 100 ){
	erf->SetParameters(1.00, 103, 29);
	meteff = erf->Eval(cms2.gen_met());
  }

  else if( metcut == 200 ){
	erf->SetParameters(0.99, 214, 38);
	meteff = erf->Eval(cms2.gen_met());
  }

  else if( metcut == 300 ){
	erf->SetParameters(0.98, 321, 40);
	meteff = erf->Eval(cms2.gen_met());
  }    

  else{
	cout << "ERROR! unrecognized metcut " << metcut << ", quitting" << endl;
	exit(0);
  }
      
  float eff = trgeff * lep1eff * lep2eff * meteff;

  return eff;


}


