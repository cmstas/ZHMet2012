
bool makePhotonTemplates::getbjets( const Float_t workingpoint )
{

  bool twogoodjets = false;
  goodbs.clear();
  if(       templates.csv1() >= workingpoint && templates.csv2() >= workingpoint && templates.csv3() < workingpoint ){
	goodbs.push_back(templates.jet1());
	goodbs.push_back(templates.jet2());
	twogoodjets = true;
  }else if( templates.csv1() >= workingpoint && templates.csv3() >= workingpoint && templates.csv2() < workingpoint ){
	goodbs.push_back(templates.jet1());
	goodbs.push_back(templates.jet3());
	twogoodjets = true;
  }else if( templates.csv2() >= workingpoint && templates.csv3() >= workingpoint && templates.csv1() < workingpoint ){
	goodbs.push_back(templates.jet2());
	goodbs.push_back(templates.jet3());
	twogoodjets = true;
  }
  return twogoodjets;
}

bool makePhotonTemplates::getbjets( const Float_t workingpoint, const vector <Float_t> &csvvals )
{
  bool twogoodjets = false;
  goodbs.clear();
  if(       csvvals.at(0) >= workingpoint && csvvals.at(1) >= workingpoint && csvvals.at(2) < workingpoint ){
	goodbs.push_back(templates.jet1());
	goodbs.push_back(templates.jet2());
	twogoodjets = true;
  }else if( csvvals.at(0) >= workingpoint && csvvals.at(2) >= workingpoint && csvvals.at(1) < workingpoint ){
	goodbs.push_back(templates.jet1());
	goodbs.push_back(templates.jet3());
	twogoodjets = true;
  }else if( csvvals.at(1) >= workingpoint && csvvals.at(2) >= workingpoint && csvvals.at(0) < workingpoint ){
	goodbs.push_back(templates.jet2());
	goodbs.push_back(templates.jet3());
	twogoodjets = true;
  }
  return twogoodjets;
}
