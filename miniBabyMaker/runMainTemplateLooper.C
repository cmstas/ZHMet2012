// #include "TSystem.h"
// #include "TStyle.h"
// #include "TROOT.h"
// #include "TChain.h"

// #include <iostream>

// #include "include/ScanChain.h"

using namespace std;

int runMainTemplateLooper( string filesuffix = "" ){

  gSystem->AddIncludePath(" -Iinclude");
  gSystem->Load("libScanChain.so");

  gROOT ->SetStyle("Plain");
  gStyle->SetOptStat(111111);

  TChain *ch = new TChain("T1"); 

  // string sample = "closure_";
  string sample = "data_";

  string suffix = filesuffix;
  
  string ntuples = "/home/users/cwelke/ZHmet_2013/output/V00-02-19";
  vector <string> samples;
  cout<<"Chaining up ntuples"<<endl;
  
  if(sample == "data_"){
	

	// samples.push_back("data_53X_2012A_baby_nojson.root");
	// samples.push_back("data_53X_2012B_baby_nojson.root");
	ch->Add("/home/users/cwelke/ZHmet_2013/output/V00-02-21/data_53X_2012C_ecalreco_baby_nojson.root");
	// samples.push_back("data_53X_2012C_baby_nojson.root");
	// samples.push_back("data_53X_2012D_baby_nojson.root");


  }else if(sample == "closure_"){


	samples.push_back("zjets_53X_slim_baby.root");
	samples.push_back("z1jet_53X_slim__baby.root");
	samples.push_back("z2jet_53X_slim__baby.root");
	samples.push_back("z3jet_53X_slim__baby.root");
	samples.push_back("z4jet_53X_slim__baby.root");

	// samples.push_back("zbb2l_53X_slim_baby.root");

	// samples.push_back("zjetsmc_ee_baby.root");
	// samples.push_back("zjetsmc_mm_baby.root");

  }

  for( size_t ind = 0; ind < samples.size(); ind++ ){
	ch->Add( Form( "%s/%s", ntuples.c_str(), samples.at(ind).c_str() ) );
  }

  miniBabyMaker looper;// = new mainTemplateLooper();
  
  cout<<"running looper for: "<<suffix<<endl;
  looper.ScanChain(ch, -1, suffix); 

  delete ch;
 
  return 0;
}
