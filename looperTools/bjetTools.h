#include <vector>

#include "TROOT.h"
#include "TMath.h"
#include "Math/LorentzVector.h"
#include "../CORE/MT2/MT2.h"

#ifndef BJETTOOLS_H
#define BJETTOOLS_H

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class BJets 
{
public: 
  
  BJets();

  //constructor for general number of jets
  BJets( const float workingpoint, const std::vector <float> &jetcsv, const std::vector <LorentzVector> &jets );

  //constructor for 2 jets
  BJets( const float workingpoint, 
		 const float &jetcsv1, const float &jetcsv2,
		 const LorentzVector &jet1, const LorentzVector &jet2 
		 );

  //constructor for 3 jets
  BJets( const float workingpoint, 
		 const float &jetcsv1, const float &jetcsv2, const float &jetcsv3,
		 const LorentzVector &jet1, const LorentzVector &jet2, const LorentzVector &jet3 
		 );

  //destructor
  ~BJets();

  //returns true if two good bs are found
  bool twogoodbs();
  int getnbtags();

  //variables to deal with gen jets info
  void setAlgo( const std::vector <int> &algoValue );
  int getJetFlavor( const unsigned int index );
  bool isGenb( const unsigned int index );
  bool isbtagged( const unsigned int index );

  //returns the two bjets with sorted by pt high to low
  std::vector <LorentzVector> getbjets();

  //returns mlb variables
  std::vector <float> getMlb( const std::vector <LorentzVector> &leps );
  std::vector <float> smartSortMlb( const std::vector <float> &mlb_unsorted );
  float getminMlb( const std::vector <LorentzVector> &leps );

  //returns mbb
  float getMbb();

  //returns mt2j variables
  float getMT2b( const float met, const float metphi, const std::vector <LorentzVector> &leps );

  //broken for now
  std::vector <float> getminpTlb();

private:

  std::vector <LorentzVector> bjets;
  std::vector <int> jetType;
  std::vector <bool> isbjet;
  bool twogoodjets;

};

#endif
