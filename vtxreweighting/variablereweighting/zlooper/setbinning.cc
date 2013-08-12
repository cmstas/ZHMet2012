#include <vector>
using namespace std;

vector <double> setptbins( double minPT = 0.0,  double maxPT = 0.0 )
{

  vector <double> binning;
  double binedge = minPT;
  while( abs(binedge - maxPT) > 0.1 ){
	binning.push_back(binedge);
	if( binedge < 92 ) binedge += 10.0;
	else if( binedge < 152 ) binedge += 25.0;
	else if( binedge < 252 ) binedge += 50.0;
	else if( binedge < 452 ) binedge += 100.0;
	else if( binedge < maxPT ) binedge += 200.0;
	if( binedge > maxPT ){ 
	  binning.push_back(maxPT);
	  binning.push_back(maxPT+200);
	  break;
	}
  }

  return binning;
}

vector <double> sethtbins( double minHT = 0.0,  double maxHT = 0.0 )
{

  vector <double> htbinning;
  htbinning.push_back(60.0);
  double htbinedge = minHT;
  while( abs(htbinedge - maxHT) > 0.1 ){
  	htbinning.push_back(htbinedge);
  	if( htbinedge < 150 ) htbinedge += 30.0;
  	else if( htbinedge < 250 ) htbinedge += 60.0;
  	else if( htbinedge < 350 ) htbinedge += 90.0;
  	else if( htbinedge < maxHT ) htbinedge += 120.0;
	if( htbinedge > maxHT ){
	  htbinning.push_back(maxHT);
	  htbinning.push_back(maxHT+120);
	  break;
	}
  }

  return htbinning;
}

vector <double> setmjjbins( double minMJJ = 0.0, double maxMJJ = 0.0 )
{

  vector <double> mjjbinning;
  mjjbinning.push_back(0.0);
  mjjbinning.push_back(20.0);
  double mjjbinedge = minMJJ;
  while( abs(mjjbinedge - maxMJJ) > 0.1 ){
	// cout<<mjjbinedge<<endl;
  	mjjbinning.push_back(mjjbinedge);
  	if( mjjbinedge < 150 ) mjjbinedge += 15.0;
  	else if( mjjbinedge < 250 ) mjjbinedge += 25.0;
  	else if( mjjbinedge < 350 ) mjjbinedge += 50.0;
  	else if( mjjbinedge < 550 ) mjjbinedge += 100.0;
  	else if( mjjbinedge < maxMJJ ) mjjbinedge += 50.0;
	if( mjjbinedge > maxMJJ ){
	  mjjbinning.push_back(maxMJJ);
	  mjjbinning.push_back(maxMJJ+100);
	  break;
	}
  }
  return mjjbinning;
}
