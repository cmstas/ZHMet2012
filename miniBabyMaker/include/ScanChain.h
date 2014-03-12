#ifndef SCANCHAIN_H
#define SCANCHAIN_H

// #include <vector>
#include <string>

//root stuff
#include "TChain.h"
// #include "TChainElement.h"
// #include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "Math/LorentzVector.h"
// #include "Math/VectorUtil.h"

// #include "ZMET.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// ROOT
class TChain;

class miniBabyMaker
{
public:
  miniBabyMaker();
  ~miniBabyMaker();
  
  int ScanChain( TChain * chain, int nEvents = -1, std::string suffix = "" );

private:
  
  void MakeBabyNtuple();
  void Initialize();
  void FillBabyNtuple();

  float luminosity;

  //Tree pointer
  TTree * babyTree_;

  //histo file pointer
  std::string babyFileName_;
  TFile * babyFile_;

  //baby variables
  LorentzVector * lep1_;
  LorentzVector * lep2_;

  float lep1pt_;
  float lep2pt_;

};
#endif
