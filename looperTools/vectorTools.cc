#include "TMath.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

float deltaPhi( float phi1 , float phi2 ) {
  float dphi = fabs( phi1 - phi2 );
  if( dphi > TMath::Pi() ) dphi = TMath::TwoPi() - dphi;
  return dphi;
}

double dRbetweenVectors (const LorentzVector &vec1, const LorentzVector &vec2){
  float deta = vec1.eta()-vec2.eta();
  float dphi = deltaPhi(vec1.phi(), vec2.phi());
  return sqrt(dphi*dphi + deta*deta);
}

