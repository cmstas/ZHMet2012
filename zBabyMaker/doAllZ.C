int doAllZ( string fileprefix = "", string ntuplenumber = "", bool isdata = false )
{

  gROOT->ProcessLine(".L histtools.C+");
  gROOT->ProcessLine(".L runZLooper.C+");

  runZLooper( fileprefix.c_str(), ntuplenumber.c_str(), isdata );

  return 0;

}




