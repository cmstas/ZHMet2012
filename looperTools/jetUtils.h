//c stuff
#include <vector>
// #include <map>
// #include <string>
// #include <stdio.h>
// #include <stdlib.h>

//root stuff
// #include "TSystem.h"
#include "Math/LorentzVector.h"
#include "Math/VectorUtil.h"

#ifndef JETUTILS_H
#define JETUTILS_H

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

std::vector <LorentzVector> get_bjets( const std::vector <LorentzVector> &jets, const std::vector <float> &csvvals, const float workingpoint );
float getMT2bInc( const std::vector <LorentzVector> &leps, const std::vector <LorentzVector> &bjets, const float met, const float metphi );

float getMbb_2jets( const std::vector <LorentzVector> &bjets );

bool sortByCSVValues (const std::pair <float, int> &csv1, const std::pair<float, int> &csv2);
float getMbb_multijets( const std::vector <LorentzVector> &jets, const std::vector <float> &csvvals, const float workingpoint );


#endif
