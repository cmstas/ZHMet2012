#! /bin/bash

root -b -q "runMakePhotonBabies.C+ (\"Pt-15to30\",false)" > Pt15-30.log 2>&1 
sleep 5
root -b -q "runMakePhotonBabies.C+ (\"Pt-30to50\",false)" > Pt30-50.log 2>&1 
sleep 5
root -b -q "runMakePhotonBabies.C+ (\"Pt-50to80\",false)" > Pt50-80.log 2>&1 
sleep 5
root -b -q "runMakePhotonBabies.C+ (\"Pt-80to120\",false)" > Pt80-120.log 2>&1 
sleep 5
root -b -q "runMakePhotonBabies.C+ (\"Pt-120to170\",false)" > Pt120-170.log 2>&1 
sleep 5
root -b -q "runMakePhotonBabies.C+ (\"Pt-170to300\",false)" > Pt170-300.log 2>&1 
sleep 5
root -b -q "runMakePhotonBabies.C+ (\"Pt-300to470\",false)" > Pt300-470.log 2>&1
sleep 5
root -b -q "runMakePhotonBabies.C+ (\"Pt-470to800\",false)" > Pt470-800.log 2>&1 
sleep 5
root -b -q "runMakePhotonBabies.C+ (\"Pt-800to1400\",false)" > Pt800-1400.log 2>&1 
