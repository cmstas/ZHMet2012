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
  goodrunfilename_ = "";

  babyTree_ = NULL;
  babyFile_ = NULL;
  luminosity_ = 1.0;

  MakeBabyNtuple();

}

miniBabyMaker::miniBabyMaker( string babyfilename = "test" )
{
  babyFileName_ = Form("%s_baby.root", babyfilename.c_str());
  goodrunfilename_ = "";

  babyTree_ = NULL;
  babyFile_ = NULL;
  luminosity_ = 1.0;

  MakeBabyNtuple();

}

miniBabyMaker::~miniBabyMaker(){
  delete babyFile_;
}

int miniBabyMaker::ScanChain( TChain * chain, int nEvents, string suffix ){

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Loop over events to Analyze
  long i_permilleOld = 0;
  unsigned long nEventsTotal = 0;
  unsigned long nDuplicates = 0;
  unsigned long nBadEvents  = 0;
  unsigned long nEventsPass = 0;
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
  if( goodrunfilename_ != "" ) set_goodrun_file(goodrunfilename_.c_str());

  //~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
  //Start file loop
  //~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
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
	  if( goodrunfilename_ != "" ){
		if( zmet.isdata() ){
		  if( !goodrun_json( zmet.run(), zmet.lumi() ) ){
			nBadEvents++;
			continue;
		  }
		}
	  }

	  if( zmet.isdata() ){
		DorkyEventIdentifier id = { zmet.run(), zmet.event(), zmet.lumi() };
		if ( is_duplicate( id ) ){
		  // cout << "\t! ERROR: found duplicate." << endl;
		  nDuplicates++;
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
	  	weight *= luminosity_;
	  }else if (zmet.isdata()                                                            ){
	  	weight = 1;
	  }

	  // if( TString(currentFile->GetTitle()).Contains("zjets_") ) {
	  // 	if( zmet.nwzpartons() > 0 ){
	  // 	  continue;
	  // 	}
	  // }

	  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
	  //Selection starts here
	  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
	  if(zmet.isdata() ){
		if(!(zmet.csc()==0 && 
			 zmet.hbhe()==1 && 
			 zmet.hcallaser()==1 && 
			 zmet.ecallaser()==1 && 
			 zmet.ecaltp()==1 && 
			 zmet.trkfail()==1 && 
			 zmet.eebadsc()==1 && 
			 zmet.hbhenew()==1))                                continue;//met filters
	  }

	  if(zmet.isdata()){                                                 //triggers
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

	  // if( zmet.pfTau_leadPtcandID() != (-1) )                   continue;//tau veto	  
	  if( zmet.lep1().pt() < 20.0 )                             continue;
	  if( zmet.lep2().pt() < 20.0 )                             continue;//pT > (20,20)

	  int evt_njets = 0;
	  float evt_ht  = 0;
		evt_njets = zmet.njets40();
		evt_ht    = zmet.ht40();


	  if( evt_njets < 2 ) continue;
	  if( !(evt_ht > 0.0) ) continue;

	  //*****************************
	  //set branch variables
	  //*****************************

	  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
	  //event variables
	  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
	  run_     = zmet.run();
	  lumi_    = zmet.lumi();
	  event_   = zmet.event();
	  isdata_ = zmet.isdata();

	  pfmet_    = zmet.pfmet();
	  pfmetphi_ = zmet.pfmetphi();

	  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
	  //jet variables
	  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
	  if( evt_njets > 0 ){
		jet1_    = &zmet.jet1();
		csv1_old_ = zmet.csv1();
	  }

	  if( evt_njets > 1 ){
		jet2_    = &zmet.jet2();
		csv2_old_ = zmet.csv2();
		mjj_  = ( zmet.jet1() + zmet.jet2() ).mass();
		ptjj_ = ( zmet.jet1() + zmet.jet2() ).pt();
		mt2j_ = zmet.mt2j();
	  }

	  if( evt_njets > 2 ){
		jet3_    = &zmet.jet3();
		csv3_old_ = zmet.csv3();
	  }

	  if( evt_njets > 3 ){
		jet4_    = &zmet.jet4();
		csv4_old_ = zmet.csv4();
	  }

	  njets_ = evt_njets;
	  ht_    = evt_ht;

	  // //add these later
	  // babyTree_->Branch("csv1",      &csv1_,       "csv1/F" );
	  // babyTree_->Branch("csv2",      &csv2_,       "csv2/F" );
	  // babyTree_->Branch("csv3",      &csv3_,       "csv3/F" );
	  // babyTree_->Branch("csv4",      &csv4_,       "csv4/F" );

	  // //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
	  // //bjet variables - assume medium btagging unless otherwise specified
	  // //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
	  // bjet1_ = 0;
	  // bjet2_ = 0;
	  // bjet3_ = 0;
	  // bjet4_ = 0;

	  // nbcsvl_ = -999;
	  // nbcsvm_ = -999;
	  // nbcsvt_ = -999;

	  // nbcsvl_old_ = -999;
	  // nbcsvm_old_ = -999;
	  // nbcsvt_old_ = -999;

	  // mbb_ = -999.9;
	  // ptbb_ = -999.9;
	  // mt2b_ = -999.9;


	  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
	  //lepton variables
	  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
	  hastau_ = zmet.pfTau_leadPtcandID() != (-1);

	  mll_  = ( zmet.lep1() + zmet.lep2() ).mass();
	  ptll_ = ( zmet.lep1() + zmet.lep2() ).pt();

	  leptype_ = zmet.leptype();

	  lep1_    = &zmet.lep1();
	  lep2_    = &zmet.lep2();
	  lep3_    = &zmet.lep3();

	  lep1pt_  = zmet.lep1().pt();
	  lep2pt_  = zmet.lep2().pt();
	  lep3pt_  = zmet.lep3().pt();

	  // lep1dz_  = zmet.lep1Dz();
	  // lep2dz_  = zmet.lep2Dz();
	  // // lep3dz_  = zmet.lep3Dz();

	  // lep1iso_ = zmet.lep1iso();
	  // lep2iso_ = zmet.lep2iso();
	  // // lep3iso_ = zmet.lep3iso();

	  // lep1d0_  = zmet.lep1D0();
	  // lep2d0_  = zmet.lep2D0();
	  // // lep3d0_  = zmet.lep3D0();

	  nEventsPass++;
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
  cout << nBadEvents   << " Events Failed goodrun" << endl;
  cout << nEventsPass  << " Events Passing" << endl;
  cout << nDuplicates  << " Duplicate events in data" << endl;

  cout << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  cout<<"Writing baby to: "<<babyFileName_<<endl;
  // babyFile_->cd();
  babyFile_->Write();
  babyFile_->Close();
  return 0;

}

void miniBabyMaker::MakeBabyNtuple()
{

  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  rootdir->cd();

  babyFile_ = new TFile(Form("output/miniBabies/%s", babyFileName_.c_str()), "RECREATE");
  babyFile_->cd();
  babyTree_ = new TTree("T1", "mini baby for Z-Analysis");


  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //event variables
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  babyTree_->Branch("run",      &run_,         "run/I" );
  babyTree_->Branch("lumi",     &lumi_,        "lumi/I" );
  babyTree_->Branch("event",    &event_,       "event/I" );
  babyTree_->Branch("isdata",   &isdata_,      "isdata/B" );

  babyTree_->Branch("pfmet",    &pfmet_,       "pfmet/F" );
  babyTree_->Branch("pfmetphi", &pfmetphi_,    "pfmetphi/F" );

  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //jet variables
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  babyTree_->Branch("jet1",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &jet1_	);
  babyTree_->Branch("jet2",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &jet2_	);
  babyTree_->Branch("jet3",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &jet3_	);
  babyTree_->Branch("jet4",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &jet4_	);

  babyTree_->Branch("njets",     &njets_,      "njets/I" );
  babyTree_->Branch("ht",        &ht_,         "ht/F" );

  babyTree_->Branch("mjj",       &mjj_,        "mjj/F" );//leading jets
  babyTree_->Branch("ptjj",      &ptjj_,       "ptjj/F" );//leading jets
  babyTree_->Branch("mt2j",      &mt2j_,       "mt2j/F" );

  babyTree_->Branch("csv1",      &csv1_,       "csv1/F" );
  babyTree_->Branch("csv2",      &csv2_,       "csv2/F" );
  babyTree_->Branch("csv3",      &csv3_,       "csv3/F" );
  babyTree_->Branch("csv4",      &csv4_,       "csv4/F" );

  babyTree_->Branch("csv1_old",  &csv1_old_,   "csv1_old/F" );
  babyTree_->Branch("csv2_old",  &csv2_old_,   "csv2_old/F" );
  babyTree_->Branch("csv3_old",  &csv3_old_,   "csv3_old/F" );
  babyTree_->Branch("csv4_old",  &csv4_old_,   "csv4_old/F" );

  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //bjet variables - assume medium btagging unless otherwise specified
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  babyTree_->Branch("bjet1",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &bjet1_	);
  babyTree_->Branch("bjet2",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &bjet2_	);
  babyTree_->Branch("bjet3",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &bjet3_	);
  babyTree_->Branch("bjet4",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &bjet4_	);

  babyTree_->Branch("nbcsvl",      &nbcsvl_,       "nbcsvl/I" );
  babyTree_->Branch("nbcsvm",      &nbcsvm_,       "nbcsvm/I" );
  babyTree_->Branch("nbcsvt",      &nbcsvt_,       "nbcsvt/I" );

  babyTree_->Branch("nbcsvl_old",  &nbcsvl_old_,   "nbcsvl_old/I" );
  babyTree_->Branch("nbcsvm_old",  &nbcsvm_old_,   "nbcsvm_old/I" );
  babyTree_->Branch("nbcsvt_old",  &nbcsvt_old_,   "nbcsvt_old/I" );

  babyTree_->Branch("mbb",         &mbb_,          "mbb/F" );
  babyTree_->Branch("ptbb",        &ptbb_,         "ptbb/F" );
  babyTree_->Branch("mt2b",        &mt2b_,         "mt2b/F" );

  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //lepton variables
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  babyTree_->Branch("lep1",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &lep1_	);
  babyTree_->Branch("lep2",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &lep2_	);
  babyTree_->Branch("lep3",   "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >",   &lep3_	);

  babyTree_->Branch("mll",      &mll_,         "mll/F" );//leading leps
  babyTree_->Branch("ptll",     &ptll_,        "ptll/F" );//leading leps

  babyTree_->Branch("hastau",   &hastau_,      "hastau/B" );

  babyTree_->Branch("leptype",  &leptype_,     "leptype/I" );

  babyTree_->Branch("lep1pt",   &lep1pt_,      "lep1pt/F"  );
  babyTree_->Branch("lep2pt",   &lep2pt_,      "lep2pt/F"  );
  babyTree_->Branch("lep3pt",   &lep3pt_,      "lep3pt/F"  );

  babyTree_->Branch("lep1dz",   &lep1dz_,      "lep1dz/F"  );
  babyTree_->Branch("lep2dz",   &lep2dz_,      "lep2dz/F"  );
  babyTree_->Branch("lep3dz",   &lep3dz_,      "lep3dz/F"  );

  babyTree_->Branch("lep1iso",  &lep1iso_,     "lep1iso/F" );
  babyTree_->Branch("lep2iso",  &lep2iso_,     "lep2iso/F" );
  babyTree_->Branch("lep3iso",  &lep3iso_,     "lep3iso/F" );

  babyTree_->Branch("lep1d0",   &lep1d0_,      "lep1d0/F"  );
  babyTree_->Branch("lep2d0",   &lep2d0_,      "lep2d0/F"  );
  babyTree_->Branch("lep3d0",   &lep3d0_,      "lep3d0/F"  );

}

void miniBabyMaker::Initialize()
{

  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //event variables
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  run_      = -999;
  lumi_     = -999;
  event_    = -999;
  isdata_   = false;

  pfmet_    = -999.9;
  pfmetphi_ = -999.9;

  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //jet variables
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  jet1_ = 0;
  jet2_ = 0;
  jet3_ = 0;
  jet4_ = 0;

  njets_ = -999;
  ht_    = -999.9;

  mjj_ = -999.9;//leading jets
  ptjj_ = -999.9;
  mt2j_ = -999.9;

  csv1_ = -999.9;
  csv2_ = -999.9;
  csv3_ = -999.9;
  csv4_ = -999.9;

  csv1_old_ = -999.9;
  csv2_old_ = -999.9;
  csv3_old_ = -999.9;
  csv4_old_ = -999.9;

  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //bjet variables - assume medium btagging unless otherwise specified
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  bjet1_ = 0;
  bjet2_ = 0;
  bjet3_ = 0;
  bjet4_ = 0;

  nbcsvl_ = -999;
  nbcsvm_ = -999;
  nbcsvt_ = -999;

  nbcsvl_old_ = -999;
  nbcsvm_old_ = -999;
  nbcsvt_old_ = -999;

  mbb_  = -999.9;
  ptbb_ = -999.9;
  mt2b_ = -999.9;

  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //lepton variables
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  lep1_ = 0;
  lep2_ = 0;
  lep3_ = 0;

  mll_  = -999.9;//leading leps
  ptll_ = -999.9;

  hastau_ = false;

  leptype_ = -999;//0 = ee, 1 = mm, 2 = em

  lep1pt_ = -999.9;
  lep2pt_ = -999.9;
  lep3pt_ = -999.9;

  lep1dz_ = -999.9;
  lep2dz_ = -999.9;
  lep3dz_ = -999.9;

  lep1iso_ = -999.9;
  lep2iso_ = -999.9;
  lep3iso_ = -999.9;

  lep1d0_ = -999.9;
  lep2d0_ = -999.9;
  lep3d0_ = -999.9;

}

void miniBabyMaker::FillBabyNtuple()
{
  babyTree_->Fill();
}

void miniBabyMaker::SetGoodRun( std::string filename )
{
  std::cout<<"Using json: "<<filename<<std::endl;
  goodrunfilename_ = filename;
}

void miniBabyMaker::SetLuminosity( float luminosity )
{
  std::cout<<"Luminosity: "<<luminosity<<std::endl;
  luminosity_ = luminosity;
}
