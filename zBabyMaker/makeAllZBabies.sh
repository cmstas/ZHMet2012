#! /bin/bash

. makeZBaby.sh

versionnumber="V00-02-23"

make -j5
if [ ! "$?" -eq "0" ]; then
	echo "Did not Compile, Exiting"
	exit
fi

# processsample edge_sync_newvars false $versionnumber

# processsample data_53X_2012A_recover_06Aug2012 true $versionnumber

processsample data_53X_2012D_16Jan2013 true $versionnumber &
processsample data_53X_2012D true $versionnumber &
processsample data_53X_2012C_24Aug2012 true $versionnumber &
processsample data_53X_2012C true $versionnumber &

# processsample zjetsmc_ee false $versionnumber
# processsample zjetsmc_mm false $versionnumber

# processsample z1jet_53X_slim_ false $versionnumber
# processsample z2jet_53X_slim_ false $versionnumber
# processsample z3jet_53X_slim_ false $versionnumber
# processsample z4jet_53X_slim_ false $versionnumber

# processsample zjets_53X_slim false $versionnumber

# processsample data_53X_2012A true $versionnumber
# processsample data_53X_2012B true $versionnumber
# processsample data_53X_2012C_ecalreco true $versionnumber
# processsample data_53X_2012C true $versionnumber
# processsample data_53X_2012D true $versionnumber

# processsample t_53X_slim false $versionnumber

# processsample ttbar_mgdl_53X_slim false $versionnumber
# processsample ttbar_mgsl_53X_slim false $versionnumber
# processsample ttbar_mghad_53X_slim false $versionnumber

# processsample TChizh_53X_150_1 false $versionnumber
# processsample TChizh_53X_200_1 false $versionnumber
# processsample TChizh_53X_250_1 false $versionnumber

# processsample TChizh_53X_scan false $versionnumber

# processsample zhsm_53X_slim false $versionnumber

# processsample zz2l2nu_53X_slim false $versionnumber
# processsample zz2l2q_53X_slim false $versionnumber
# processsample zz4l_53X_slim false $versionnumber

# processsample wz2l2q_53X_slim false $versionnumber
# processsample wz3lnu_53X_slim false $versionnumber

# processsample ww_53X_slim false $versionnumber

# processsample ttz_53X_slim false $versionnumber
# processsample ttw_53X_slim false $versionnumber
# processsample ttg_53X_slim false $versionnumber
# processsample ttww_53X_slim false $versionnumber
# processsample tbz_53X_slim false $versionnumber

# processsample vvv_53X_slim false $versionnumber

# processsample zbb2l_53X_slim false $versionnumber

