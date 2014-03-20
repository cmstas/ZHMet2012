#! /bin/bash

if [ ! "$CMSSW_BASE" == "" ]; then
# ln -s /home/users/cwelke/CMSSW/CMSSW_5_3_2_patch4/src/CMS2/NtupleMacros/CORE
	if [ -h "CORE" ]; then
		echo "CORE exists at $CMSSW_BASE/src/CMS2/NtupleMacros/CORE"
	else
		echo "Creating simlink to CORE from $CMSSW_BASE/src/CMS2/NtupleMacros/CORE"
		ln -s "$CMSSW_BASE/src/CMS2/NtupleMacros/CORE"
	fi

# ln -s /home/users/cwelke/CMSSW/CMSSW_5_3_2_patch4/src/CMS2/NtupleMacros/Tools
	if [ -h "Tools" ]; then
		echo "Tools exists at $CMSSW_BASE/src/CMS2/NtupleMacros/Tools"
	else
		echo "Creating simlink to Tools from $CMSSW_BASE/src/CMS2/NtupleMacros/Tools"
		ln -s "$CMSSW_BASE/src/CMS2/NtupleMacros/Tools"
	fi

else
	echo "Error: CMSSW path not set. Exiting."
	exit 1
fi

if [ ! -h "looperTools" ]; then
	echo "looperTools directory does not exist. Creating link to /home/users/cwelke/dev/cwelke/looperTools"
	ln -s /home/users/cwelke/dev/cwelke/looperTools
else
	echo "looperTools exists at /home/users/cwelke/dev/cwelke/looperTools"
fi

#setup your output directory where you will store ntuples
if [ ! -h "output" ]; then
	echo "output directory does not exist. Creating link to ../output"
	ln -s ../output
else
	echo "output exists at ../output"
fi

if [ ! -d "output/miniBabies" ]; then
	echo "Directory output/miniBabies does not exist. Creating now."
	mkdir output/miniBabies
	didMakeDir=$?

	if [ "$didMakeDir" -eq "0" ]; then
		echo "Directory output/miniBabies created successfully."
	else
		echo "Directory output/miniBabies not created successfully. Exiting."
		exit 2
	fi
else
	echo "Directory output/miniBabies already exists."
fi
