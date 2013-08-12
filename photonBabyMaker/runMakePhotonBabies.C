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

  gROOT->ProcessLine(".L histtools.C+");
  // gROOT->ProcessLine(".L runMakePhotonBabies.C+");
  TChain* ch = new TChain("Events");

  // ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-30t-50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-470to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-800to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-*_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");

  //-----------------------------------------------------------------------------------
  // if( strcmp( prefix , "Photon_calo") ){

	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_1.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_1.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_1.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_1.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_2.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_2.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_2.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_2.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_3.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_3.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_3.root");
	ch->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19_full/merged_ntuple_3.root");

	/*  }else*/ if( strcmp( prefix , "Photon" ) == 0 ){
    pickSkimIfExists(ch,"/hadoop/cms/store/user/cwelke/CMSSW_5_2_3_patch4_V05-02-27/Photon_Run2012A-PromptReco-v1_AOD/unmerged/store*root");
    pickSkimIfExists(ch,"/hadoop/cms/store/user/cwelke/CMSSW_5_2_3_patch4_V05-02-27/SinglePhoton_Run2012B-PromptReco-v1_AOD/unmerged/store*root");
  }

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "DoubleElectron" ) == 0 ){
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012A-13Jul2012-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012B-13Jul2012-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012C-PromptReco-v1_AOD/V05-03-13/merged*root");
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012C-PromptReco-v2_AOD/V05-03-13/merged*root");
  }
  
  //-----------------------------------------------------------------------------------

  // else if( strcmp( prefix , "DoubleElectron_2012Cv2" ) == 0 ){
  //   pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012C-PromptReco-v2_AOD/V05-03-13/merged*root");
  // }
  

  //-----------------------------------------------------------------------------------

  else if( strcmp( prefix , "DoubleElectron_2012Cv2" ) == 0 ){
    pickSkimIfExists(ch,"PhotonTriggerSkim/DoubleElectron_Run2012C-PromptReco-v2_AOD/V05-03-13/merged*root");
  }
  

  //-----------------------------------------------------------------------------------

  // else{
  //   cout << "ERROR: cannot find sample " << prefix << endl;
  //   exit(0);
  // }
   else if ( strcmp( prefix, "Pt-15to30" ) == 0 ){	
  	pickSkimIfExists(ch, "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  }else if ( strcmp( prefix, "Pt-30to50" ) == 0 ){
  	pickSkimIfExists(ch, "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
   }else if ( strcmp( prefix, "Pt-50to80" ) == 0 ){
  	pickSkimIfExists(ch, "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-19/merged_ntuple_*.root");
   }else if ( strcmp( prefix, "Pt-80to120" ) == 0 ){
  	pickSkimIfExists(ch, "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
   }else if ( strcmp( prefix, "Pt-120to170" ) == 0 ){
  	pickSkimIfExists(ch, "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
  }else if ( strcmp( prefix, "Pt-170to300" ) == 0 ){
  	pickSkimIfExists(ch, "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
   }else if ( strcmp( prefix, "Pt-300to470" ) == 0 ){
  	pickSkimIfExists(ch, "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
   }else if ( strcmp( prefix, "Pt-470to800" ) == 0 ){
  	pickSkimIfExists(ch, "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-470to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
   }else if ( strcmp( prefix, "Pt-800to1400" ) == 0 ){
  	pickSkimIfExists(ch, "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-800to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-18/merged_ntuple_*.root");
	
   }
  //-----------------------------------------------------------------------------------
    
  bool calculateTCMET = false;  //recalculate tcmet on-the-fly?
  
  makePhotonBabies* myLooper = new makePhotonBabies();
  
  cout << "Running on sample " << prefix << endl;
  myLooper->ScanChain(ch, prefix, isData, calculateTCMET, -1 ,kFactor);
  
}

