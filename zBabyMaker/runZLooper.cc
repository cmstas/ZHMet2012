#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

#include "TROOT.h"
#include "TChain.h"

using namespace std;

void doAllZ( string prefix, string ntuplenumber, bool isData, float kFactor, string version );
void pickSkimIfExists( TChain *ch, const std::string& base )
{

  TChain *dummy = new TChain("Events");
  int nFiles = 0;
  if (dummy->Add(base.c_str())) {
    nFiles = ch->Add(base.c_str());
    std::cout << "Main " <<base.c_str() << " exists: use it. Loaded " 
              << nFiles << " files" << std::endl;
  } else{
    std::cout << "Didn't find sample " << base << " , quitting" << std::endl;
    exit(0);
  }

  // be paranoid
  if (nFiles == 0) {
    std::cout << "ERROR: expected to read files " 
              << base.c_str() << "  but found none" << std::endl;
    assert(0);
  }

  return;
}

int runZLooper( string fileprefix = "", string ntuplenumber = "", bool isdata = false, string version )
{
  //compile libraries
  gROOT->ProcessLine(".L ../CORE/libCMS2NtupleMacrosCORE.so");
  gROOT->ProcessLine(".L libZ_looper.so");
  doAllZ( fileprefix.c_str(), ntuplenumber.c_str(), isdata, 1.0, version );
  return 0;
}


void doAllZ( string prefix, string ntuplenumber, bool isData, float kFactor, string version )
{

  TChain* ch = new TChain("Events");
  string basentuplelocation = "";

  //zjets exclusive----------------------------------------------------------------------------------------
  vector <string> njet;
  njet.push_back("1");
  njet.push_back("2");
  njet.push_back("3");
  njet.push_back("4");

  vector <string> partialsample;
  partialsample.push_back("");
  partialsample.push_back("0");
  partialsample.push_back("1");
  partialsample.push_back("2");
  partialsample.push_back("3");
  partialsample.push_back("4");
  partialsample.push_back("5");
  partialsample.push_back("6");
  partialsample.push_back("7");
  partialsample.push_back("8");
  partialsample.push_back("9");

  // try
  // 	{	
  
  for( size_t njeti = 0; njeti < njet.size(); njeti++ ){
	for( size_t partiali = 0; partiali < partialsample.size(); partiali++ ){

	  if( njet.at(njeti) == "1" ){
		if( prefix == Form( "z%sjet_53X_slim_%s", 
							njet.at(njeti).c_str(), 
							partialsample.at(partiali).c_str() ) ){
		  pickSkimIfExists(ch, Form(
									"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY%sJetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/merged_ntuple_%s*.root", 
									njet.at(njeti).c_str(), 
									partialsample.at(partiali).c_str() ) );
		  break;
		}		
		
	  }else if( njet.at(njeti) == "2" ){
		if( prefix == Form( "z%sjet_53X_slim_%s", 
							njet.at(njeti).c_str(), 
							partialsample.at(partiali).c_str() ) ){
		  
		  pickSkimIfExists(ch, Form(
									"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY%sJetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7C-v1/V05-03-25/merged_ntuple_%s*.root", 
									njet.at(njeti).c_str(), 
									partialsample.at(partiali).c_str() ) );
		  break;
		}				
		
	  }else if( njet.at(njeti) == "3" ){
		if( prefix == Form( "z%sjet_53X_slim_%s", 
							njet.at(njeti).c_str(), 
							partialsample.at(partiali).c_str() ) ){
    	
		  pickSkimIfExists(ch, Form(
									"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY%sJetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/merged_ntuple_%s*.root", 
									njet.at(njeti).c_str(), 
									partialsample.at(partiali).c_str() ) );
		  break;
		}		

	  }else if( njet.at(njeti) == "4" ){
		if( prefix == Form( "z%sjet_53X_slim_%s", 
							njet.at(njeti).c_str(), 
							partialsample.at(partiali).c_str()) ){    	
		  
		  pickSkimIfExists(ch, Form(
									"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY%sJetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_%s*.root", 
									njet.at(njeti).c_str(), 
									partialsample.at(partiali).c_str() ) );
		  break;
		}
		
	  }
	}
  }

// }

  // catch (exception& e)	
  // 	{
  // 	  cout<<e.what()<<endl;
  // 	  cout << "Problem with vector size. Moving on to other sample." << endl;		
  // 	  // return;
	  
  // 	}
  
  if( ch->GetEntries() == 0 ){  

	//edge sync DYJets MC-----------------------------------------------------------------------------------
	if( prefix == "edge_sync" ){
	  pickSkimIfExists(ch,"/nfs-7/userdata/cwelke/CMSSW_testing/DYJets_m50/merged/zjets_cms2_unprocessed_ntuple.root");
	}

	//zjets ee powheg-----------------------------------------------------------------------------------
	else if( prefix == "edge_sync_newvars" ){
	  pickSkimIfExists(ch,"/nfs-7/userdata/cwelke/CMSSW_testing/DYJets_m50/merged/zjets_cms2_unprocessed_ntuple.root");
	}

	//zjets ee powheg-----------------------------------------------------------------------------------
	else if( prefix == "zjetsmc_ee" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYToEE_M-20_CT10_TuneZ2star_v2_8TeV-powheg-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*");
	}

	//zjets mumu powheg-----------------------------------------------------------------------------------
	else if( prefix == "zjetsmc_mm" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYToMuMu_M-20_CT10_TuneZ2star_v2_8TeV-powheg-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*");
	}
	
	//private signal MC-----------------------------------------------------------------------------------
	else if( prefix == "TChizh_53X_150_1" ){    
	  pickSkimIfExists(ch,"/nfs-7/userdata/cwelke/TChizh/CMS2/unmerged/TChizh_150_1.root");
	}
	else if( prefix == "TChizh_53X_200_1" ){    
	  pickSkimIfExists(ch,"/nfs-7/userdata/cwelke/TChizh/CMS2/unmerged/TChizh_200_1.root");
	}
	else if( prefix == "TChizh_53X_250_1" ){    
	  pickSkimIfExists(ch,"/nfs-7/userdata/cwelke/TChizh/CMS2/unmerged/TChizh_250_1.root");
	}
	else if( prefix == "TChizh_53X_scan" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/SMS-TChiZH_ZllHbb_2J_mChargino-130to500_mLSP-1to370_TuneZ2star_8TeV-madgraph-tauola/V05-03-31/merged_ntuple_*.root");
	}

	//all data-----------------------------------------------------------------------------------
	//data_53X_2012A_recover_06Aug2012-----------------------------------------------------------------------------------
	else if( prefix == "data_53X_2012A_recover_06Aug2012" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged/merged*.root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/merged/merged*.root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012A-recover-06Aug2012-v1_AOD/merged/merged_ntuple_*.root");
	}

	else if( prefix == "data_53X_2012A" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged/merged_ntuple_*.root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012A-13Jul2012-v1_AOD/merged/merged_ntuple_*.root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012A-13Jul2012-v1_AOD/merged/merged_ntuple_*.root");
	}

	else if( prefix == "data_53X_2012B" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012B-13Jul2012-v1_AOD/merged/merged*.root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012B-13Jul2012-v4_AOD/merged/merged*.root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012B-13Jul2012-v1_AOD/merged/merged*.root");
	}

	else if( prefix == "data_53X_2012C_ecalreco" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012C-EcalRecover_11Dec2012-v1_AOD/merged/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012C-EcalRecover_11Dec2012-v1_AOD/merged/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012C-EcalRecover_11Dec2012-v1_AOD/merged/merged*root");

	}

	else if( prefix == "data_53X_2012C_24Aug2012" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012C-24Aug2012-v1_AOD/merged/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012C-24Aug2012-v1_AOD/merged/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012C-24Aug2012-v1_AOD/merged/merged*root");
	}

	else if( prefix == "data_53X_2012C" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012C-PromptReco-v2_AOD/merged/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012C-PromptReco-v2_AOD/merged/merged*root");
	}

	else if( prefix == "data_53X_2012D_16Jan2013" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012D-16Jan2013-v1_AOD/merged/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012D-16Jan2013-v2_AOD/merged/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012D-16Jan2013-v2_AOD/merged/merged*root");
	}

	else if( prefix == "data_53X_2012D" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012D-PromptReco-v1_AOD/merged/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012D-PromptReco-v1_AOD/merged/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012D-PromptReco-v1_AOD/merged/merged*root");
	}	

	//zjets inclusive----------------------------------------------------------------------------------------
	else if( prefix == "zjets_53X_slim" ){    
	  pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_%s*.root", ntuplenumber.c_str()) );
	}


	//single top----------------------------------------------------------------------------------------
	else if( prefix == "t_53X_slim" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TToDilepton_tW-channel-DR_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/merged*root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TBarToDilepton_tW-channel-DR_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/merged*root");
	}

	//ttbar - Exclusive----------------------------------------------------------------------------------------
	else if( prefix == "ttbar_mgdl_53X_slim" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-24/merged_ntuple_*.root");
	}
	else if( prefix == "ttbar_mgsl_53X_slim" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1/V05-03-24/merged_ntuple_*.root");
	}
	else if( prefix == "ttbar_mghad_53X_slim" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1/V05-03-24/merged_ntuple_*.root"); 
	}

	//SM z(ll)h(bb)----------------------------------------------------------------------------------------
	else if( prefix == "zhsm_53X_slim" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/ZH_ZToLL_HToBB_M-125_8TeV-powheg-herwigpp_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_*.root"); 
	}

	//ZZ----------------------------------------------------------------------------------------
	else if( prefix == "zz2l2nu_53X_slim" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/ZZJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v3/V05-03-23/merged_ntuple_*.root"); 
	}
	else if( prefix == "zz2l2q_53X_slim" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/ZZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_*.root"); 
	}
	else if( prefix == "zz4l_53X_slim" ){    
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_*.root"); 
	}

	//WZ----------------------------------------------------------------------------------------
	else if( prefix == "wz2l2q_53X_slim" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_*.root"); 
	}
	else if( prefix == "wz3lnu_53X_slim" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_*.root"); 
	}

	//WW----------------------------------------------------------------------------------------
	else if( prefix == "ww_53X_slim" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_*.root"); 
	}

	//ttv----------------------------------------------------------------------------------------
	else if( prefix == "ttz_53X_slim" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTZJets_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_*.root"); 
	}
	else if( prefix == "ttw_53X_slim" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_*.root"); 
	}
	else if( prefix == "ttg_53X_slim" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTGJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_*.root"); 
	}
	else if( prefix == "ttww_53X_slim" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_*.root"); 
	}
	else if( prefix == "tbz_53X_slim" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TBZToLL_4F_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1/V05-03-23/merged_ntuple_*.root"); 
	}

	//vvv----------------------------------------------------------------------------------------
	else if( prefix == "vvv_53X_slim" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/ZZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-24/merged_ntuple_*.root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WWWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-24/merged_ntuple_*.root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WZZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-24/merged_ntuple_*.root");
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WWZNoGstarJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-24/merged_ntuple_*.root");
	}

	//zbb to 2l----------------------------------------------------------------------------------------
	else if( prefix == "zbb2l_53X_slim" ){
	  pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/ZbbToLL_massive_M-50_TuneZ2star_8TeV-madgraph-pythia6_tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/merged_ntuple_*.root");
	}

	//----------------------------------------------------------------------------------------
	else{
	  cout << "ERROR: cannot find sample " << prefix << endl;
	  exit(0);
	}
  }

  //----------------------------------------------------------------------------------------
  cout << endl << endl;
  cout << "Checking for corrupt files" << endl;
  cout << "Entries in chain: " << ch->GetEntries() << endl;
  ch->Draw("evt_nEvts");
  cout << endl << endl;


  bool calculateTCMET = false;  //recalculate tcmet on-the-fly?
  
  try
	{
	  Z_looper* myLooper = new Z_looper( version );  
	  cout << "Running on sample " << prefix << endl;
	  myLooper->ScanChain(ch, prefix.c_str(), isData, calculateTCMET, -1 ,kFactor);
	}
  catch (exception& e)	
  	{
  	  cout<<e.what()<<endl;
  	  cout << "Problem with vector size. Exiting." << endl;		
	}  

}
