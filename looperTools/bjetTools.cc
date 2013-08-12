#include <vector>

#include "bjetTools.h"

using namespace std;

BJets::BJets()
{
  twogoodjets = false;
  bjets.clear();
  jetType.clear();
}

BJets::BJets( const float workingpoint, const vector <float> &jetcsv, const vector <LorentzVector> &jets )
{
  twogoodjets = false;
  bjets.clear();
  jetType.clear();
  isbjet.clear();

  if( jetcsv.size() != jets.size() ){
	cout<<"warning, jet csv vector different size from jet vector!"<<endl;
  }

  for( size_t jeti = 0; jeti < jets.size(); jeti++ ){
	if( jetcsv.at(jeti) > workingpoint ){
	  bjets.push_back(jets.at(jeti));
	  isbjet.push_back(true);
	}
	isbjet.push_back(false);
	jetType.push_back(-999);
  }  
  if( bjets.size() == 2 ){ twogoodjets = true;}
}

BJets::~BJets()
{
}

bool BJets::twogoodbs()
{
  return twogoodjets;
}

int BJets::getnbtags()
{
  return bjets.size();
}

void BJets::setAlgo( const vector <int> &algoValue )
{
  for( size_t index = 0; index < algoValue.size(); index++ ){
	jetType.at(index) = algoValue.at(index);
  }
  return;
}

int BJets::getJetFlavor( const unsigned int index )
{
  return jetType.at(index);
}

bool BJets::isGenb( const unsigned int index )
{
  if( abs( jetType.at(index) ) == 5 ){ return true;
  }else if( jetType.at(index) == -999 ){ 
	cout<<"MC algo not set."<<endl;
	cout<<"Use setAlgo(value) to set MC algo."<<endl;
	return false;
  }else{ 
	return false;
  }
}

bool BJets::isbtagged( const unsigned int index )
{
  if( index < isbjet.size() ){
  return isbjet.at(index);
  }else{ 
	cout<<"Jet index out of range in function isbtagged."<<endl;
	return false;
  }
}

vector <LorentzVector> BJets::getbjets()
{
  return bjets;
}

//returns mlb
vector <float> BJets::getMlb( const vector <LorentzVector> &leps )
{
  vector <float> mlb;
  mlb.push_back(( leps.at(0) + bjets.at(0) ).mass());
  mlb.push_back(( leps.at(1) + bjets.at(0) ).mass());
  mlb.push_back(( leps.at(0) + bjets.at(1) ).mass());
  mlb.push_back(( leps.at(1) + bjets.at(1) ).mass());
  return mlb;
}

//sorts mlb with lowest lowest mass and it's event partner
vector <float> BJets::smartSortMlb( const vector <float> &mlb_unsorted )
{
  vector <Float_t> mlb;
  vector <Float_t> mlb1;
  vector <Float_t> mlb2;
  mlb1.push_back(mlb_unsorted.at(0));
  mlb2.push_back(mlb_unsorted.at(1));
  mlb1.push_back(mlb_unsorted.at(2));
  mlb2.push_back(mlb_unsorted.at(3));
  sort(mlb1.begin(), mlb1.end());
  sort(mlb2.begin(), mlb2.end());
  if( mlb1.at(0) < mlb2.at(0) ){
	mlb.push_back( mlb1.at(0) );
	mlb.push_back( mlb1.at(1) );
	mlb.push_back( mlb2.at(0) );
	mlb.push_back( mlb2.at(1) );
  }else if( mlb1.at(0) > mlb2.at(0) ){
	mlb.push_back( mlb2.at(0) );
	mlb.push_back( mlb2.at(1) );
	mlb.push_back( mlb1.at(0) );
	mlb.push_back( mlb1.at(1) );
  }
  return mlb;
}

float BJets::getminMlb( const vector <LorentzVector> &leps )
{
  vector <float> mlb;
  mlb.push_back(( leps.at(0) + bjets.at(0) ).mass());
  mlb.push_back(( leps.at(1) + bjets.at(0) ).mass());
  mlb.push_back(( leps.at(0) + bjets.at(1) ).mass());
  mlb.push_back(( leps.at(1) + bjets.at(1) ).mass());
  sort(mlb.begin(), mlb.end());
  return mlb.at(0);
}

float BJets::getMbb()
{
  if( bjets.size() > 1 ){
	return ( bjets.at(0) + bjets.at(1) ).mass();
  }else{ return -999;}
}

float BJets::getMT2b( const float met, const float metphi, const vector <LorentzVector> &leps )
{
  float mT2b1 = 0;
  float mT2b2 = 0;
  if( bjets.size() > 1 ){
  mT2b1 = MT2( met, metphi, leps.at(0) + bjets.at(0), leps.at(1) + bjets.at(1) );
  mT2b2 = MT2( met, metphi, leps.at(0) + bjets.at(1), leps.at(1) + bjets.at(0) );
  return min( mT2b1, mT2b2 );
  }else{ return -999;}
}

vector <float> BJets::getminpTlb()
{
  vector <float> ptlb;
  // ptlb.push_back(( zmet.lep1() + goodbs.at(0) ).mass());
  // ptlb.push_back(( zmet.lep2() + goodbs.at(0) ).mass());
  // ptlb.push_back(( zmet.lep1() + goodbs.at(1) ).mass());
  // ptlb.push_back(( zmet.lep2() + goodbs.at(1) ).mass());
  // sort(ptlb.begin(), ptlb.end());
  return ptlb;
}
