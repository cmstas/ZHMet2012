

float getZHGMSBCrossSection( int mu ){

  float xsec = -1;
  if( mu == 130 ) xsec = 3.248;
  if( mu == 150 ) xsec = 1.876;
  if( mu == 175 ) xsec = 1.027;
  if( mu == 200 ) xsec = 0.608;
  if( mu == 225 ) xsec = 0.377;
  if( mu == 250 ) xsec = 0.244;
  if( mu == 275 ) xsec = 0.162;
  if( mu == 300 ) xsec = 0.111;
  if( mu == 325 ) xsec = 0.0779;
  if( mu == 350 ) xsec = 0.0553;
  if( mu == 375 ) xsec = 0.0401;
  if( mu == 400 ) xsec = 0.0294;
  if( mu == 425 ) xsec = 0.0218;
  if( mu == 450 ) xsec = 0.0163;
  if( mu == 475 ) xsec = 0.0123;
  if( mu == 500 ) xsec = 0.0094;
      
  if( xsec < 0 ){
	std::cout << __FILE__ << " " << __LINE__ << " ERROR! couldn't find GMSB cross section for mu " << mu << std::endl;
  }

  return xsec;

}

