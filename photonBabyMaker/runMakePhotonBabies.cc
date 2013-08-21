#include <string>
#include <stdexcept>
#include "TChain.h"
#include "TROOT.h"

using namespace std;

void doAllPhotonBabies( string prefix = "", string ntuplenumber = "", bool isData = false, float kFactor = 1.0, string version = "" );
void pickSkimIfExists( TChain *ch, const string& base )
{

  TChain *dummy = new TChain("Events");
  int nFiles = 0;
  if (dummy->Add(base.c_str())) {
    nFiles = ch->Add(base.c_str());
	cout << "Main " <<base.c_str() << " exists: use it. Loaded " 
		 << nFiles << " files" << endl;
  } else{
    cout << "Didn't find sample " << base << " , quitting" << endl;
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

int runMakePhotonBabies( string fileprefix = "", string ntuplenumber = "", bool isData = false, string version = "" )
{

  string cms2path = "../CORE/libCMS2NtupleMacrosCORE.so";
  cout<<"loading cms2 from: "<<cms2path<<endl;
  gROOT->ProcessLine(Form(".L %s", cms2path.c_str() ));
  cout<<"loading local libs: libmakePhotonBabies.so"<<endl;
  gROOT->ProcessLine(".L libmakePhotonBabies.so");

  doAllPhotonBabies( fileprefix.c_str(), ntuplenumber.c_str(), isData, 1., version.c_str() );

  return 0;
}

void doAllPhotonBabies( string prefix, string ntuplenumber, bool isData, float kFactor, string version )
{

  string percentage = "";

  if( ntuplenumber == "" ){
	percentage = "*";
  }else{
	percentage = ntuplenumber;
  }

  cout<<"Getting sample:"<<endl;

  TChain* ch = new TChain("Events");

  //-----------------------------------------------------------------------------------

  if( prefix == "data_53X_2012A" ){    
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged/merged_ntuple_%s.root", percentage.c_str() ) );
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged/merged_ntuple_%s.root", percentage.c_str() ) );
  }

  //-----------------------------------------------------------------------------------

  else if( prefix == "data_53X_2012B" ){    
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012B-13Jul2012-v1_AOD/merged/merged_ntuple_%s.root", percentage.c_str() ));
  }

  //-----------------------------------------------------------------------------------

  else if( prefix == "data_53X_2012C" ){    
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012C-24Aug2012-v1_AOD/merged/merged_ntuple_%s.root", percentage.c_str() ));
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012C-PromptReco-v2_AOD/merged/merged_ntuple_%s.root", percentage.c_str() ));
  }

  //-----------------------------------------------------------------------------------

  else if( prefix == "data_53X_2012D" ){    
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012D-16Jan2013-v1_AOD/merged/merged_ntuple_%s.root", percentage.c_str() ));
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012D-PromptReco-v1_AOD/merged/merged_ntuple_%s.root", percentage.c_str() ));
  }

  //-----------------------------------------------------------------------------------

  else if( prefix == "ttbar_slmc_53X" ){    
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1/V05-03-24/merged_ntuple_%s.root", percentage.c_str() ));
  }

  //-----------------------------------------------------------------------------------

  else if( prefix == "ttbar_flmc_53X" ){    
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2/V05-03-24/merged_ntuple_%s.root", percentage.c_str() ));
  }

  //-----------------------------------------------------------------------------------

  else if( prefix == "photon_mght40" ){
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/GJets_HT-40To100_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V19-v1/V05-03-31/merged_ntuple_%s.root", percentage.c_str() ));
  }

  else if( prefix == "photon_mght100" ){
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/GJets_HT-100To200_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V19-v1/V05-03-31/merged_ntuple_%s.root", percentage.c_str() ));
  }

  else if( prefix == "photon_mght200" ){
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/GJets_HT-200To400_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-31/merged_ntuple_%s.root", percentage.c_str() ));
  }

  else if( prefix == "photon_mght400" ){
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/GJets_HT-400ToInf_8TeV-madgraph_v3_Summer12_DR53X-PU_S10_START53_V7C-v1/V05-03-31/merged_ntuple_%s.root", percentage.c_str() ));
  }

  //-----------------------------------------------------------------------------------

  else if( prefix == "photon_15" ){
    pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }
  else if( prefix == "photon_30" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }
  else if( prefix == "photon_50" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }
  else if( prefix == "photon_80" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }
  else if( prefix == "photon_120" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }
  else if( prefix == "photon_170" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }
  else if( prefix == "photon_300" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }
  else if( prefix == "photon_470" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-470to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }
  else if( prefix == "photon_800" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-800to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }
  else if( prefix == "photon_1400" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/G_Pt-1400to1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }

  //-----------------------------------------------------------------------------------

  else if( prefix == "zjetsmc_ee" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYToEE_M-20_CT10_TuneZ2star_v2_8TeV-powheg-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
  }
  else if( prefix == "zjetsmc_mm" ){
	pickSkimIfExists(ch,Form( "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYToMuMu_M-20_CT10_TuneZ2star_v2_8TeV-powheg-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_%s.root", percentage.c_str() ));
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
  
  if( ntuplenumber != "" ){
    prefix = Form("%s_%s", prefix.c_str(), percentage.c_str() );
  }

  try
	{
	  makePhotonBabies* myLooper = new makePhotonBabies( version.c_str() );
  
	  cout << "Running on sample " << prefix << endl;
	  myLooper->ScanChain(ch, prefix.c_str(), isData, calculateTCMET, -1 ,kFactor);
	}
  catch (exception& e)	
  	{
  	  cout<<e.what()<<endl;
  	  cout << "Problem running looper." << endl;		
	}  
  
}

