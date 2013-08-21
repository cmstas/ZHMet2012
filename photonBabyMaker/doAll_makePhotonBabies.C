void doAll_makePhotonBabies( string input, bool isdata ){
  gROOT->ProcessLine(".L histtools.C+");
  gROOT->ProcessLine(".L runMakePhotonBabies.C+");

  runMakePhotonBabies( input.c_str()             , isdata  );  

  // runMakePhotonBabies("data_53X_2012A"             , true  );  
  // runMakePhotonBabies("data_53X_2012B"             , true  );  
  // runMakePhotonBabies("data_53X_2012C"             , true  );  
  // runMakePhotonBabies("data_53X_2012D"             , true  );  
  // runMakePhotonBabies("ttbar_flmc_53X"             , false  );  
  
  //--photon+jets---
  //runMakePhotonBabies("DoubleElectron"          , true  );   // DoubleElectron data
  //runMakePhotonBabies("DoubleElectron_2012Cv2"  , true  );   // DoubleElectron data
  //runMakePhotonBabies("Photon"                  , true  );   // Photon data
}
