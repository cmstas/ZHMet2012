#ifndef COMMONLOOPERUTILS_H
#define COMMONLOOPERUTILS_H

#include <vector>
#include "TH1.h"

// float dRGenJet ( LorentzVector p4, std::vector <LorentzVector> &genjetsp4, bool isData, float ptcut = 20.0 );
void fillUnderOverFlow( TH1F * &h1, const float value, const float weight);
float deltaPhi( const float phi1 , const float phi2);

#endif
