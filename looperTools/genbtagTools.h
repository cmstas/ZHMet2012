#ifndef GENBTAGTOOLS_H
#define GENBTAGTOOLS_H

#include <vector>

bool hasnogenbjets( const std::vector <float> &mcfavals );
bool hasonegenbjets( const std::vector <float> &mcfavals );
bool hastwogenbjets( const float workingpoint, const std::vector <float> &csvvals, const std::vector <float> &mcfavals );


#endif
