make sure all the directories are set. specifically:

../CORE/
../CORE/MT2/
../Tools/

The rest should be included with the repository.
../jetCorrections/
../looperTools/
../jsons/

Make sure the links in runZLooper.cc are set correctly.

In order to run a sample, comment the datasets you want to run in makeAllZBabies.sh, e.g. 

processsample TChizh_53X_150_1 false $versionnumber

then run the submission script as follows
 
./makeAllZBabies.sh

Warning: I've only run 5ish jobs per uaf at a time using this method. Additionally, I stored the output on a simlink to nfs-[]/userdata/cwelke/output/.

EXTRA:
If you want to break the job up a bit, rather than use the command

processsample zjets_53X_slim false

You can set a value of files to run on with

# processsample zjets_53X_slim false 1

which then takes all the ntuples that match the criteria

merged_ntuple_1*.root

in order to have completeness, you would have to do this for 1-9.

