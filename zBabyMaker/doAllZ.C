#include "TROOT.h"

#include <cstdlib>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

int doAllZ( string fileprefix = "", string ntuplenumber = "", bool isdata = false )
{

  //compile libraries
  gROOT->ProcessLine(".L ../CORE/libCMS2NtupleMacrosCORE.so");
  // gROOT->ProcessLine(".L ../CORE/CMS2.cc+");
  // gROOT->ProcessLine(".L ../CORE/utilities.cc+");
  // gROOT->ProcessLine(".L ../CORE/ssSelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/electronSelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/electronSelectionsParameters.cc+");
  // gROOT->ProcessLine(".L ../CORE/MITConversionUtilities.cc+");
  // gROOT->ProcessLine(".L ../CORE/muonSelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/eventSelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/ttbarSelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/trackSelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/metSelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/jetSelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/photonSelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/triggerUtils.cc+");
  // gROOT->ProcessLine(".L ../CORE/triggerSuperModel.cc+");
  // gROOT->ProcessLine(".L ../CORE/mcSelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/susySelections.cc+");
  // gROOT->ProcessLine(".L ../CORE/mcSUSYkfactor.cc+");
  // gROOT->ProcessLine(".L ../CORE/SimpleFakeRate.cc+");
  // gROOT->ProcessLine(".L ../CORE/MT2/MT2Utility.cc+");
  // gROOT->ProcessLine(".L ../CORE/MT2/MT2.cc+");
  gROOT->ProcessLine(".L ../Tools/goodrun.cc+");
  gROOT->ProcessLine(".L ../Tools/vtxreweight.cc+");
  gROOT->ProcessLine(".L ../Tools/msugraCrossSection.cc+");
  gROOT->ProcessLine(".L ../Tools/bTagEff_BTV.cc+");

  gROOT->ProcessLine(".L histtools.C+");
  gROOT->ProcessLine(".L Z_looper.C+");
  gROOT->ProcessLine(".L runZLooper.C+");

  runZLooper( fileprefix.c_str(), ntuplenumber.c_str(), isdata );

  return 0;

}




