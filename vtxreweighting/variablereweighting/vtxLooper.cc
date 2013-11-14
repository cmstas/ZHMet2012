// C++
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <set>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"
#include "TDatabasePDG.h"
#include "TSystem.h"
#include "TChainElement.h"
#include "TTree.h"
#include "TH1F.h"
#include "TString.h"
#include "TMath.h"
#include "TCut.h"

//local headers
#include "vtxLooper.h"
#include "TEMPLATES.h"

//stuff from tools/BTagReshaping
#include "/home/users/cwelke/CMSSW/CMSSW_5_3_2_patch4/src/CMS2/NtupleMacros/Tools/BTagReshaping/BTagReshaping.h"

//stuff from my tools
#include "/home/users/cwelke/Analysis/Spring2013/looperTools/genbtagTools.h"

using namespace std;
// using namespace Templates;

// vtxLooper::vtxLooper()
// {
// };

vtxLooper::vtxLooper( string input_selection )
{
  
  h20  = NULL;
  h30  = NULL;
  h50  = NULL;
  h70  = NULL;
  h90  = NULL;

  // TH1F* hall = new TH1F("hall","hall",50,0,50);
  hall = NULL;
  hgvar = NULL;
  hzvar = NULL;
  hgmjj = NULL;
  hzmjj = NULL;
  hzvtx = NULL;

  selection = input_selection;
  // rootfilename = Form("../tempfiles/vtxreweight_DoubleElectron_19fb_data%s_temp.root", input_selection.c_str() );

  if( TString(selection).Contains("2btag") ){ dotwobtag = true;
  }else                                     { dotwobtag = false; }
  if( TString(selection).Contains("bveto") ){ dobveto = true;
  }else                                     { dobveto = false; }

  if( TString(selection).Contains("mjjhi") ){ domjjhi = true;
  }else                                     { domjjhi = false; }
  if( TString(selection).Contains("mjjlo") ){ domjjlo = true;
  }else                                     { domjjlo = false; }
  
  if( TString(selection).Contains("0genbs") ){ dogenbs = true;
	ngenbs = 0;
  }else	if( TString(selection).Contains("1genbs") ){ dogenbs = true;
	ngenbs = 1;
  }else if( TString(selection).Contains("2genbs") ){ dogenbs = true;
	ngenbs = 2;
  }else                                     { dogenbs = false; }

  // if( TString(selection).Contains("mt2jhi") ){ domt2jhi = true;
  // }else                                      { domt2jhi = false; }
  // if( TString(selection).Contains("mt2jlo") ){ domt2jlo = true;
  // }else                                      { domt2jlo = false; }


};

vtxLooper::~vtxLooper()
{
};

// vtxLooper::vtxLooper( vector <double> binning )
// {

// }
void vtxLooper::setBinning( vector <double> binning )
{
  bins = binning;
  return;
}

void vtxLooper::setzvar( TH1F * &zhist )
{
  hzvar = dynamic_cast<TH1F*>(zhist->Clone("hzvar"));
  return;
}

void vtxLooper::setzmjj( TH1F * &zhist )
{
  hzmjj = dynamic_cast<TH1F*>(zhist->Clone("hzmjj"));
  return;
}

void vtxLooper::setzvtx( TH1F * &zhist )
{
  hzvtx = dynamic_cast<TH1F*>(zhist->Clone("hZ"));
  // hzvtx -> Scale ( 0.0 );
  return;
}

void vtxLooper::setgmjj( TH1F * &zhist )
{
  hgmjj = dynamic_cast<TH1F*>(zhist->Clone("hgmjj"));
  hgmjj -> Scale ( 0.0 );
  return;
}

void vtxLooper::setgvar( TH1F * &zhist )
{
  hgvar = dynamic_cast<TH1F*>(zhist->Clone("hgvar"));
  hgvar -> Scale ( 0.0 );
  // cout<<hgvar -> GetSumOfWeights()<<endl;
  return;
}

int vtxLooper::ScanChain( TChain* chain, bool fast = true, int nEvents = -1, Int_t runnumber = 0, bool isdata = false )
{

  TH1F * photon_metwithbs = new TH1F("photon_metwithbs","metwithbs", 250, 0, 250 );
  TH1F * photon_metwithcs = new TH1F("photon_metwithcs","metwithcs", 250, 0, 250 );

  //histos for mcfa stuff
  TH1F * photon_mcfabjet1 = new TH1F("photon_mcfabjet1","mcfabjet1", 9, 0, 9 );
  TH1F * photon_mcfabjet2 = new TH1F("photon_mcfabjet2","mcfabjet2", 9, 0, 9 );

  vector <string> binlabels;
  binlabels.push_back("u");
  binlabels.push_back("d");
  binlabels.push_back("s");
  binlabels.push_back("c");
  binlabels.push_back("b");
  binlabels.push_back("t");
  binlabels.push_back("gluon");
  binlabels.push_back("photon");

  for( size_t bini = 0; bini < binlabels.size(); bini++ ){
  	photon_mcfabjet1 -> GetXaxis() -> SetBinLabel( bini+2, binlabels.at(bini).c_str() );
  	photon_mcfabjet2 -> GetXaxis() -> SetBinLabel( bini+2, binlabels.at(bini).c_str() );
  }

  photon_metwithbs -> Sumw2();
  photon_metwithcs -> Sumw2();

  photon_mcfabjet1 -> Sumw2();
  photon_mcfabjet2 -> Sumw2();

  Long64_t ntotevts = 0;
  
  TFile * reweightfile = NULL;
  TH1F * ptreweightHist = NULL;
  TH1F * htreweightHist = NULL;

  // // Example Histograms
  // TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  // TH1F *samplehisto = new TH1F("samplehisto", "Example histogram", 200,0,200);
  // hgvar = new TH1F("hgvar","", nbins, binning );
  // TH1F * hzmjj =  (TH1F*)zhist->Clone("hzmjj");


  if( runnumber == 0 ){
	h20  = new TH1F("h20" ,"h20",35,0,35);
	h30  = new TH1F("h30" ,"h30",35,0,35);
	h50  = new TH1F("h50" ,"h50",35,0,35);
	h70  = new TH1F("h70" ,"h70",35,0,35);
	h90  = new TH1F("h90" ,"h90",35,0,35);

	h20 -> Sumw2();
	h30 -> Sumw2();
	h50 -> Sumw2();
	h70 -> Sumw2();
	h90 -> Sumw2();

	h20 -> Rebin(5);
	h30 -> Rebin(5);
	h50 -> Rebin(5);
	h70 -> Rebin(5);
	h90 -> Rebin(5);
  }

  //~-~-~-~-~-~-~-~-~-~-~-~-~//
  //Actual Looper starts here//
  //~-~-~-~-~-~-~-~-~-~-~-~-~//
  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  //Set btag reshaping
  BTagShapeInterface * nominalShape = 0;
  nominalShape = new BTagShapeInterface("/home/users/cwelke/CMSSW/CMSSW_5_3_2_patch4/src/CMS2/NtupleMacros/Tools/BTagReshaping/csvdiscr.root", 0.0, 0.0); 

  if( runnumber != 0 ) {
	if( !isdata ){
	  // cout<<Form( "tempfiles/vtxreweight_DoubleElectron_19fb_MC_temp%i.root", runnumber - 1 )<<endl;
	  // reweightfile = TFile::Open( Form( "tempfiles/vtxreweight_DoubleElectron_19fb_MC_temp%i.root", runnumber - 1 ), "READ");
	  // if( runnumber == 1) ptreweightHist = (TH1F*) reweightfile->Get("hptratio");	
	  // if( runnumber == 2) htreweightHist = (TH1F*) reweightfile->Get("hhtratio");	
	  reweightfile = TFile::Open( Form( "vtxreweight_DoubleElectron_19fb_MC%s.root", selection.c_str() ), "READ");
	  if( runnumber == 1){
		ptreweightHist = dynamic_cast<TH1F*>(reweightfile->Get("hptratio"));	
	  }if( runnumber == 2){
		ptreweightHist = dynamic_cast<TH1F*>(reweightfile->Get("hptratio"));	
		htreweightHist = dynamic_cast<TH1F*>(reweightfile->Get("hhtratio"));	
	  }
		
	}else{ 
	  if( runnumber != 0 ) {
		reweightfile = TFile::Open( Form( "vtxreweight_DoubleElectron_19fb_data%s.root", selection.c_str() ), "READ");
		if( runnumber == 1){
		  ptreweightHist = dynamic_cast<TH1F*>(reweightfile->Get("hptratio"));	
		}if( runnumber == 2){ 
		  ptreweightHist = dynamic_cast<TH1F*>(reweightfile->Get("hptratio"));	
		  htreweightHist = dynamic_cast<TH1F*>(reweightfile->Get("hhtratio"));	
		}
	  }
	}
  }
  
  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

	if( !currentFile || currentFile->IsZombie() ) {
	  cout << "Skipping bad input file: " << currentFile->GetTitle() << endl;
	  continue; //exit(1);                                                                                             
	}
	
	// cout<<"Running on file: "<<currentFile->GetTitle()<<endl;
	if( !isdata ){
	  cout<<currentFile->GetTitle()<<" is MC file. isdata = false"<<endl;
	  // isdata = false;
	}else{
	  cout<<currentFile->GetTitle()<<" is data file. isdata = true"<<endl;
	  // isdata = true;
	}
	
    bool isttbar = TString(currentFile->GetTitle()).Contains("ttbar_");

	// Get File Content
	TFile *file = new TFile( currentFile->GetTitle() );
	TTree *tree = (TTree*)file->Get("T1");
	if(fast) TTreeCache::SetLearnEntries(10);
	if(fast) tree->SetCacheSize(128*1024*1024);
	templates.Init(tree);
    
	// Loop over Events in current file
	if( nEventsTotal >= nEventsChain ) continue;
	unsigned int nEventsTree = tree->GetEntriesFast();
	for( unsigned int event = 0; event < nEventsTree; ++event) {
    
	  // Get Event Content
	  if( nEventsTotal >= nEventsChain ) continue;
	  if(fast) tree->LoadTree(event);
	  templates.GetEntry(event);
	  ++nEventsTotal;
    
	  // Progress
	  TEMPLATES::progress( nEventsTotal, nEventsChain );

	  double weight = 1;
	  
	  // Analysis Code
      if( templates.njets() < 2 )                                           continue; // >=2 jets
      if( templates.njets() > 3 )                                           continue; // <=3 jets
      if( templates.etg() <  20 )                                           continue; // photon pt  > 20 GeV
      if( fabs( templates.etag() ) > 2 )                                    continue; // photon eta < 2
	  if( templates.hoe() > 0.1  )                                          continue; // H/E < 0.1	  
	  if( templates.photon_pixelseed() != 0 )                               continue; // photon pixel seed
	  if( templates.jetneutralemfrac() < 0.7 )                              continue; // jet neutral EM fraction cut
      if( templates.jetpt() - templates.etg() < -5 )                        continue; // pfjet cleaning
      if( templates.elveto() == 1 )                                         continue; // remove photons with nearby electrons
      if( templates.maxleppt() > 20.0 )                                     continue; // veto leptons pt > 20 GeV
      if( acos( cos( templates.phig() - templates.pfmetphi() ) ) < 0.14 )   continue; // kill photons aligned with MET

      if( isdata && !isttbar && !(templates.csc()==0 && 
								  templates.hbhe()==1 && 
								  templates.hcallaser()==1 && 
								  templates.ecallaser()==1 && 
								  templates.ecaltp()==1 && 
								  templates.trkfail()==1 && 
								  templates.eebadsc()==1 && 
								  templates.hbhenew()==1) 
		  )                                                                 continue; // MET filters

	  if( isdata && !isttbar && ( templates.hgg22() < 1 && 
								  // templates.hgg36() < 1 && 
								  templates.hgg50() < 1 && 
								  templates.hgg75() < 1 && 
								  templates.hgg90() < 1 )
		  )                                                                 continue; // require trig

	  if( isdata && !isttbar ){
		if(       templates.hgg90() >= 1 ){
		  weight *= templates.hgg90();
		}else if( templates.hgg75() >= 1 ){
		  weight *= templates.hgg75();
		}else if( templates.hgg50() >= 1 ){
		  weight *= templates.hgg50();
		}else if( templates.hgg36() >= 1 ){
		  weight *= templates.hgg22();
		}else if( templates.hgg22() >= 1 ){
		  weight *= templates.hgg22();
		}
	  }else if( !isdata || isttbar ){
		weight = templates.weight();
		weight *= 19.5;
	  }
	  	  
	  // if( event % 12 != 0 ) continue;

	  //b-tag reshaping
	  float csv1_nominal = templates.csv1();
	  float csv2_nominal = templates.csv2();
	  float csv3_nominal = templates.csv3();	  
	  if( !isdata || isttbar ){
	  	csv1_nominal=nominalShape->reshape(templates.jet1().Eta(), 
	  									   templates.jet1().Pt(),
	  									   templates.csv1(),
	  									   templates.jet1mcfa());
	  	csv2_nominal=nominalShape->reshape(templates.jet2().Eta(), 
	  									   templates.jet2().Pt(),
	  									   templates.csv2(),
	  									   templates.jet2mcfa());
	  	csv3_nominal=nominalShape->reshape(templates.jet3().Eta(), 
	  									   templates.jet3().Pt(),
	  									   templates.csv3(),
	  									   templates.jet3mcfa());
	  }

	  vector <Float_t> csvvals;
	  csvvals.push_back(csv1_nominal);
	  csvvals.push_back(csv2_nominal);
	  csvvals.push_back(csv3_nominal);

	  Float_t mjj = 0.0;
	  Float_t csvproduct = 0.0;
	  // Float_t mT2j = 0.0;

	  if( !dobveto && !dotwobtag ){
		vector <LorentzVector> jets;
		jets.push_back(templates.jet1());
		jets.push_back(templates.jet2());
		if( templates.njets() == 3 ){ jets.push_back(templates.jet3()); }
		mjj = (jets.at(0) + jets.at(1)).mass();
		csvproduct = templates.csv1()*templates.csv2();
		// mT2j = getMT2b( leps, jets );

	  }else if( dobveto && !dotwobtag ){
		bool bveto = ( templates.nbl() < 1 );
		if( dobveto && bveto ){
		  vector <LorentzVector> jets;
		  jets.push_back(templates.jet1());
		  jets.push_back(templates.jet2());
		  if( templates.njets() == 3 ){ jets.push_back(templates.jet3()); }
		  mjj = (jets.at(0) + jets.at(1)).mass();
		  csvproduct = templates.csv1()*templates.csv2();
		  // mT2j = getMT2b( leps, jets );
		}else{ continue; }

	  }else if( !dobveto && dotwobtag ){
		// Bool_t twogoodbs = getbjets( 0.244 );	  		
		Bool_t twogoodbs = getbjets( 0.244, csvvals );	  		
		if( dotwobtag && twogoodbs ){
		  mjj = (goodbs.at(0) + goodbs.at(1)).mass();
		  csvproduct = get2btagproduct( 0.244, csvvals );
		  // mT2j = getMT2b( leps, goodbs );
		}else{ continue; }		

	  }else{
		cout<<"incosistent b-tagging selection. exiting."<<endl;
		exit(1);
	  }
	  
	  if( dogenbs && !isdata ){
		vector <Float_t> mcfavals;
		mcfavals.push_back(templates.jet1mcfa());
		mcfavals.push_back(templates.jet2mcfa());
		mcfavals.push_back(templates.jet3mcfa());

		if( ngenbs == 0 && !hasnogenbjets(  mcfavals ) ) continue;
		if( ngenbs == 1 && !hasonegenbjets( mcfavals ) ) continue;
   		if( ngenbs == 2 && !hastwogenbjets( 0.244, csvvals, mcfavals ) ) continue;
	  }

	  if( domjjhi  &&  mjj < 150.0 )                 continue;
	  if( domjjlo  && (mjj > 150.0 || mjj < 100.0) ) continue;
	  // if( domt2jhi && mT2j < 200.0 )                 continue;
	  // if( domt2jlo && mT2j > 200.0 )                 continue;

	  vector <Float_t> mcfavals;
	  Float_t mcfaproduct = 0.0;

	  if( !isdata ){
		mcfavals.push_back(templates.jet1mcfa());
		mcfavals.push_back(templates.jet2mcfa());
		mcfavals.push_back(templates.jet3mcfa());
		mcfaproduct = get2btagmcfaproduct( 0.244, csvvals, mcfavals );
	  if( dobveto ) mcfaproduct = templates.jet1mcfa()*templates.jet2mcfa();

	  }

	  if( runnumber == 0 ){
		
		if( !isdata && !isttbar ){

		  // if( templates.pfmet() > 100.0 ){
			// fillmcfahists( 0.244, photon_mcfabjet1, photon_mcfabjet2, weight );
			// }

			if( abs(templates.jet1mcfa()) != 21 && abs(templates.jet1mcfa()) != 22 ) fillHist(photon_mcfabjet1, abs(templates.jet1mcfa()), weight);
			else if( abs(templates.jet1mcfa()) == 21 )                               fillHist(photon_mcfabjet1, 7, weight);
			else if( abs(templates.jet1mcfa()) == 22 )                               fillHist(photon_mcfabjet1, 8, weight);
			if( abs(templates.jet2mcfa()) != 21 && abs(templates.jet2mcfa()) != 22 ) fillHist(photon_mcfabjet2, abs(templates.jet2mcfa()), weight);
			else if( abs(templates.jet2mcfa()) == 21 )                               fillHist(photon_mcfabjet2, 7, weight);
			else if( abs(templates.jet2mcfa()) == 22 )                               fillHist(photon_mcfabjet2, 8, weight);
		  // }

		  if( abs(templates.jet2mcfa()) == 5 ) fillHist(photon_metwithbs, templates.pfmet(), weight);
		  if( abs(templates.jet2mcfa()) == 4 ) fillHist(photon_metwithcs, templates.pfmet(), weight);
		}

		fillHist( hgvar, templates.etg(), weight );
		if(       (isdata && templates.hgg90()) || ( !isdata && (templates.etg() > 90.0                            )) ){ fillHist( h90, templates.nvtx(), weight );
		}else if( (isdata && templates.hgg75()) || ( !isdata && (templates.etg() > 75.0 && templates.etg() <= 90.0 )) ){ fillHist( h70, templates.nvtx(), weight );
		}else if( (isdata && templates.hgg50()) || ( !isdata && (templates.etg() > 50.0 && templates.etg() <= 75.0 )) ){ fillHist( h50, templates.nvtx(), weight );
		}else if( (isdata && templates.hgg36()) || ( !isdata && (templates.etg() > 36.0 && templates.etg() <= 50.0 )) ){ fillHist( h30, templates.nvtx(), weight );
		}else if( (isdata && templates.hgg22()) || ( !isdata && (templates.etg() > 22.0 && templates.etg() <= 36.0 )) ){ fillHist( h20, templates.nvtx(), weight );
		}
	  }else if( runnumber == 1 ){
		weight *= ptreweightHist->GetBinContent( min( ptreweightHist->FindBin( templates.etg() )
													  , ptreweightHist->GetNbinsX() ) ); 
		// if(      templates.njets() == 2 )		fillHist( hgvar, templates.jet1().pt() + templates.jet2().pt(), weight);
		// else if( templates.njets() == 3 )		fillHist( hgvar, templates.jet1().pt() + templates.jet2().pt() + templates.jet3().pt(), weight);
		fillHist( hgvar, templates.ht(),  weight );
	  }else if( runnumber == 2 ){
		// weight *= ptreweightHist->GetBinContent( min( ptreweightHist->FindBin( templates.etg() )
		// 											  , ptreweightHist->GetNbinsX() ) ); 
		weight *= htreweightHist->GetBinContent( min( htreweightHist->FindBin( templates.ht() )
													  , htreweightHist->GetNbinsX() ) ); 

		// fillHist( hgmjj, mcfaproduct, weight);
		fillHist( hgmjj, csvproduct, weight );
		// fillHist( hgmjj, (templates.jet1() + templates.jet2()).mass(), weight );
		// fillHist( hgmjj, (templates.jet1() + templates.jet2()).mass(), weight );
	  }
	  
	  ntotevts++;	  
	}
  
	// Clean Up
	delete tree;
	file->Close();
	delete file;
  }
  if ( nEventsChain != nEventsTotal ) {
	cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  
  // Example Histograms
  // samplehisto->Draw();
  
  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << ntotevts     << " Events Passing"   << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  if( runnumber != 0 ) reweightfile -> Close();

  TH1F * hzmjjnorm = NULL;
  TH1F * hgmjjnorm = NULL;
  TH1F * hzvarnorm = NULL;
  TH1F * hgvarnorm = NULL;
  TH1F * hratio    = NULL;
  TH1F * hmjjratio = NULL;
  TH1F * hratio20  = NULL;
  TH1F * hratio30  = NULL;
  TH1F * hratio50  = NULL;
  TH1F * hratio70  = NULL;
  TH1F * hratio90  = NULL;

  if( runnumber == 0 ){
	hratio20 = dynamic_cast<TH1F*>(hzvtx->Clone("hratio20"));
	hratio30 = dynamic_cast<TH1F*>(hzvtx->Clone("hratio30"));
	hratio50 = dynamic_cast<TH1F*>(hzvtx->Clone("hratio50"));
	hratio70 = dynamic_cast<TH1F*>(hzvtx->Clone("hratio70"));
	hratio90 = dynamic_cast<TH1F*>(hzvtx->Clone("hratio90"));

	hzvarnorm = dynamic_cast<TH1F*>(hzvar -> Clone("hzptnorm"));
	hgvarnorm = dynamic_cast<TH1F*>(hgvar -> Clone("hgptnorm"));
	hratio    = dynamic_cast<TH1F*>(hzvar -> Clone("hptratio"));

	hratio20 -> Scale ( 1.0 / hratio20 -> GetSumOfWeights() );
	hratio30 -> Scale ( 1.0 / hratio30 -> GetSumOfWeights() );
	hratio50 -> Scale ( 1.0 / hratio50 -> GetSumOfWeights() );
	hratio70 -> Scale ( 1.0 / hratio70 -> GetSumOfWeights() );
	hratio90 -> Scale ( 1.0 / hratio90 -> GetSumOfWeights() );

	h20 -> Scale ( 1.0 / h20 -> GetSumOfWeights() );
	h30 -> Scale ( 1.0 / h30 -> GetSumOfWeights() );
	h50 -> Scale ( 1.0 / h50 -> GetSumOfWeights() );
	h70 -> Scale ( 1.0 / h70 -> GetSumOfWeights() );
	h90 -> Scale ( 1.0 / h90 -> GetSumOfWeights() );

	hratio20 -> Divide( h20 );
	hratio30 -> Divide( h30 );
	hratio50 -> Divide( h50 );
	hratio70 -> Divide( h70 );
	hratio90 -> Divide( h90 );

  }else if( runnumber == 1 ){

	hzvarnorm = dynamic_cast<TH1F*>(hzvar->Clone("hzhtnorm"));
	hgvarnorm = dynamic_cast<TH1F*>(hgvar->Clone("hghtnorm"));
	hratio    = dynamic_cast<TH1F*>(hzvar->Clone("hhtratio"));

  }else if( runnumber == 2 ){

	hzmjjnorm = dynamic_cast<TH1F*>(hzmjj -> Clone("hzmjjnorm"));
	hgmjjnorm = dynamic_cast<TH1F*>(hgmjj -> Clone("hgmjjnorm"));
	hgmjjnorm -> Scale ( 1.0/ hgmjjnorm -> GetSumOfWeights() );
	hzmjjnorm -> Scale ( 1.0/ hzmjjnorm -> GetSumOfWeights() );
	hmjjratio = dynamic_cast<TH1F*>(hzmjj->Clone("hmjjratio"));
	hmjjratio -> Scale ( 1.0 / hmjjratio -> GetSumOfWeights() );
	hmjjratio -> Divide(hgmjjnorm);  
	
  }

  if( runnumber != 2 ){
	hgvarnorm -> Scale ( 1.0/ hgvarnorm -> GetSumOfWeights() );
	hzvarnorm -> Scale ( 1.0/ hzvarnorm -> GetSumOfWeights() );
	hratio -> Scale ( 1.0 / hratio -> GetSumOfWeights() );
	hratio -> Divide(hgvarnorm);  
  }  

  TFile * fratio = NULL;
  TFile * finalratio = NULL;
  if( runnumber == 0 ){	
	if( !isdata ){
	  cout<<Form( "tempfiles/vtxreweight_DoubleElectron_19fb_MC%s_temp%i.root", selection.c_str(), runnumber )<<endl;
	  fratio = TFile::Open( Form( "tempfiles/vtxreweight_DoubleElectron_19fb_MC%s_temp%i.root", selection.c_str(), runnumber ), "RECREATE");
	  finalratio = TFile::Open( Form( "vtxreweight_DoubleElectron_19fb_MC%s.root", selection.c_str() ), "RECREATE");
	}else{ 
	  fratio = TFile::Open( Form( "tempfiles/vtxreweight_DoubleElectron_19fb_data%s_temp%i.root", selection.c_str(), runnumber ), "RECREATE");
	  finalratio = TFile::Open( Form( "vtxreweight_DoubleElectron_19fb_data%s.root", selection.c_str() ), "RECREATE");
	}
  }else if( runnumber != 0 ){
	if( !isdata ){
	  fratio = TFile::Open( Form( "tempfiles/vtxreweight_DoubleElectron_19fb_MC%s_temp%i.root", selection.c_str(), runnumber ), "RECREATE");
	  finalratio = TFile::Open( Form( "vtxreweight_DoubleElectron_19fb_MC%s.root", selection.c_str() ), "UPDATE");
	}else{
	  fratio = TFile::Open( Form( "tempfiles/vtxreweight_DoubleElectron_19fb_data%s_temp%i.root", selection.c_str(), runnumber ), "RECREATE");
	  finalratio = TFile::Open( Form( "vtxreweight_DoubleElectron_19fb_data%s.root", selection.c_str() ), "UPDATE");
	}
  }

  fratio->cd();
  if( runnumber == 0 ){
	dynamic_cast<TH1F*>(hgvar -> Clone("gPt")) -> Write();
	dynamic_cast<TH1F*>(hzvar -> Clone("ZPt")) -> Write();
	hratio20 -> Write();
	hratio30 -> Write();
	hratio50 -> Write();
	hratio70 -> Write();
	hratio90 -> Write();
  }else if( runnumber == 1 ){
	dynamic_cast<TH1F*>(hgvar -> Clone("gHt")) -> Write();
	dynamic_cast<TH1F*>(hzvar -> Clone("ZHt")) -> Write();
  }else if( runnumber == 2 ){
	hzmjj -> Write();
	hgmjj -> Write();
	hzmjjnorm -> Write();
	hgmjjnorm -> Write();
	hmjjratio -> Write();
  }
  if( runnumber != 2 ){
	hgvarnorm -> Write();
	hzvarnorm -> Write();
	hratio -> Write();
  }
  fratio -> Close();

	
  TFile * zfile;
  if( !isdata ){
	zfile = TFile::Open(Form("tempfiles/vtxreweight_DoubleElectron_19fb_MC%s_temp.root", selection.c_str() ), "READ");
  }else{
	zfile = TFile::Open(Form("tempfiles/vtxreweight_DoubleElectron_19fb_data%s_temp.root", selection.c_str() ), "READ");
  }

  finalratio->cd();
  if( runnumber == 0 ){
	dynamic_cast<TH1F*>(hgvar -> Clone("gPt")) -> Write();
	dynamic_cast<TH1F*>(hzvar -> Clone("ZPt")) -> Write();
	hratio20 -> Write();
	hratio30 -> Write();
	hratio50 -> Write();
	hratio70 -> Write();
	hratio90 -> Write();

	dynamic_cast<TH1F*>(zfile -> Get( "hZHt_compare" )) -> Write();
	dynamic_cast<TH1F*>(zfile -> Get( "hZPt_compare" )) -> Write();

	if( !isdata ){
	  photon_mcfabjet1 -> Write();
	  photon_mcfabjet2 -> Write();
	  photon_metwithbs -> Write();
	  photon_metwithcs -> Write();
	  dynamic_cast<TH1F*>(zfile -> Get( "z_mcfabjet1" )) -> Write();
	  dynamic_cast<TH1F*>(zfile -> Get( "z_mcfabjet2" )) -> Write();
	  dynamic_cast<TH1F*>(zfile -> Get( "z_metwithbs" )) -> Write();
	  dynamic_cast<TH1F*>(zfile -> Get( "z_metwithcs" )) -> Write();
	}

  }else if( runnumber == 1 ){
	dynamic_cast<TH1F*>(hgvar -> Clone("gHt")) -> Write();
	dynamic_cast<TH1F*>(hzvar -> Clone("ZHt")) -> Write();
  }else if( runnumber == 2 ){
	hzmjj -> Write();
	hgmjj -> Write();
	hzmjjnorm -> Write();
	hgmjjnorm -> Write();
	hmjjratio -> Write();
  }
  if( runnumber != 2 ){
	hgvarnorm -> Write();
	hzvarnorm -> Write();
	hratio -> Write();
  }
  finalratio -> Close();

  zfile -> Close();


  return 0;
}

bool vtxLooper::getbjets( const Float_t workingpoint )
{
  bool twogoodjets = false;
  goodbs.clear();
  if(       templates.csv1() >= workingpoint && templates.csv2() >= workingpoint && templates.csv3() < workingpoint ){
	goodbs.push_back(templates.jet1());
	goodbs.push_back(templates.jet2());
	twogoodjets = true;
  }else if( templates.csv1() >= workingpoint && templates.csv3() >= workingpoint && templates.csv2() < workingpoint ){
	goodbs.push_back(templates.jet1());
	goodbs.push_back(templates.jet3());
	twogoodjets = true;
  }else if( templates.csv2() >= workingpoint && templates.csv3() >= workingpoint && templates.csv1() < workingpoint ){
	goodbs.push_back(templates.jet2());
	goodbs.push_back(templates.jet3());
	twogoodjets = true;
  }
  return twogoodjets;
}

bool vtxLooper::getbjets( const Float_t workingpoint, const vector <Float_t> &csvvals )
{
  bool twogoodjets = false;
  goodbs.clear();
  if(       csvvals.at(0) >= workingpoint && csvvals.at(1) >= workingpoint && csvvals.at(2) < workingpoint ){
	goodbs.push_back(templates.jet1());
	goodbs.push_back(templates.jet2());
	twogoodjets = true;
  }else if( csvvals.at(0) >= workingpoint && csvvals.at(2) >= workingpoint && csvvals.at(1) < workingpoint ){
	goodbs.push_back(templates.jet1());
	goodbs.push_back(templates.jet3());
	twogoodjets = true;
  }else if( csvvals.at(1) >= workingpoint && csvvals.at(2) >= workingpoint && csvvals.at(0) < workingpoint ){
	goodbs.push_back(templates.jet2());
	goodbs.push_back(templates.jet3());
	twogoodjets = true;
  }
  return twogoodjets;
}


void vtxLooper::fillmcfahists( const Float_t workingpoint, TH1F * &photon_mcfabjet1, TH1F * &photon_mcfabjet2, const double weight ){
  if(       templates.csv1() >= workingpoint && templates.csv2() >= workingpoint && templates.csv3() < workingpoint ){
	// fillHist(photon_mcfabjet1, abs(templates.jet1mcfa()), weight);
	// fillHist(photon_mcfabjet2, abs(templates.jet2mcfa()), weight);
	if( abs(templates.jet1mcfa()) != 21 && abs(templates.jet1mcfa()) != 22 ) fillHist(photon_mcfabjet1, abs(templates.jet1mcfa()), weight);
	else if( abs(templates.jet1mcfa()) == 21 )                               fillHist(photon_mcfabjet1, 7, weight);
	else if( abs(templates.jet1mcfa()) == 22 )                               fillHist(photon_mcfabjet1, 8, weight);
	if( abs(templates.jet2mcfa()) != 21 && abs(templates.jet2mcfa()) != 22 ) fillHist(photon_mcfabjet2, abs(templates.jet2mcfa()), weight);
	else if( abs(templates.jet2mcfa()) == 21 )                               fillHist(photon_mcfabjet2, 7, weight);
	else if( abs(templates.jet2mcfa()) == 22 )                               fillHist(photon_mcfabjet2, 8, weight);

  }else if( templates.csv1() >= workingpoint && templates.csv3() >= workingpoint && templates.csv2() < workingpoint ){
	// fillHist(photon_mcfabjet1, abs(templates.jet1mcfa()), weight);
	// fillHist(photon_mcfabjet2, abs(templates.jet3mcfa()), weight);
	if( abs(templates.jet1mcfa()) != 21 && abs(templates.jet1mcfa()) != 22 ) fillHist(photon_mcfabjet1, abs(templates.jet1mcfa()), weight);
	else if( abs(templates.jet1mcfa()) == 21 )                               fillHist(photon_mcfabjet1, 7, weight);
	else if( abs(templates.jet1mcfa()) == 22 )                               fillHist(photon_mcfabjet1, 8, weight);
	if( abs(templates.jet3mcfa()) != 21 && abs(templates.jet3mcfa()) != 22 ) fillHist(photon_mcfabjet2, abs(templates.jet3mcfa()), weight);
	else if( abs(templates.jet3mcfa()) == 21 )                               fillHist(photon_mcfabjet2, 7, weight);
	else if( abs(templates.jet3mcfa()) == 22 )                               fillHist(photon_mcfabjet2, 8, weight);

  }else if( templates.csv2() >= workingpoint && templates.csv3() >= workingpoint && templates.csv1() < workingpoint ){
	// fillHist(photon_mcfabjet1, abs(templates.jet2mcfa()), weight);
	// fillHist(photon_mcfabjet2, abs(templates.jet3mcfa()), weight);
	if( abs(templates.jet2mcfa()) != 21 && abs(templates.jet2mcfa()) != 22 ) fillHist(photon_mcfabjet1, abs(templates.jet2mcfa()), weight);
	else if( abs(templates.jet2mcfa()) == 21 )                               fillHist(photon_mcfabjet1, 7, weight);
	else if( abs(templates.jet2mcfa()) == 22 )                               fillHist(photon_mcfabjet1, 8, weight);
	if( abs(templates.jet3mcfa()) != 21 && abs(templates.jet3mcfa()) != 22 ) fillHist(photon_mcfabjet2, abs(templates.jet3mcfa()), weight);
	else if( abs(templates.jet3mcfa()) == 21 )                               fillHist(photon_mcfabjet2, 7, weight);
	else if( abs(templates.jet3mcfa()) == 22 )                               fillHist(photon_mcfabjet2, 8, weight);

  }
  return;
}

void vtxLooper::fillHist( TH1F* &hist, double variable, const double weight )
{
  float min = hist->GetXaxis()->GetXmin();
  float max = hist->GetXaxis()->GetXmax();
  if (variable > max) variable = hist->GetBinCenter(hist->GetNbinsX());
  if (variable < min) variable = hist->GetBinCenter(1);
  hist->Fill(variable, weight);
  return;
}
