#! /bin/bash

. makePhotonBaby.sh

versionnumber="V00-02-21"

make -j5
if [ ! "$?" -eq "0" ]; then
	echo "Did not Compile, Exiting"
	exit
fi

# processsample zjetsmc_ee false $versionnumber
# processsample zjetsmc_mm false $versionnumber

# processsample photon_mght40 false $versionnumber "1*" &
# processsample photon_mght40 false $versionnumber "2*" &
# processsample photon_mght40 false $versionnumber "3*" &
# processsample photon_mght40 false $versionnumber "4*" &
# processsample photon_mght40 false $versionnumber "5*" &
# processsample photon_mght40 false $versionnumber "6*" &
# processsample photon_mght40 false $versionnumber "7*" &
# processsample photon_mght40 false $versionnumber "8*" &
# processsample photon_mght40 false $versionnumber "9*" &

processsample photon_tchizh_250_1 false $versionnumber &
processsample photon_tchizh_200_1 false $versionnumber &
processsample photon_tchizh_150_1 false $versionnumber &
processsample photon_tchizh_130_1 false $versionnumber &

# processsample photon_15 false $versionnumber 1
# processsample photon_15 false $versionnumber 2
# processsample photon_30 false $versionnumber
# processsample photon_50 false $versionnumber
# processsample photon_80 false $versionnumber
# processsample photon_120 false $versionnumber
# processsample photon_170 false $versionnumber
# processsample photon_300 false $versionnumber
# processsample photon_470 false $versionnumber
# processsample photon_800 false $versionnumber
# processsample photon_1400 false $versionnumber

