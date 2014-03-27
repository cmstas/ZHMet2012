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

//stuff from tools/BTagReshaping
#include "BTagReshaping.h"
class BTagShapeInterface;

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// ROOT
class TChain;

class miniBabyMaker
{
public:
  miniBabyMaker();
  miniBabyMaker( std::string babyfilename );
  ~miniBabyMaker();
  
  int ScanChain( TChain * chain, int nEvents = -1, std::string suffix = "" );
  void SetGoodRun( std::string filename );
  void SetLuminosity( float luminosity );
  void SetBTagShapeInterface( std::string filename );
  void SetCSVWorkingPoint( float workingpoint );

private:
  
  void MakeBabyNtuple();
  void Initialize();
  void FillBabyNtuple();
  void reshapeCSV( std::vector <float> &csvvals );

  float luminosity_;

  std::string goodrunfilename_;

  BTagShapeInterface * nominalShape_;

  float csvWorkingPoint_;

  //Tree pointer
  TTree * babyTree_;

  //histo file pointer
  std::string babyFileName_;
  TFile * babyFile_;

  //baby variables
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //event variables
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  int run_;
  int lumi_;
  int event_;
  bool isdata_;

  float pfmet_;
  float pfmetphi_;

  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //jet variables
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  LorentzVector * jet1_;
  LorentzVector * jet2_;
  LorentzVector * jet3_;
  LorentzVector * jet4_;

  int njets_;
  float ht_;

  float mjj_;//leading jets
  float ptjj_;
  float mt2j_;

  float csv1_;
  float csv2_;
  float csv3_;
  float csv4_;

  float csv1_old_;
  float csv2_old_;
  float csv3_old_;
  float csv4_old_;

  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //bjet variables - assume medium btagging unless otherwise specified
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  LorentzVector * bjet1_;
  LorentzVector * bjet2_;
  LorentzVector * bjet3_;
  LorentzVector * bjet4_;

  int nbcsvl_;
  int nbcsvm_;
  int nbcsvt_;

  int nbcsvl_old_;
  int nbcsvm_old_;
  int nbcsvt_old_;

  float mbb_;
  float ptbb_;
  float mt2b_;

  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  //lepton variables
  //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
  LorentzVector * lep1_;
  LorentzVector * lep2_;
  LorentzVector * lep3_;

  float mll_;//leading leps
  float ptll_;

  bool hastau_;

  int leptype_;//0 = ee, 1 = mm, 2 = em

  float lep1pt_;
  float lep2pt_;
  float lep3pt_;

  float lep1dz_;
  float lep2dz_;
  float lep3dz_;

  float lep1iso_;
  float lep2iso_;
  float lep3iso_;

  float lep1d0_;
  float lep2d0_;
  float lep3d0_;


};
#endif
