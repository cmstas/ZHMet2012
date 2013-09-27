//c stuff
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <set>

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
#include "TMath.h"

//stuff from tools
#include "/home/users/cwelke/CMSSW/CMSSW_5_3_2_patch4/src/CMS2/NtupleMacros/Tools/goodrun.h"

//stuff from CMS2
#include "/home/users/cwelke/CMSSW/CMSSW_5_3_2_patch4/src/CMS2/NtupleMacros/CORE/metTemplatesSelections.h"
#include "/home/users/cwelke/CMSSW/CMSSW_5_3_2_patch4/src/CMS2/NtupleMacros/CORE/MT2/MT2.h"

//stuff from my tools
#include "/home/users/cwelke/dev/cwelke/looperTools/eventFilter.h"
#include "/home/users/cwelke/dev/cwelke/looperTools/genbtagTools.h"

//stuff from tools/BTagReshaping
#include "/home/users/cwelke/CMSSW/CMSSW_5_3_2_patch4/src/CMS2/NtupleMacros/Tools/BTagReshaping/BTagReshaping.h"

//stuff from this looper
#include "setbinning.cc"
#include "zhist_looper.h"
#include "ZMET.h"

using namespace std;
using namespace ZMet;

// typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
//3.14159265358979323846

zhist_looper::zhist_looper()
{

  hZMjj = NULL;
  hZMjjof = NULL;
  hZMjjsf = NULL;

  // //histos for pT reweighting
  hZPt = NULL;
  hZPtof = NULL;
  hZPtsf = NULL;

  // //histos for hT reweighting
  hZHt = NULL;
  hZHtof = NULL;
  hZHtsf = NULL;

  // //histos for vertex reweighting
  hZ = NULL;

  rootfilename = "../tempfiles/vtxreweight_DoubleElectron_19fb_data_temp.root";

  reweightFile_ = NULL;
  hvtxreweight = NULL;
	
  outfile_ = NULL;

  checkJetDr = false;
  luminosity = 19.5;

}

zhist_looper::zhist_looper( Float_t mT2jlow = 0.0, Float_t mT2jhi = 5000.0, string input_selection = "" )
{

  z_metwithbs = new TH1F("z_metwithbs","metwithbs", 250, 0, 250 );
  z_metwithcs = new TH1F("z_metwithcs","metwithcs", 250, 0, 250 );

  //histos for mcfa stuff
  z_mcfabjet1 = new TH1F("z_mcfabjet1","mcfabjet1", 9, 0, 9 );
  z_mcfabjet2 = new TH1F("z_mcfabjet2","mcfabjet2", 9, 0, 9 );

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
  	z_mcfabjet1 -> GetXaxis() -> SetBinLabel( bini+2, binlabels.at(bini).c_str() );
  	z_mcfabjet2 -> GetXaxis() -> SetBinLabel( bini+2, binlabels.at(bini).c_str() );
  }

  z_metwithbs-> Sumw2();
  z_metwithcs-> Sumw2();

  z_mcfabjet1-> Sumw2();
  z_mcfabjet2-> Sumw2();

  hZMjj = NULL;
  hZMjjof = NULL;
  hZMjjsf = NULL;

  // //histos for pT reweighting
  hZPt = NULL;
  hZPtof = NULL;
  hZPtsf = NULL;

  // //histos for hT reweighting
  hZHt = NULL;
  hZHtof = NULL;
  hZHtsf = NULL;

  // //histos for vertex reweighting
  hZ = NULL;

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
  
  if( TString(selection).Contains("mt2jhi") ){ domt2jhi = true;
  }else                                      { domt2jhi = false; }
  if( TString(selection).Contains("mt2jlo") ){ domt2jlo = true;
  }else                                      { domt2jlo = false; }

  if( TString(selection).Contains("0genbs") ){ dogenbs = true;
	ngenbs = 0;
  }else if( TString(selection).Contains("1genbs") ){ dogenbs = true;
	ngenbs = 1;
  }else if( TString(selection).Contains("2genbs") ){ dogenbs = true;
	ngenbs = 2;
  }else                                     { dogenbs = false; }

  reweightFile_ = NULL;
  hvtxreweight = NULL;
	
  outfile_ = NULL;

  checkJetDr = false;
  luminosity = 19.5;

  mt2jlow = mT2jlow;
  mt2jhi = mT2jhi;

}


zhist_looper::~zhist_looper(){
  delete outfile_;
}

int zhist_looper::ScanChain ( TChain * chain, bool fast, int nEvents, string skimFilePrefix, string suffix ){


  cout<<Form("Running zhist_looper with following selection: %s", selection.c_str() )<<endl;

  if( skimFilePrefix == "data_" ){
	rootfilename = Form("../tempfiles/vtxreweight_DoubleElectron_19fb_data%s_temp.root", selection.c_str() );
  }else if( skimFilePrefix == "closure_" ){
	rootfilename = Form("../tempfiles/vtxreweight_DoubleElectron_19fb_MC%s_temp.root", selection.c_str() );
  }

  cout<<"Saving output file to: "<<rootfilename<<endl;

  // if( dobveto ){	cout<<"doing bveto"<<endl;
  // }else{	cout<<"not doing bveto"<<endl;  }
  // if( dotwobtag ){	cout<<"doing twobtag"<<endl;
  // }else{	cout<<"not doing twobtag"<<endl;  }
  // if( domjjhi ){	cout<<"doing mjjhi"<<endl;
  // }else{	cout<<"not doing mjjhi"<<endl;  }
  // if( domjjlo ){	cout<<"doing mjjlo"<<endl;
  // }else{	cout<<"not doing mjjlo"<<endl;  }
  // if( domt2jhi ){	cout<<"doing mt2jhi"<<endl;
  // }else{	cout<<"not doing mt2jhi"<<endl;  }
  // if( domt2jlo ){	cout<<"doing mt2jlo"<<endl;
  // }else{	cout<<"not doing mt2jlo"<<endl;  }

  //~-~-~-~-~-~-~-~-~-~-~-~-~-~//
  //Setting up histos for stuff//
  //~-~-~-~-~-~-~-~-~-~-~-~-~-~//
  //control bins for variable reweighting
  if( skimFilePrefix == "closure_" ){
  	if( dotwobtag && !domjjhi && !domjjlo && !domt2jhi && !domt2jlo ){
  	  cout<<"2btag"<<endl;
  	  // setpthists( 2.0, 112.0 );
  	  // seththists( 90.0, 360.0 );
  	  // setmjjhists( 40.0, 600.0 );
  	  setpthists( 2.0, 662.0 );
  	  seththists( 90.0, 1080.0 );
  	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
  	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
  	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
  	  // hZMjj = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
  	  // hZMjjof = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
  	  // hZMjjsf = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
  	  hZMjj -> Sumw2();
  	  hZMjjof -> Sumw2();
  	  hZMjjsf -> Sumw2();
  	  // setmjjhists( 40.0, 600.0 );
  	}else if( dobveto && !domjjhi && !domjjlo && !domt2jhi && !domt2jlo ){
  	  cout<<"bveto"<<endl;

  	  setpthists( 2.0, 862.0 );
  	  seththists( 90.0, 1440.0 );
	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
	  // hZMjj = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
	  // hZMjjof = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
	  // hZMjjsf = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
	  hZMjj -> Sumw2();
	  hZMjjof -> Sumw2();
	  hZMjjsf -> Sumw2();
	  // setmjjhists( 40.0, 600.0 );
  	}else if( dotwobtag && !domjjhi && !domjjlo && domt2jhi ){
  	  cout<<"2btag high mt2j"<<endl;
  	  setpthists( 2.0, 462.0 );
  	  seththists( 90.0, 840.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}else if( dotwobtag && !domjjhi && !domjjlo && domt2jlo ){
  	  cout<<"2btag low mt2j"<<endl;
  	  setpthists( 2.0, 462.0 );
  	  seththists( 90.0, 840.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}else if( !dotwobtag && !domjjhi && !domjjlo && !domt2jhi && !domt2jlo ){
  	  cout<<"no two btag"<<endl;
  	  setpthists( 2.0, 462.0 );
  	  seththists( 90.0, 840.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}

  	if( dotwobtag && domjjhi && domt2jhi ){ 
  	  cout<<__LINE__<<endl;
  	  setpthists( 2.0, 462.0 );
  	  seththists( 90.0, 840.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}else if( dotwobtag && domjjhi && domt2jlo ){
  	  cout<<__LINE__<<endl;
  	  setpthists( 2.0, 202.0 );
  	  seththists( 90.0, 840.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}else if( dotwobtag && domjjlo && domt2jlo ){
  	  cout<<__LINE__<<endl;
  	  setpthists( 2.0, 262.0 );
  	  seththists( 90.0, 840.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}else if( dotwobtag && domjjlo && domt2jhi ){
  	  cout<<__LINE__<<endl;
  	  setpthists( 2.0, 462.0 );
  	  seththists( 90.0, 840.0 );
  	  setmjjhists( 40.0, 600.0 );

  	}else if( dobveto && domjjhi && domt2jhi ){ 
  	  cout<<__LINE__<<endl;
  	  setpthists( 2.0, 462.0 );
  	  seththists( 90.0, 840.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}else if( dobveto && domjjlo && domt2jhi ){ 
  	  cout<<__LINE__<<endl;
  	  setpthists( 2.0, 462.0 );
  	  seththists( 90.0, 480.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}else if( dobveto && domjjhi && domt2jlo ){ 
  	  cout<<__LINE__<<endl;
  	  setpthists( 2.0, 212.0 );
  	  seththists( 90.0, 840.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}else if( dobveto && domjjlo && domt2jlo ){ 
  	  cout<<__LINE__<<endl;
  	  setpthists( 2.0, 262.0 );
  	  seththists( 90.0, 480.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}
  }else{ 

  	if( dotwobtag && !domjjhi && !domjjlo && !domt2jhi && !domt2jlo ){
  	  cout<<"2btag"<<endl;
  	  // setpthists( 2.0, 112.0 );
  	  // seththists( 90.0, 360.0 );
  	  // setmjjhists( 40.0, 600.0 );
  	  setpthists( 2.0, 262.0 );
  	  seththists( 90.0, 960.0 );
  	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
  	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
  	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
  	  // hZMjj = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
  	  // hZMjjof = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
  	  // hZMjjsf = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
  	  hZMjj -> Sumw2();
  	  hZMjjof -> Sumw2();
  	  hZMjjsf -> Sumw2();
  	  // setmjjhists( 40.0, 600.0 );
  	}else if( dobveto && !domjjhi && !domjjlo && !domt2jhi && !domt2jlo ){
  	  cout<<"bveto"<<endl;
  	  setpthists( 2.0, 262.0 );
  	  seththists( 90.0, 960.0 );
	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 500, 0, 500 );
	  // hZMjj = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
	  // hZMjjof = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
	  // hZMjjsf = new TH1F( "hZMjj", "hZMjj", 50, 0, 1. );
	  hZMjj -> Sumw2();
	  hZMjjof -> Sumw2();
	  hZMjjsf -> Sumw2();
	  // setmjjhists( 40.0, 600.0 );
  	}else if( dotwobtag && !domjjhi && !domjjlo && domt2jhi ){
  	  cout<<"2btag high mt2j"<<endl;
  	  setpthists( 2.0, 262.0 );
  	  seththists( 90.0, 960.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}else if( dotwobtag && !domjjhi && !domjjlo && domt2jlo ){
  	  cout<<"2btag low mt2j"<<endl;
  	  setpthists( 2.0, 262.0 );
  	  seththists( 90.0, 960.0 );
  	  setmjjhists( 40.0, 600.0 );

  	}else if( dobveto && !domjjhi && !domjjlo && domt2jhi ){
  	  cout<<"bveto high mt2j"<<endl;
  	  setpthists( 2.0, 262.0 );
  	  seththists( 90.0, 960.0 );
  	  setmjjhists( 40.0, 600.0 );
  	}else if( dobveto && !domjjhi && !domjjlo && domt2jlo ){
  	  cout<<"bveto low mt2j"<<endl;
  	  setpthists( 2.0, 262.0 );
  	  seththists( 90.0, 960.0 );
  	  setmjjhists( 40.0, 600.0 );

	}else if( dotwobtag && domjjhi && domt2jhi ){ 
	  setpthists( 2.0, 262.0 );
	  seththists( 90.0, 960.0 );
	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  // setmjjhists( 40.0, 600.0 );
	}else if( dotwobtag && domjjhi && domt2jlo ){
	  setpthists( 2.0, 112.0 );
	  seththists( 90.0, 480.0 );
	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  // setmjjhists( 40.0, 600.0 );
	}else if( dotwobtag && domjjlo && domt2jlo ){
	  setpthists( 2.0, 112.0 );
	  seththists( 90.0, 480.0 );
	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  // setmjjhists( 40.0, 600.0 );
	}else if( dotwobtag && domjjlo && domt2jhi ){
	  setpthists( 2.0, 162.0 );
	  seththists( 90.0, 480.0 );
	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 25, 0, 1 );
	  // setmjjhists( 40.0, 600.0 );

  	}else if( dobveto && domjjhi && domt2jhi ){ 
  	  setpthists( 2.0, 262.0 );
  	  seththists( 90.0, 960.0 );
	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
  	  // setmjjhists( 40.0, 600.0 );
  	}else if( dobveto && domjjlo && domt2jhi ){ 
  	  setpthists( 2.0, 262.0 );
  	  seththists( 90.0, 360.0 );
	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
  	  // setmjjhists( 40.0, 600.0 );
  	}else if( dobveto && domjjhi && domt2jlo ){ 
  	  setpthists( 2.0, 212.0 );
  	  seththists( 90.0, 960.0 );
	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
  	  // setmjjhists( 40.0, 600.0 );
  	}else if( dobveto && domjjlo && domt2jlo ){ 
  	  setpthists( 2.0, 162.0 );
  	  seththists( 90.0, 360.0 );
	  hZMjj =   new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
	  hZMjjof = new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
	  hZMjjsf = new TH1F( "hZMjj", "hZMjj", 25, 0, 0.06 );
  	  // setmjjhists( 40.0, 600.0 );
  	}
  }

  // //histos for vertex reweighting
  hZ = new TH1F("hZ","",35,0,35);
  hZ -> Sumw2();
  hZ -> Rebin(5);
  hZMjj -> Sumw2();
  hZMjjof -> Sumw2();
  hZMjjsf -> Sumw2();

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

  //Set btag reshaping
  BTagShapeInterface * nominalShape = 0;
  nominalShape = new BTagShapeInterface("/home/users/cwelke/CMSSW/CMSSW_5_3_2_patch4/src/CMS2/NtupleMacros/Tools/BTagReshaping/csvdiscr.root", 0.0, 0.0); 

  //set json file
  // set_goodrun_file("/home/users/benhoob/ZMet2012/jsons/final_19p47fb_cms2.txt");

  //json for moriond
  set_goodrun_file("/home/users/benhoob/ZMet2012/jsons/Merged_190456-208686_8TeV_PromptReReco_Collisions12_goodruns.txt");

  //json for hcp
  // set_goodrun_file("/home/users/benhoob/ZMet2012/jsons/Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON_goodruns.txt");

  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile *file = new TFile( currentFile->GetTitle() ); 
    TTree *tree = (TTree*)file->Get("T1");

	cout<<"Loading file: "<<currentFile->GetTitle()<<endl;
	setSample( currentFile->GetTitle() );

    zmet.Init(tree);
    unsigned int nEventsTree = tree->GetEntries(); 
    for( unsigned long event = 0; event < nEventsTree; ++event) {
    
      // Get Event Content
      if( nEventsTotal >= nEventsChain ) continue;
      if(fast) tree->LoadTree(event);
      zmet.GetEntry(event);
	  // cout<<"event: "<<event<<endl;
      ++nEventsTotal;

	  // pogress
	  long i_permille = (long)floor(1000 * nEventsTotal / double(nEventsChain));
	  if (i_permille != i_permilleOld) {
		printf("  \015\033[32m ---> \033[1m\033[31m%4.1f%%" "\033[0m\033[32m <---\033[0m\015", i_permille/10.);
		fflush(stdout);
		i_permilleOld = i_permille;
	  }

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
	  
	  //filter inclusive dy sample
	  if( !zmet.isdata() ){
		if( basename == "zjets" || basename == "zjetsinc" ){
		  // if( !TString(currentFile->GetTitle()).Contains("zbb2l") ){
		  // if( zmet.ngenbs() == 2 ){
		  //   continue;
		  //   // if( TString(currentFile->GetTitle()).Contains("zjets_") ) basename = "zjetsinc";
		  // }

		  if( TString(currentFile->GetTitle()).Contains("zjets_") ) {
			if( zmet.nwzpartons() > 0 ){
			  continue;
			}
		  }	  

		  // if( basename == "zjetsinc" ){
		  // 	if( zmet.ngenbs() == 2 ){
		  // 	  continue;
		  // 	}else{
		  // }else{
		  // basename = "zjetsinc2";
		  // }
		}
		basename = "zjets";
	  }
	  // 	  if( TString(currentFile->GetTitle()).Contains("zjets_") ) basename = "zjetsinc";
	  // 	}
	  
	  // 	if( basename == "zjetsinc" ){
	  // 	  if( zmet.nwzpartons() > 0 ){
	  // 		continue;
	  // 	  }
	  // 	}
	  // }
	  // }
   	  
	  //~-~-~-~-~-~-~-~-~-//
	  //Analysis Code Here//
	  //~-~-~-~-~-~-~-~-~-//
	  double weight = 1;
	  // weight *= hvtxreweight->GetBinContent(zmet.nvtx()+1);
	  //rescale MC
	  if(       !zmet.isdata() && (basename == "zpythia") ){
		// weight = 1;
		// weight *= hvtxreweight->GetBinContent(zmet.nvtx()+1);
	  	weight = weight
		  // *zmet.vtxweight()
		  // *zmet.trgeff()
		  *zmet.weight()
		  *luminosity;
	  }else if( !zmet.isdata() && !(basename == "zpythia") ){
	  	weight = 1;
	  	// weight *= zmet.vtxweight();
		// weight *= zmet.trgeff();	   
	  	weight *= zmet.weight();
	  	weight *= luminosity;
	  }else if (zmet.isdata()  ){
	  	weight = 1;
	  }
	  
	  weight = 1;
	  // weight *= zmet.vtxweight();
	  // weight *= zmet.trgeff();	   
	  weight *= zmet.weight();
	  weight *= luminosity;

	  //Selection starts here

	  // if(zmet.isdata() ){
	  // 	if(!(zmet.csc()==0 && 
	  // 		 zmet.hbhe()==1 && 
	  // 		 zmet.hcallaser()==1 && 
	  // 		 zmet.ecallaser()==1 && 
	  // 		 zmet.ecaltp()==1 && 
	  // 		 zmet.trkfail()==1 && 
	  // 		 zmet.eebadsc()==1 && 
	  // 		 zmet.hbhenew()==1))                                continue;//met filter variables and trigger variables
	  // }

	  if( zmet.lep1().pt() < 20.0 )                             continue;
	  if( zmet.lep2().pt() < 20.0 )                             continue;//pT > (20,20)

	  if( zmet.pfTau_leadPtcandID() != (-1) ) continue;//tau veto

	  // if(zmet.isdata()){
	  // 	if( zmet.leptype()==0 ){
	  // 	  if( zmet.ee()==0 )	                                continue;
	  // 	}
	  // 	else if( zmet.leptype()==1 ){
	  // 	  if( zmet.mm()==0 )		                            continue;
	  // 	}
	  // 	else if( zmet.leptype()==2 ){
	  // 	  if( zmet.em()==0 && zmet.me()==0 )			        continue;
	  // 	}
	  // }
	  
	  //b-tag reshaping
	  float csv1_nominal = zmet.csv1();
	  float csv2_nominal = zmet.csv2();
	  float csv3_nominal = zmet.csv3();
	  if( !zmet.isdata() ){
	  	csv1_nominal=nominalShape->reshape(zmet.jet1().Eta(), 
	  									   zmet.jet1().Pt(),
	  									   zmet.csv1(),
	  									   zmet.jet1mcfa());
	  	csv2_nominal=nominalShape->reshape(zmet.jet2().Eta(), 
	  									   zmet.jet2().Pt(),
	  									   zmet.csv2(),
	  									   zmet.jet2mcfa());
	  	csv3_nominal=nominalShape->reshape(zmet.jet3().Eta(), 
	  									   zmet.jet3().Pt(),
	  									   zmet.csv3(),
	  									   zmet.jet3mcfa());
	  }
	  
	  vector <Float_t> csvvals;
	  csvvals.push_back(csv1_nominal);
	  csvvals.push_back(csv2_nominal);
	  csvvals.push_back(csv3_nominal);

	  Float_t csvproduct = 0.0;
	  
	  // if( zmet.isdata() && zmet.pfTau_leadPtcandID() != (-1) ) continue;//tau veto	 
	  if( zmet.njets() < 2 ){                                   continue;}//jet selection 
	  if( zmet.njets() > 3 ){                                   continue;}//jet selection 
	  // if( zmet.nlep()  > 2 ){                                   continue;}// 3rd lep veto
	  	  
	  vector <LorentzVector> leps;
	  leps.push_back(zmet.lep1());
	  leps.push_back(zmet.lep2());
	  Float_t mll= zmet.dilep().mass();
	  bool medzwindow = !( mll < 81.0 || mll > 101.0);
	  if( !medzwindow ) continue;		

	  Float_t mjj = 0.0;
	  Float_t mT2j = 0.0;

	  if( !dobveto && !dotwobtag ){
		vector <LorentzVector> jets;
		jets.push_back(zmet.jet1());
		jets.push_back(zmet.jet2());
		if( zmet.njets() == 3 ){ jets.push_back(zmet.jet3()); }
		mjj = (jets.at(0) + jets.at(1)).mass();
		mT2j = getMT2b( leps, jets );
		csvproduct = zmet.csv1()*zmet.csv2();
		  
	  }else if( dobveto && !dotwobtag ){
		bool bveto = ( zmet.nbcsvl() < 1 );
		if( dobveto && bveto ){
		  vector <LorentzVector> jets;
		  jets.push_back(zmet.jet1());
		  jets.push_back(zmet.jet2());
		  if( zmet.njets() == 3 ){ jets.push_back(zmet.jet3()); }
		  mjj = (jets.at(0) + jets.at(1)).mass();
		  mT2j = getMT2b( leps, jets );
		  csvproduct = zmet.csv1()*zmet.csv2();
		}else{ continue; }

	  }else if( !dobveto && dotwobtag ){
		Bool_t twogoodbs = getbjets( 0.244, csvvals );	  		
		if( dotwobtag && twogoodbs ){
		  mjj = (goodbs.at(0) + goodbs.at(1)).mass();
		  mT2j = getMT2b( leps, goodbs );
		  csvproduct = get2btagproduct( 0.244, csvvals );
		}else{ continue; }		

	  }else{
		cout<<"incosistent b-tagging selection. exiting."<<endl;
		exit(1);
	  }
	  
	  if( domjjhi  &&  mjj < 150.0 )                 continue;
	  if( domjjlo  && (mjj > 150.0 || mjj < 100.0) ) continue;
	  if( domt2jhi && mT2j < 200.0 )                 continue;
	  if( domt2jlo && mT2j > 200.0 )                 continue;

	  if( dogenbs && !zmet.isdata() ){
		vector <Float_t> mcfavals;
		mcfavals.push_back(zmet.jet1mcfa());
		mcfavals.push_back(zmet.jet2mcfa());
		mcfavals.push_back(zmet.jet3mcfa());

		if( ngenbs == 0 && !hasnogenbjets(  mcfavals ) ) continue;
		if( ngenbs == 1 && !hasonegenbjets( mcfavals ) ) continue;
   		if( ngenbs == 2 && !hastwogenbjets( 0.244, csvvals, mcfavals ) ) continue;
	  }
	
	  vector <Float_t> mcfavals;
	  Float_t mcfaproduct = 0.0;

	  if( !zmet.isdata() ){
		mcfavals.push_back(zmet.jet1mcfa());
		mcfavals.push_back(zmet.jet2mcfa());
		mcfavals.push_back(zmet.jet3mcfa());
		mcfaproduct = get2btagmcfaproduct( 0.244, csvvals, mcfavals );
		if( dobveto ) mcfaproduct = zmet.jet1mcfa()*zmet.jet2mcfa();
	  }

	  if( zmet.leptype() == 2 ){
		// fillHist( hZMjjof, csvproduct, weight);
		// fillHist( hZMjjof, mcfaproduct, weight);
		fillHist( hZPtof, zmet.dilep().pt(), weight);
		fillHist( hZHtof, zmet.sumjetpt(), weight);

	  }else if( ( zmet.leptype() == 0 || zmet.leptype() == 1 ) ){

		if( !zmet.isdata() ){

		  // if( zmet.pfmet() > 100.0 ){
		  // fillmcfahists( 0.244, z_mcfabjet1, z_mcfabjet2, weight );
		  // }

		  if( abs(zmet.jet1mcfa()) != 21 && abs(zmet.jet1mcfa()) != 22 ) fillHist(z_mcfabjet1, abs(zmet.jet1mcfa()), weight);
		  else if( abs(zmet.jet1mcfa()) == 21 )                               fillHist(z_mcfabjet1, 7, weight);
		  else if( abs(zmet.jet1mcfa()) == 22 )                               fillHist(z_mcfabjet1, 8, weight);
		  if( abs(zmet.jet2mcfa()) != 21 && abs(zmet.jet2mcfa()) != 22 ) fillHist(z_mcfabjet2, abs(zmet.jet2mcfa()), weight);
		  else if( abs(zmet.jet2mcfa()) == 21 )                               fillHist(z_mcfabjet2, 7, weight);
		  else if( abs(zmet.jet2mcfa()) == 22 )                               fillHist(z_mcfabjet2, 8, weight);

		  // }

		  if( abs(zmet.jet2mcfa()) == 5 ) fillHist(z_metwithbs, zmet.pfmet(), weight);
		  if( abs(zmet.jet2mcfa()) == 4 ) fillHist(z_metwithcs, zmet.pfmet(), weight);
		  // }
		}

		fillHist( hZMjjsf, csvproduct, weight);
		// fillHist( hZMjjsf, mcfaproduct, weight);
		fillHist( hZPtsf, zmet.dilep().pt(), weight);
		fillHist( hZHtsf, zmet.sumjetpt(), weight);
		// if(      zmet.njets() == 2 )		fillHist( hZHtsf, zmet.jet1().pt() + zmet.jet2().pt(), weight);
		// else if( zmet.njets() == 3 )		fillHist( hZHtsf, zmet.jet1().pt() + zmet.jet2().pt() + zmet.jet3().pt(), weight);
	  }
	  fillHist( hZ, zmet.nvtx(), weight );
	  
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

  //this command saves the histos to the file and closes it.
  subtract_ofevents();
  saveHists();

  cout<<"Writing baby to: "<<rootfilename<<endl;
  return 0;
  
}

void zhist_looper::setpthists( double minPT,  double maxPT )
{
  ptbins = setptbins( minPT, maxPT );
  double newbinning[ptbins.size()];
  for( size_t bini = 0; bini < ptbins.size(); bini++ ){
  	newbinning[bini] = ptbins.at(bini);
  }
  Int_t nbins = ptbins.size()-1;
  
  // // only necessary for debugging 
  // for( Int_t bini = 0; bini < binning.size(); bini++ ){
  // 	cout<<"binedgelow: "<<newbinning[bini]<<endl;;
  // }
  
  // //histos for pT reweighting
  hZPt   = new TH1F("hZPt",   "hZPt",nbins,newbinning);
  hZPtof = new TH1F("hZPtof", "hZPt",nbins,newbinning);
  hZPtsf = new TH1F("hZPtsf", "hZPt",nbins,newbinning);
  hZPt   -> Sumw2();
  hZPtof -> Sumw2();
  hZPtsf -> Sumw2();
  return;
}

void zhist_looper::seththists( double minHT,  double maxHT )
{
  htbins = sethtbins( minHT, maxHT );
  double newhtbinning[htbins.size()];
  for( size_t bini = 0; bini < htbins.size(); bini++ ){
  	newhtbinning[bini] = htbins.at(bini);
  }
  Int_t nhtbins = htbins.size()-1;
  
  // only necessary for debugging  
  for( Int_t bini = 0; bini < htbins.size(); bini++ ){
  	cout<<"ht binedgelow: "<<newhtbinning[bini]<<endl;;
  }

  // //histos for hT reweighting
  hZHt   = new TH1F("hZHt",   "hZHt",nhtbins,newhtbinning);
  hZHtof = new TH1F("hZHtof", "hZHt",nhtbins,newhtbinning);
  hZHtsf = new TH1F("hZHtsf", "hZHt",nhtbins,newhtbinning);
  hZHt   -> Sumw2();
  hZHtof -> Sumw2();
  hZHtsf -> Sumw2();
  return;
}

void zhist_looper::setmjjhists( double minMJJ, double maxMJJ )
{
  mjjbins = setmjjbins( minMJJ, maxMJJ );
  double newmjjbinning[mjjbins.size()];
  for( size_t bini = 0; bini < mjjbins.size(); bini++ ){
  	newmjjbinning[bini] = mjjbins.at(bini);
  }
  Int_t nmjjbins = mjjbins.size()-1;

  // // only necessary for debugging  
  // for( Int_t bini = 0; bini < mjjbins.size(); bini++ ){
  // 	cout<<"mjj binedgelow: "<<newmjjbinning[bini]<<endl;;
  // }

  //histos for mjj reweighting
  hZMjj   = new TH1F("hZMjj",   "hZMjj",nmjjbins,newmjjbinning);
  hZMjjof = new TH1F("hZMjjof", "hZMjj",nmjjbins,newmjjbinning);
  hZMjjsf = new TH1F("hZMjjsf", "hZMjj",nmjjbins,newmjjbinning);
  hZMjj -> Sumw2();
  hZMjjof -> Sumw2();
  hZMjjsf -> Sumw2();
  return;
}
  
bool zhist_looper::getbjets( const Float_t workingpoint )
{
  bool twogoodjets = false;
  goodbs.clear();
  if(       zmet.csv1() >= workingpoint && zmet.csv2() >= workingpoint && zmet.csv3() < workingpoint ){
	goodbs.push_back(zmet.jet1());
	goodbs.push_back(zmet.jet2());
	twogoodjets = true;
  }else if( zmet.csv1() >= workingpoint && zmet.csv3() >= workingpoint && zmet.csv2() < workingpoint ){
	goodbs.push_back(zmet.jet1());
	goodbs.push_back(zmet.jet3());
	twogoodjets = true;
  }else if( zmet.csv2() >= workingpoint && zmet.csv3() >= workingpoint && zmet.csv1() < workingpoint ){
	goodbs.push_back(zmet.jet2());
	goodbs.push_back(zmet.jet3());
	twogoodjets = true;
  }
  return twogoodjets;
}

bool zhist_looper::getbjets( const Float_t workingpoint, const vector <Float_t> &csvvals )
{
  bool twogoodjets = false;
  goodbs.clear();
  if(       csvvals.at(0) >= workingpoint && csvvals.at(1) >= workingpoint && csvvals.at(2) < workingpoint ){
	goodbs.push_back(zmet.jet1());
	goodbs.push_back(zmet.jet2());
	twogoodjets = true;
  }else if( csvvals.at(0) >= workingpoint && csvvals.at(2) >= workingpoint && csvvals.at(1) < workingpoint ){
	goodbs.push_back(zmet.jet1());
	goodbs.push_back(zmet.jet3());
	twogoodjets = true;
  }else if( csvvals.at(1) >= workingpoint && csvvals.at(2) >= workingpoint && csvvals.at(0) < workingpoint ){
	goodbs.push_back(zmet.jet2());
	goodbs.push_back(zmet.jet3());
	twogoodjets = true;
  }
  return twogoodjets;
}

void zhist_looper::fillmcfahists( const Float_t workingpoint, TH1F * &z_mcfabjet1, TH1F * &z_mcfabjet2, const double weight ){
  if(       zmet.csv1() >= workingpoint && zmet.csv2() >= workingpoint && zmet.csv3() < workingpoint ){
	// fillHist(z_mcfabjet1, abs(zmet.jet1mcfa()), weight);
	// fillHist(z_mcfabjet2, abs(zmet.jet2mcfa()), weight);
	if( abs(zmet.jet1mcfa()) != 21 && abs(zmet.jet1mcfa()) != 22 ) fillHist(z_mcfabjet1, abs(zmet.jet1mcfa()), weight);
	else if( abs(zmet.jet1mcfa()) == 21 )                               fillHist(z_mcfabjet1, 7, weight);
	else if( abs(zmet.jet1mcfa()) == 22 )                               fillHist(z_mcfabjet1, 8, weight);
	if( abs(zmet.jet2mcfa()) != 21 && abs(zmet.jet2mcfa()) != 22 ) fillHist(z_mcfabjet2, abs(zmet.jet2mcfa()), weight);
	else if( abs(zmet.jet2mcfa()) == 21 )                               fillHist(z_mcfabjet2, 7, weight);
	else if( abs(zmet.jet2mcfa()) == 22 )                               fillHist(z_mcfabjet2, 8, weight);

  }else if( zmet.csv1() >= workingpoint && zmet.csv3() >= workingpoint && zmet.csv2() < workingpoint ){
	// fillHist(z_mcfabjet1, abs(zmet.jet1mcfa()), weight);
	// fillHist(z_mcfabjet2, abs(zmet.jet3mcfa()), weight);
	if( abs(zmet.jet1mcfa()) != 21 && abs(zmet.jet1mcfa()) != 22 ) fillHist(z_mcfabjet1, abs(zmet.jet1mcfa()), weight);
	else if( abs(zmet.jet1mcfa()) == 21 )                               fillHist(z_mcfabjet1, 7, weight);
	else if( abs(zmet.jet1mcfa()) == 22 )                               fillHist(z_mcfabjet1, 8, weight);
	if( abs(zmet.jet3mcfa()) != 21 && abs(zmet.jet3mcfa()) != 22 ) fillHist(z_mcfabjet2, abs(zmet.jet3mcfa()), weight);
	else if( abs(zmet.jet3mcfa()) == 21 )                               fillHist(z_mcfabjet2, 7, weight);
	else if( abs(zmet.jet3mcfa()) == 22 )                               fillHist(z_mcfabjet2, 8, weight);

  }else if( zmet.csv2() >= workingpoint && zmet.csv3() >= workingpoint && zmet.csv1() < workingpoint ){
	// fillHist(z_mcfabjet1, abs(zmet.jet2mcfa()), weight);
	// fillHist(z_mcfabjet2, abs(zmet.jet3mcfa()), weight);
	if( abs(zmet.jet2mcfa()) != 21 && abs(zmet.jet2mcfa()) != 22 ) fillHist(z_mcfabjet1, abs(zmet.jet2mcfa()), weight);
	else if( abs(zmet.jet2mcfa()) == 21 )                               fillHist(z_mcfabjet1, 7, weight);
	else if( abs(zmet.jet2mcfa()) == 22 )                               fillHist(z_mcfabjet1, 8, weight);
	if( abs(zmet.jet3mcfa()) != 21 && abs(zmet.jet3mcfa()) != 22 ) fillHist(z_mcfabjet2, abs(zmet.jet3mcfa()), weight);
	else if( abs(zmet.jet3mcfa()) == 21 )                               fillHist(z_mcfabjet2, 7, weight);
	else if( abs(zmet.jet3mcfa()) == 22 )                               fillHist(z_mcfabjet2, 8, weight);

  }
  return;
}

void zhist_looper::setSample( string samplename )
{
  if(       TString(samplename).Contains("zjetsmc_") ){ basename = "zpythia";
  }else if( TString(samplename).Contains("zjets_") ){ basename = "zjetsinc";
  }else if( TString(samplename).Contains("zbb2l_") ){ basename = "zjets";
  }else if( TString(samplename).Contains("z1jet_") ){ basename = "zjets";
  }else if( TString(samplename).Contains("z2jet_") ){ basename = "zjets";
  }else if( TString(samplename).Contains("z3jet_") ){ basename = "zjets";
  }else if( TString(samplename).Contains("z4jet_") ){ basename = "zjets";
  }else if( TString(samplename).Contains("data_") ){ basename = "data";
  }else if( TString(samplename).Contains("wz") ){ basename = "wz";
  }else if( TString(samplename).Contains("ww") ){ basename = "ww";
  }else if( TString(samplename).Contains("zz") ){ basename = "zz";
  }else if( TString(samplename).Contains("ttbar_") ){ basename = "ttbar";
  }else if( TString(samplename).Contains("t_53X_slim_baby") ){ basename = "st";
  }else if( TString(samplename).Contains("tbz_53X_slim_baby") ){ basename = "tbz";
  }else if( TString(samplename).Contains("ttg_53X_slim_baby") ){ basename = "ttv";
  }else if( TString(samplename).Contains("ttw_53X_slim_baby") ){ basename = "ttv";
  }else if( TString(samplename).Contains("ttz_53X_slim_baby") ){ basename = "ttv";
  }else if( TString(samplename).Contains("vvv_53X_slim_baby") ){ basename = "vvv";
  }else if( TString(samplename).Contains("zhsm_53X_slim_baby") ){ basename = "smzh";

  }else{ 
  	cout<<"filename for file:"<<samplename<<"not set."<<endl;
  	basename = "";
  }
  // cout<<"filename:"<<samplename<<endl;
  cout<<"basename:"<<basename<<endl;
  return;
}

Float_t zhist_looper::getMT2b( const vector <LorentzVector> &leps, const vector <LorentzVector> &bjets )
{
  Float_t mT2b1 = 0;
  Float_t mT2b2 = 0;
  if( bjets.size() == 2 ){
	mT2b1 = MT2( zmet.pfmet(), zmet.pfmetphi(), leps.at(0) + bjets.at(0), leps.at(1) + bjets.at(1) );
	mT2b2 = MT2( zmet.pfmet(), zmet.pfmetphi(), leps.at(0) + bjets.at(1), leps.at(1) + bjets.at(0) );
	return min( mT2b1, mT2b2 );
  }else if ( bjets.size() == 3 ){
	vector <float> mT2b;
	mT2b.push_back( MT2( zmet.pfmet(), zmet.pfmetphi(), leps.at(0) + bjets.at(0), leps.at(1) + bjets.at(1) ) );
	mT2b.push_back( MT2( zmet.pfmet(), zmet.pfmetphi(), leps.at(0) + bjets.at(1), leps.at(1) + bjets.at(0) ) );
	mT2b.push_back( MT2( zmet.pfmet(), zmet.pfmetphi(), leps.at(0) + bjets.at(0), leps.at(1) + bjets.at(2) ) );
	mT2b.push_back( MT2( zmet.pfmet(), zmet.pfmetphi(), leps.at(0) + bjets.at(2), leps.at(1) + bjets.at(0) ) );
	mT2b.push_back( MT2( zmet.pfmet(), zmet.pfmetphi(), leps.at(0) + bjets.at(1), leps.at(1) + bjets.at(2) ) );
	mT2b.push_back( MT2( zmet.pfmet(), zmet.pfmetphi(), leps.at(0) + bjets.at(2), leps.at(1) + bjets.at(1) ) );
    sort( mT2b.begin(), mT2b.end() );
	return mT2b.at(0);
  }else{
	return 0.0;
  }
}

vector <Float_t> zhist_looper::getMlb( const vector <LorentzVector> &leps, const vector <LorentzVector> &bjets )
{
  vector <Float_t> mlb;
  mlb.push_back(( leps.at(0) + bjets.at(0) ).mass());
  mlb.push_back(( leps.at(1) + bjets.at(0) ).mass());
  mlb.push_back(( leps.at(0) + bjets.at(1) ).mass());
  mlb.push_back(( leps.at(1) + bjets.at(1) ).mass());
  sort(mlb.begin(), mlb.end());
  return mlb;
}

void zhist_looper::bookHist(map<string,TH1F*> &hist_map, const string &histname, const string &histtitle, unsigned int nbins, float min, float max)
{

  cout<<"Booking Hist: "<<histname<<endl;
  hist_map.insert ( pair<string,TH1F*>(histname, new TH1F(histname.c_str(), histtitle.c_str(), nbins, min, max)));
  hist_map[histname]->Sumw2();
  return;

}


void zhist_looper::bookHists(){
  
  return;
}

void zhist_looper::fillHist( const string &histoname, double variable, const double weight ){

  float min = evthists_[histoname]->GetXaxis()->GetXmin();
  float max = evthists_[histoname]->GetXaxis()->GetXmax();

  if (variable > max) variable = evthists_[histoname]->GetBinCenter(evthists_[histoname]->GetNbinsX());
  if (variable < min) variable = evthists_[histoname]->GetBinCenter(1);

  evthists_[histoname]->Fill(variable, weight);

  return;
}

void zhist_looper::fillHist(  TH1F* &hist, double variable, const double weight ){

  float min = hist->GetXaxis()->GetXmin();
  float max = hist->GetXaxis()->GetXmax();

  if (variable > max) variable = hist->GetBinCenter(hist->GetNbinsX());
  if (variable < min) variable = hist->GetBinCenter(1);

  hist->Fill(variable, weight);

  return;
}

void zhist_looper::subtract_ofevents()
{
  hZMjj -> Add( hZMjjsf );
  hZMjj -> Add( hZMjjof, -0.97 );
  hZPt -> Add( hZPtsf );
  hZPt -> Add( hZPtof, -0.97 );
  hZHt -> Add( hZHtsf );
  hZHt -> Add( hZHtof, -0.97 );
  return;
}

void zhist_looper::saveHists(map < string, TH1F* > &hist_map ){

  outfile_->cd();
  for (map<string, TH1F*>::iterator itr = hist_map.begin(); itr != hist_map.end(); itr++){
	itr->second->Write(itr->first.c_str(), TObject::kOverwrite);
  }

  return;
}

void zhist_looper::saveHists(){

  TFile *fratio = TFile::Open(rootfilename.c_str(),"RECREATE");
  fratio  -> cd();
  hZ      -> Write();
  hZPt    -> Write();
  hZMjj   -> Write();
  hZHt    -> Write();
  hZPtof  -> Write();
  hZMjjof -> Write();
  hZHtof  -> Write();
  hZPtsf  -> Write();
  hZMjjsf -> Write();
  hZHtsf  -> Write();

  if( TString(rootfilename).Contains("MC") ){
	z_mcfabjet1 -> Write();
	z_mcfabjet2 -> Write();
	z_metwithbs -> Write();
	z_metwithcs -> Write();
  }

  fratio  -> Close();
  return;
}

Float_t zhist_looper::getBinomialError( const Float_t num, const Float_t deno ){
  
  Float_t   p       =   num / deno;
  Float_t   error   =   sqrt(p*(1-p)/deno);
  return error;
  
}

