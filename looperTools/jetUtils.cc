#include <vector>
#include <algorithm>
#include <stdexcept>

#include "jetUtils.h"

#include "../CORE/MT2/MT2.h"

using namespace std;


vector <LorentzVector> get_bjets( const vector <LorentzVector> &jets, const vector <float> &csvvals, const float workingpoint )
{
  vector <LorentzVector> bjets;
  for( size_t jetind = 0; jetind < jets.size(); jetind++ ){
	if( csvvals.at(jetind) > workingpoint ) bjets.push_back( jets.at(jetind) );
  }

  return bjets;
}

float getMT2bInc( const vector <LorentzVector> &leps, const vector <LorentzVector> &bjets, const float met, const float metphi )
{

  if( bjets.size() >= 2 ){		  
	vector <float> mT2b;
	for( size_t jetind = 0; jetind < bjets.size() - 1; jetind++ ){
	  mT2b.push_back( MT2( met, metphi, leps.at(0) + bjets.at(jetind),   leps.at(1) + bjets.at(jetind+1) ) );
	  mT2b.push_back( MT2( met, metphi, leps.at(0) + bjets.at(jetind+1), leps.at(1) + bjets.at(jetind)   ) );
	}
	  
	return *min_element(mT2b.begin(), mT2b.end());	  
  }else{
	return 0.0;
  }
}

float getMbb_2jets( const vector <LorentzVector> &bjets )
{
  if( bjets.size() == 2 ){		  
	return (bjets.at(0) + bjets.at(1)).mass();	  
  }else{
	return 0.0;
  }
}

bool sortByCSVValues (const std::pair <float, int> &csv1, const std::pair<float, int> &csv2)
{
  return csv1.first > csv2.first;
}

float getMbb_multijets( const vector <LorentzVector> &jets, const vector <float> &csvvals, const float workingpoint )
{

  if( jets.size() >= 2 ){		  
	vector < pair <float, int> > sortedCSVValues;

	//sort by csv value
	for( size_t csvind = 0; csvind < csvvals.size(); csvind++ ){
	  pair <float, int> csvpair = make_pair( csvvals.at(csvind), static_cast<int>(csvind) ); 
	  sortedCSVValues.push_back( csvpair );
	}
	sort( sortedCSVValues.begin(), sortedCSVValues.end(), sortByCSVValues );

	if ( sortedCSVValues.at(0).first > workingpoint && sortedCSVValues.at(1).first > workingpoint ){
	  LorentzVector bjet1 = jets.at( sortedCSVValues.at(0).second );
	  LorentzVector bjet2 = jets.at( sortedCSVValues.at(1).second );
	  return ( bjet1 + bjet2 ).mass();
	}else{
	  return 0.0;
	}
	  
  }else{
	return 0.0;
  }
}
