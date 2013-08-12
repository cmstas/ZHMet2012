// #include <vector>
#include <map>
#include <string>
// #include <set>
// #include <stdio.h>
// #include <stdlib.h>

//root stuff
// #include "TSystem.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TH1F.h"
#include "Math/LorentzVector.h"
#include "Math/VectorUtil.h"
// #include
// #include "TString.h"

#ifndef ZHIST_LOOPER_H
#define ZHIST_LOOPER_H

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// ROOT
class TChain;

class zhist_looper
{
public:
  zhist_looper();
  zhist_looper( Float_t mT2jlow, Float_t mT2jhi, std::string input_selection );
  ~zhist_looper();
  
  int ScanChain ( TChain * chain, bool fast = true, int nEvents = -1, std::string skimFilePrefix = "test", std::string suffix = "" );
  void setpthists( double minPT = 0.0, double maxPT = 0.0 );
  void seththists( double minHT = 0.0, double maxHT = 0.0 );
  void setmjjhists( double minMJJ = 0.0, double maxMJJ = 0.0 );
  bool getbjets( const Float_t workingpoint );
  bool getbjets( const Float_t workingpoint, const std::vector <Float_t> &csvvals );
  void fillmcfahists( const Float_t workingpoint, TH1F * &photon_mcfabjet1, TH1F * &photon_mcfabjet2, const double weight );
  Float_t getMT2b( const std::vector <LorentzVector> &leps, const std::vector <LorentzVector> &bjets );
  std::vector <Float_t> getMlb( const std::vector <LorentzVector> &leps, const std::vector <LorentzVector> &bjets );
  void setSample( std::string samplename );
  void bookHist(std::map<std::string,TH1F*> &hist_map, const std::string &histname, const std::string &histtitle, unsigned int nbins, float min, float max);
  void bookHists();
  void fillHist( const std::string &histoname, const double variable, const double weight );
  void fillHist(  TH1F* &hist, double variable, const double weight );
  void subtract_ofevents();
  void saveHists( std::map < std::string, TH1F* > &hist_map );
  void saveHists();
  Float_t getBinomialError(Float_t num, Float_t deno );

private:
  
  TH1F * z_mcfabjet1;
  TH1F * z_mcfabjet2;

  TH1F * z_metwithbs;
  TH1F * z_metwithcs;

  //bjets
  std::vector <LorentzVector> goodbs;
  
  std::string basename;
  std::string selection;

  //some setting variables
  bool checkJetDr;
  double luminosity;
  Float_t mt2jlow;
  Float_t mt2jhi;

  //reweight file
  TFile * reweightFile_;
  TH1F * hvtxreweight;
  string rootfilename;

  //histo file pointer
  TFile * outfile_;

  //binning vars
  std::vector <double> ptbins;
  std::vector <double> htbins;
  std::vector <double> mjjbins;

  //variables for cut selection
  bool dotwobtag;
  bool dobveto;
  bool domjjhi;
  bool domjjlo;
  bool domt2jhi;
  bool domt2jlo;

  bool dogenbs;
  Int_t ngenbs;

  //histograms
  TH1F* hZMjj;
  TH1F* hZMjjof;
  TH1F* hZMjjsf;

  // //histos for pT reweighting
  TH1F* hZPt;
  TH1F* hZPtof;
  TH1F* hZPtsf;

  // //histos for hT reweighting
  TH1F* hZHt;
  TH1F* hZHtof;
  TH1F* hZHtsf;

  // //histos for vertex reweighting
  TH1F* hZ;

  std::map < std::string, TH1F* > evthists_;

};
#endif
