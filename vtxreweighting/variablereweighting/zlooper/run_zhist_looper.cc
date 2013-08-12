#include <vector>

// #include "zhist_looper.h"
// #include "TChain.h"

int run_zhist_looper( Float_t lowcut = 0.0, std::string selection = "", bool ismc = false  ){

  Float_t highcut = 5000.0;

  // gSystem->Load("../CORE/libCMS2NtupleMacrosCORE.so");
  gSystem->Load("libzhist_looper.so");

  gROOT ->SetStyle("Plain");
  gStyle->SetOptStat(111111);

  TChain *ch = new TChain("T1"); 

  string sample = "";
  if( ismc ){
	sample = "closure_";
  }else if( !ismc ){
	sample = "data_";
  }

  string suffix = "";
  
  vector <string> samples;
  string ntuples = "/home/users/cwelke/ZHmet_2013/output/V00-02-19";

	cout<<"Chaining up ntuples"<<endl;	
  
  if(sample == "data_"){
	
	samples.push_back("data_53X_2012A_baby_nojson.root");
	samples.push_back("data_53X_2012B_baby_nojson.root");
	samples.push_back("data_53X_2012C_baby_nojson.root");
	samples.push_back("data_53X_2012D_baby_nojson.root");

	// samples.push_back("t_53X_slim_baby.root");

	// samples.push_back("tbz_53X_slim_baby.root");

	// samples.push_back("ttbar_mgdl_53X_slim_baby.root");
	// samples.push_back("ttbar_mgsl_53X_slim_baby.root");
	// samples.push_back("ttbar_mghad_53X_slim_baby.root");

	// samples.push_back("ttg_53X_slim_baby.root");
	// samples.push_back("ttw_53X_slim_baby.root");
	// samples.push_back("ttww_53X_slim_baby.root");
	// samples.push_back("ttz_53X_slim_baby.root");

	// samples.push_back("vvv_53X_slim_baby.root");

	// samples.push_back("ww_53X_slim_baby.root");

	// samples.push_back("wz2l2q_53X_slim_baby.root");
	// samples.push_back("wz3lnu_53X_slim_baby.root");


	// samples.push_back("zjets_53X_slim_baby.root");
	// samples.push_back("z1jet_53X_slim__baby.root");
	// samples.push_back("z2jet_53X_slim__baby.root");
	// samples.push_back("z3jet_53X_slim__baby.root");
	// samples.push_back("z4jet_53X_slim__baby.root");

	// samples.push_back("zhsm_53X_slim_baby.root");

	// samples.push_back("zz2l2nu_53X_slim_baby.root");
	// samples.push_back("zz2l2q_53X_slim_baby.root");
	// samples.push_back("zz4l_53X_slim_baby.root");


  }else if(sample == "closure_"){

	ntuples = "/home/users/cwelke/ZHmet_2013/output/V00-02-19";

	samples.push_back("zjetsmc_ee_baby.root");
	samples.push_back("zjetsmc_mm_baby.root");

	// ch->Add("/home/users/cwelke/ZMet_2012/output/V00-02-15/zjetsmc_ee_baby.root");
	// ch->Add("/home/users/cwelke/ZMet_2012/output/V00-02-15/zjetsmc_mm_baby.root");

  }

  for( size_t ind = 0; ind < samples.size(); ind++ ){
	ch->Add( Form( "%s/%s", ntuples.c_str(), samples.at(ind).c_str() ) );
  }

  zhist_looper looper( lowcut, highcut, selection );// = new zhist_looper();
  
  cout<<"running looper for: "<<suffix<<endl;
  looper.ScanChain(ch, true, -1, sample, suffix); 

  // suffix = "_emftight";
  // cout<<"running looper for: "<<suffix<<endl;
  // looper.ScanChain(ch, true, -1, sample, suffix); 

  // suffix = "_emfsupertight";
  // cout<<"running looper for: "<<suffix<<endl;
  // looper.ScanChain(ch, true, -1, sample, suffix); 

  // suffix = "_hoetight";
  // cout<<"running looper for: "<<suffix<<endl;
  // looper.ScanChain(ch, true, -1, sample, suffix); 

  // suffix = "_hoesupertight";
  // cout<<"running looper for: "<<suffix<<endl;
  // looper.ScanChain(ch, true, -1, sample, suffix); 

  // suffix = "_novtxweight";
  // cout<<"running looper for: "<<suffix<<endl;
  // looper.ScanChain(ch, true, -1, sample, suffix); 

  delete ch;
 

  return 0;
}
