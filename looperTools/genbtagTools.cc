#include <vector>
#include <cmath>
#include <iostream>
#include <genbtagTools.h>

using namespace std;

// genbjets::genbjets()
// {
// };

bool hasnogenbjets( const vector <float> &mcfavals )
{
  return ( abs(mcfavals.at(0)) != 5 && abs(mcfavals.at(1)) != 5 && abs(mcfavals.at(2)) != 5 );
}

bool hasonegenbjets( const vector <float> &mcfavals )
{
  return ( (    abs(mcfavals.at(0)) == 5 && abs(mcfavals.at(1)) != 5 && abs(mcfavals.at(2)) != 5 )
		   || ( abs(mcfavals.at(0)) != 5 && abs(mcfavals.at(1)) == 5 && abs(mcfavals.at(2)) != 5 )
		   || ( abs(mcfavals.at(0)) != 5 && abs(mcfavals.at(1)) != 5 && abs(mcfavals.at(2)) == 5 ) );  
}

bool hastwogenbjets( const float workingpoint, const vector <float> &csvvals, const vector <float> &mcfavals )
{
  if( csvvals.size() < 3 || mcfavals.size() < 3 ){
	cout<<"Warning, input vector too small. returning false"<<endl;
	return false;
  }

  bool twogoodjets = false;
  if(       csvvals.at(0) >= workingpoint && csvvals.at(1) >= workingpoint && csvvals.at(2) < workingpoint ){
	if( abs(mcfavals.at(0)) == 5 && abs(mcfavals.at(1)) == 5 && abs(mcfavals.at(2)) != 5 ){
	  twogoodjets = true;
	}
  }else if( csvvals.at(0) >= workingpoint && csvvals.at(2) >= workingpoint && csvvals.at(1) < workingpoint ){
	if( abs(mcfavals.at(0)) == 5 && abs(mcfavals.at(2)) == 5 && abs(mcfavals.at(1)) != 5 ){
	  twogoodjets = true;
	}
  }else if( csvvals.at(1) >= workingpoint && csvvals.at(2) >= workingpoint && csvvals.at(0) < workingpoint ){
	if( abs(mcfavals.at(1)) == 5 && abs(mcfavals.at(2)) == 5 && abs(mcfavals.at(0)) != 5 ){
	  twogoodjets = true;
	}
  }
  return twogoodjets;
}
