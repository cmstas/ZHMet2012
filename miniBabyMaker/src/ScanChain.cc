//c stuff
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

//root stuff
#include "TSystem.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TFile.h"
#include "TTree.h"
#include "TBenchmark.h"
#include "TDirectory.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TString.h"

//stuff from tools
#include "goodrun.h"

//stuff from CMS2
#include "metTemplatesSelections.h"
#include "MT2/MT2.h"

//stuff from my tools
#include "eventFilter.h"
#include "genbtagTools.h"
#include "jetUtils.h"


//stuff from tools/BTagReshaping
#include "BTagReshaping.h"

//stuff from include
#include "ScanChain.h"
#include "ZMET.h"

using namespace std;
// using namespace ZMet;

// typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
//3.14159265358979323846

miniBabyMaker::miniBabyMaker()
{

  babyFileName_ = "test_baby.root";

  babyTree_ = NULL;

  babyFile_ = NULL;
  luminosity = 19.5;

  MakeBabyNtuple();

}

miniBabyMaker::~miniBabyMaker(){
  delete babyFile_;
  // delete templatefile_;
  // delete templatefile_;
}

int miniBabyMaker::ScanChain( TChain * chain, int nEvents, string suffix ){

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");


  // Loop over events to Analyze
  long i_permilleOld = 0;
  unsigned long nEventsTotal = 0;
  unsigned long nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  // //Set btag reshaping
  // BTagShapeInterface * nominalShape = 0;
  // nominalShape = new BTagShapeInterface("/home/users/cwelke/CMSSW/CMSSW_5_3_2_patch4/src/CMS2/NtupleMacros/Tools/BTagReshaping/csvdiscr.root", 0.0, 0.0); 

  //~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
  //Set the histograms and output file
  //~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
  // bookHists();

  //~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
  //set json file
  //~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
  // set_goodrun_file("/home/users/benhoob/ZMet2012/jsons/final_19p47fb_cms2.txt");

  //json for moriond
  // set_goodrun_file("/home/users/benhoob/ZMet2012/jsons/Merged_190456-208686_8TeV_PromptReReco_Collisions12_goodruns.txt");
  // set_goodrun_file_json("/home/users/cwelke/ZAnalysis/Spring2013/mainLooper/all2012.txt");
  set_goodrun_file("json/alldata_flat.txt");

  //json for hcp
  // set_goodrun_file("/home/users/benhoob/ZMet2012/jsons/Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON_goodruns.txt");

  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile *file = new TFile( currentFile->GetTitle() ); 
    TTree *tree = dynamic_cast<TTree*>(file->Get("T1"));

	cout<<"Loading file: "<<currentFile->GetTitle()<<endl;

    zmet.Init(tree);
    unsigned int nEventsTree = tree->GetEntries(); 
    for( unsigned long event = 0; event < nEventsTree; ++event) {
    
      // Get Event Content
      if( nEventsTotal >= nEventsChain ) continue;
      tree->LoadTree(event);
      zmet.GetEntry(event);
      ++nEventsTotal;

	  // pogress
	  long i_permille = (long)floor(1000 * nEventsTotal / double(nEventsChain));
	  if (i_permille != i_permilleOld) {
		printf("  \015\033[32m ---> \033[1m\033[31m%4.1f%%" "\033[0m\033[32m <---\033[0m\015", i_permille/10.);
		fflush(stdout);
		i_permilleOld = i_permille;
	  }

	  //initialize mini baby
	  Initialize();

	  //parse events from json
	  if( zmet.isdata() ){
		if( !goodrun_json( zmet.run(), zmet.lumi() ) ){continue;}
		DorkyEventIdentifier id = { zmet.run(),zmet.event(), zmet.lumi() };
		if ( is_duplicate( id ) ){
		  // cout << "\t! ERROR: found duplicate." << endl;
		  // nDuplicates++;
		  continue;
		}
	  }
	  
	  //~-~-~-~-~-~-~-~-~-//
	  //Analysis Code Here//
	  //~-~-~-~-~-~-~-~-~-//
	  double weight = 1;
	  if( !zmet.isdata() ){
		weight *= zmet.vtxweight();
		weight *= zmet.trgeff();	   
	  	weight *= luminosity;
	  }else if (zmet.isdata()                                                            ){
	  	weight = 1;
	  }

	  // if( TString(currentFile->GetTitle()).Contains("zjets_") ) {
	  // 	if( zmet.nwzpartons() > 0 ){
	  // 	  continue;
	  // 	}
	  // }

	  //Selection starts here
	  if(zmet.isdata() ){
		if(!(zmet.csc()==0 && 
			 zmet.hbhe()==1 && 
			 zmet.hcallaser()==1 && 
			 zmet.ecallaser()==1 && 
			 zmet.ecaltp()==1 && 
			 zmet.trkfail()==1 && 
			 zmet.eebadsc()==1 && 
			 zmet.hbhenew()==1))                                continue;//met filter variables and trigger variables
	  }

	  // if( zmet.pfTau_leadPtcandID() != (-1) )                   continue;//tau veto	  
	  if( zmet.lep1().pt() < 20.0 )                             continue;
	  if( zmet.lep2().pt() < 20.0 )                             continue;//pT > (20,20)
	  if(zmet.isdata()){
		if( zmet.leptype()==0 ){
		  if( zmet.ee()==0 )	                                continue;
		}
		else if( zmet.leptype()==1 ){
		  if( zmet.mm()==0 && zmet.mmtk() == 0 )                continue;
		}
		else if( zmet.leptype()==2 ){
		  if( zmet.em()==0 && zmet.me()==0 )			        continue;
		}
	  }

	  int evt_njets = 0;
	  float evt_ht  = 0;
	  if( true ){
		evt_njets = zmet.njets40();
		evt_ht    = zmet.ht40();
	  }else{
		evt_njets = zmet.njets();
		evt_ht    = zmet.sumjetpt();
	  }

	  if(                evt_njets < 2 ){                                    continue;}//jet selection 

	  if( zmet.dilmass()<81.0 || zmet.dilmass()>101.0 )		    continue;//zveto medium
	  // if( zmet.dilmass()<86.0 || zmet.dilmass()>96.0 )		    continue;//zveto tight
	  if(zmet.leptype() == 2)	continue;//no more use for OF events after this point

	  lep1_ = &zmet.lep1();
	  lep2_ = &zmet.lep2();

	  lep1pt_ = zmet.lep1().pt();
	  lep2pt_ = zmet.lep2().pt();

	  FillBabyNtuple();

	}
	// Clean Up
    delete tree;
    file->Close();
  }


  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", (int)nEventsChain, (int)nEventsTotal ) << endl;
  }

  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;

  cout << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  cout<<"Writing baby to: "<<babyFileName_<<endl;
  babyFile_->cd();
  babyFile_->Write();
  babyFile_->Close();
  return 0;

}

void miniBabyMaker::MakeBabyNtuple()
{

  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  rootdir->cd();

  babyFile_ = new TFile(Form("output/%s", babyFileName_.c_str()), "RECREATE");
  babyFile_->cd();
  babyTree_ = new TTree("T1", "mini baby for Z-Analysis");

  //event stuff
  babyTree_->Branch("lep1"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &lep1_	);
  babyTree_->Branch("lep2"    , "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >", &lep2_	);

  babyTree_->Branch("lep1pt"  , &lep1pt_,      "lep1pt/F" );
  babyTree_->Branch("lep2pt"  , &lep2pt_,      "lep2pt/F" );

}

void miniBabyMaker::Initialize()
{

  lep1_ = 0;
  lep2_ = 0;

  lep1pt_ = -999.9;
  lep2pt_ = -999.9;

}

void miniBabyMaker::FillBabyNtuple()
{
  babyTree_->Fill();
}

// void makeBranches(TTree * tree){

// tree->Branch("templatemet", "TH1F", &pfNonBjets_p4_);

// }

