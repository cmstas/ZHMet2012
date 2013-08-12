// #include <vector>
#include <iostream>

// #include "TDirectory.h"
// #include "TCut.h"
// #include "TChain.h"
// #include "TCanvas.h"
#include "TH1F.h"
#include "TFile.h"
// #include "TSystem.h"
// #include "TROOT.h"
// #include "TStyle.h"
// #include "vtxLooper.h"
// #include "vtxLooper.cc"
// #include "TEMPLATES.cc"

int makeAllvtxHistos( bool doMC = false, std::string selection = ""  )
{

  std::cout<<"running selection: "<<selection<<std::endl;

  gSystem->AddIncludePath("-I./");  
  gSystem->Load("libvtxLooper.so");
  // gROOT->ProcessLine(".L libvtxLooper.so");
  // gROOT -> ProcessLine(".x makeZhists()");
  // gROOT -> ProcessLine(".L TEMPLATES.cc+");
  // gROOT -> ProcessLine(".L vtxLooper.cc+");
  gROOT ->SetStyle("Plain");
  gStyle->SetOptStat(111111);

  TChain *ch = new TChain("T1"); 
  if( doMC ){ ch->Add("/home/users/cwelke/Analysis/Winter2012/photon_output/V00-02-06/photon_*_baby.root");
// ch->Add("/home/users/cwelke/Analysis/Winter2012/photon_output/V00-02-06/photon_15_baby.root");
  }else{ ch->Add("/home/users/cwelke/Analysis/Winter2012/photon_output/V00-02-05/data_53X_2012*_baby.root");
  }

  string rootfilename;

  if( doMC ){	
	rootfilename = Form("tempfiles/vtxreweight_DoubleElectron_19fb_MC%s_temp.root", selection.c_str() );
  }else{
	rootfilename = Form("tempfiles/vtxreweight_DoubleElectron_19fb_data%s_temp.root", selection.c_str() );
  }	

  TFile *fzratio = TFile::Open(rootfilename.c_str(),"READ");
  TH1F * hZ    = (TH1F*)fzratio->Get( "hZ"    ) -> Clone("h_zvtx");
  TH1F * hZPt  = (TH1F*)fzratio->Get( "hZPt"  ) -> Clone("h_zpt" );
  TH1F * hZmjj = (TH1F*)fzratio->Get( "hZMjj" ) -> Clone("h_zmjj" );
  TH1F * hZHt  = (TH1F*)fzratio->Get( "hZHt"  ) -> Clone("h_zht" );

  // vtxLooper * looper = new vtxLooper();  
  // looper -> setzvtx( hZ );
  // looper -> setzvar( hZPt );
  // looper -> setgvar( hZPt );
  // // looper -> setzvar( hZHt );
  // // looper -> setgvar( hZHt );
  // // looper -> setzmjj( hZmjj );
  // // looper -> setgmjj( hZmjj );
  // looper -> ScanChain( ch, true, -1, 0, !doMC );

  vtxLooper * looper = new vtxLooper(selection);  
  looper -> setzvtx( hZ );
  looper -> setzvar( hZPt );
  looper -> setgvar( hZPt );
  looper -> ScanChain( ch, true, -1, 0, !doMC );
  
  vtxLooper * looper2 = new vtxLooper(selection);  
  looper2 -> setzvar( hZHt );
  looper2 -> setgvar( hZHt );
  looper2 -> ScanChain( ch, true, -1, 1, !doMC );

  vtxLooper * looper3 = new vtxLooper(selection);  
  looper3 -> setzmjj( hZmjj );
  looper3 -> setgmjj( hZmjj );
  looper3 -> ScanChain( ch, true, -1, 2, !doMC );

  return 0;
}
