#ifndef VTXLOOPER_H
#define VTXLOOPER_H

#include <vector>
// #include <map>
// #include <string>

//root stuff
#include "TChain.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "Math/LorentzVector.h"
#include "Math/VectorUtil.h"
// #include "TString.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// class TChain;

class vtxLooper
{
  
public:

  // vtxLooper();
  vtxLooper( std::string input_selection = "" );
  // vtxLooper( std::vector <double> binning );
  ~vtxLooper();
  
  void setBinning( std::vector <double> binning );
  void setzvtx( TH1F * &zhist );
  void setzvar( TH1F * &zhist );
  void setgvar( TH1F * &zhist );
  void setzmjj( TH1F * &zhist );
  void setgmjj( TH1F * &zhist );
  int ScanChain( TChain* chain, bool fast, int nEvents, Int_t runnumber, bool isdata );
  bool getbjets( const Float_t workingpoint );
  bool getbjets( const Float_t workingpoint, const std::vector <Float_t> &csvvals );
  void fillmcfahists( const Float_t workingpoint, TH1F * &photon_mcfabjet1, TH1F * &photon_mcfabjet2, const double weight );
  void fillHist(  TH1F* &hist, double variable, const double weight );


private:

  std::string selection;

  //hists for vtx reweighting
  TH1F * h20;
  TH1F * h30;
  TH1F * h50;
  TH1F * h70;
  TH1F * h90;
  TH1F * hall;

  //hists for variable reweighting
  TH1F * hgmjj;
  TH1F * hzmjj;
  TH1F * hgvar;
  TH1F * hzvar;
  TH1F * hzvtx;

  //variables for binning
  std::vector <double> bins;
  std::vector <LorentzVector> goodbs;

  //variables for cut selection
  bool dotwobtag;
  bool dobveto;
  bool domjjhi;
  bool domjjlo;

  bool dogenbs;
  Int_t ngenbs;
  // bool domt2jhi;
  // bool domt2jlo;

};
#endif
  
