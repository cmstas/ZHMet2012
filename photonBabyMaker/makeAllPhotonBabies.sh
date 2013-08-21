#! /bin/bash

. makePhotonBaby.sh

versionnumber="V00-02-21"

make -j5
if [ ! "$?" -eq "0" ]; then
	echo "Did not Compile, Exiting"
	exit
fi

# processsample zjetsmc_ee false
# processsample zjetsmc_mm false

processsample photon_15 false $versionnumber
# processsample photon_30 false
# processsample photon_50 false
# processsample photon_80 false
# processsample photon_120 false
# processsample photon_170 false
# processsample photon_300 false
# processsample photon_470 false
# processsample photon_800 false
# processsample photon_1400 false

# echo "Processing root -b -q \"doAll_makePhotonBabies.C (\"ttbar_flmc_53X\", false)\""
# echo "Output located in log/ttbar_flmc_53X.txt"
# root -b -q "doAll_makePhotonBabies.C (\"ttbar_flmc_53X\", false)" > log/ttbar_flmc_53X.txt 2>&1 &
# sleep 10

# echo "Processing root -b -q \"doAll_makePhotonBabies.C (\"ttbar_slmc_53X\", false)\""
# echo "Output located in log/ttbar_slmc_53X.txt"
# root -b -q "doAll_makePhotonBabies.C (\"ttbar_slmc_53X\", false)" > log/ttbar_slmc_53X.txt 2>&1 &
# sleep 10

# echo "Processing root -b -q \"doAll_makePhotonBabies.C (\"data_53X_2012D\", true)\""
# echo "Output located in log/data_53X_2012D.txt"
# root -b -q "doAll_makePhotonBabies.C (\"data_53X_2012D\", true)" > log/data_53X_2012D.txt 2>&1 &
# sleep 10

# echo "Processing root -b -q \"doAll_makePhotonBabies.C (\"data_53X_2012C\", true)\""
# echo "Output located in log/data_53X_2012C.txt"
# root -b -q "doAll_makePhotonBabies.C (\"data_53X_2012C\", true)" > log/data_53X_2012C.txt 2>&1 &
# sleep 10

# echo "Processing root -b -q \"doAll_makePhotonBabies.C (\"data_53X_2012B\", true)\""
# echo "Output located in log/data_53X_2012B.txt"
# root -b -q "doAll_makePhotonBabies.C (\"data_53X_2012B\", true)" > log/data_53X_2012B.txt 2>&1 &
# sleep 10

# echo "Processing root -b -q \"doAll_makePhotonBabies.C (\"data_53X_2012A\", true)\""
# echo "Output located in log/data_53X_2012A.txt"
# root -b -q "doAll_makePhotonBabies.C (\"data_53X_2012A\", true)" > log/data_53X_2012A.txt 2>&1 &

