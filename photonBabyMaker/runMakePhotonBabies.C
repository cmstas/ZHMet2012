#include "TChain.h"
#include "makePhotonBabies.C"


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


void runMakePhotonBabies(char* prefix , bool isData = true, float kFactor = 1.){

  TChain* ch = new TChain("Events");

  //-----------------------------------------------------------------------------------

  if( strcmp( prefix , "data_53X_2012A" ) == 0 ){    
    //pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012A-13Jul2012-v1_AOD/V05-03-18_slim/merged_ntuple_999999_9_1_skim.root");
    // pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012A-13Jul2012-v1_AOD/V05-03-18_slim/merged*root");
    // pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/V05-03-18_slim/merged*root");
    pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged/merged_ntuple_*.root");
    pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged/merged*.root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "data_53X_2012B" ) == 0 ){    
    // pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012B-13Jul2012-v1_AOD/V05-03-18_slim/merged*root");
    pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012B-13Jul2012-v1_AOD/merged/merged*.root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "data_53X_2012C" ) == 0 ){    
    // pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012C-24Aug2012-v1_AOD/V05-03-18_slim/merged*root");
    // pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012C-PromptReco-v2_AOD/V05-03-18_slim/merged*root");
    pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012C-24Aug2012-v1_AOD/merged/merged*root");
    pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged/merged*root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "data_53X_2012D" ) == 0 ){    
    // pickSkimIfExists(ch,"PhotonTriggerSkim_slim/DoubleElectron_Run2012D-PromptReco-v1_AOD/V05-03-18_slim/merged*root");
    pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012D-16Jan2013-v1_AOD/merged/merged*root");
    pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012D-PromptReco-v1_AOD/merged/merged*root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "ttbar_slmc_53X" ) == 0 ){    
    pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1/V05-03-24/merged_ntuple_*.root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "ttbar_flmc_53X" ) == 0 ){    
    pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-24/merged_ntuple_*.root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "Photon" ) == 0 ){
    pickSkimIfExists(ch,"/hadoop/cms/store/user/cwelke/CMSSW_5_2_3_patch4_V05-02-27/Photon_Run2012A-PromptReco-v1_AOD/unmerged/store*root");
    pickSkimIfExists(ch,"/hadoop/cms/store/user/cwelke/CMSSW_5_2_3_patch4_V05-02-27/SinglePhoton_Run2012B-PromptReco-v1_AOD/unmerged/store*root");
  }

  else if( strcmp( prefix ,"photon_15" ) == 0 ){
    pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*.root");
  }
  else if( strcmp( prefix ,"photon_30" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*.root");
  }
  else if( strcmp( prefix ,"photon_50" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*.root");
  }
  else if( strcmp( prefix ,"photon_80" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*.root");
  }
  else if( strcmp( prefix ,"photon_120" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*.root");
  }
  else if( strcmp( prefix ,"photon_170" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*.root");
  }
  else if( strcmp( prefix ,"photon_300" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*.root");
  }
  else if( strcmp( prefix ,"photon_470" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-470to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*.root");
  }
  else if( strcmp( prefix ,"photon_800" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-800to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*.root");
  }
  else if( strcmp( prefix ,"photon_1400" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-1400to1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*.root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix ,"zjetsmc_ee" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYToEE_M-20_CT10_TuneZ2star_v2_8TeV-powheg-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*");
  }
  else if( strcmp( prefix ,"zjetsmc_mm" ) == 0 ){
	pickSkimIfExists(ch,"/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYToMuMu_M-20_CT10_TuneZ2star_v2_8TeV-powheg-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_*");
	  }

  else if( strcmp( prefix , "DoubleElectron" ) == 0 ){
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012A-13Jul2012-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012B-13Jul2012-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012C-PromptReco-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012C-PromptReco-v2_AOD/V05-03-13/merged*root");
  }
  
  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "DoubleElectron_2012Cv2" ) == 0 ){
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012C-PromptReco-v2_AOD/V05-03-13/merged*root");
  }
  
  //-----------------------------------------------------------------------------------

  else{
    cout << "ERROR: cannot find sample " << prefix << endl;
    exit(0);
  }

  //-----------------------------------------------------------------------------------
    
  bool calculateTCMET = false;  //recalculate tcmet on-the-fly?
  
  cout << endl;
  cout << "Checking for corrupt files" << endl;
  cout << "Entries " << ch->GetEntries() << endl;
  ch->Draw("evt_run");
  cout << endl;
  
  makePhotonBabies* myLooper = new makePhotonBabies();
  
  cout << "Running on sample " << prefix << endl;
  myLooper->ScanChain(ch, prefix, isData, calculateTCMET, -1 ,kFactor);
  
}

