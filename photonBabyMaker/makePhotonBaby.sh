function processsample
{
dataset=$1
isdata=$2
versionnumber=$3
percentage=$4

if [ ! -d log/${versionnumber} ]; then
	echo "log/${versionnumber} does not exist. Attempting to create."
	mkdir -p log/${versionnumber}
	didMakeDir=$?
else
	echo "log/${versionnumber} Already exists! Output located in log/${versionnumber}/$dataset_${percentage}.txt"
fi
if [ "$didMakeDir" == "0" ]; then
	echo "log/${versionnumber} created successfully.Output located in log/${versionnumber}/$dataset_${percentage}.txt"
fi

if [ ! -d ../photon_output/${versionnumber} ]; then
	echo "../photon_output/${versionnumber} does not exist. Attempting to create."
	mkdir -p ../photon_output/${versionnumber}
	didMakeDir=$?
else
	echo "../photon_output/${versionnumber} Already exists! Output located in ../photon_output/${versionnumber}/$dataset_${percentage}.root"
fi
if [ "$didMakeDir" == "0" ]; then
	echo "../photon_output/${versionnumber} created successfully.Output located in ../photon_output/${versionnumber}/$dataset_${percentage}.root"
fi

echo "Processing root -b -q \"runZlooper.cc (\"$dataset\", \"$percentage\", $isdata, \"$versionnumber\")\""
root -b -q "runMakePhotonBabies.cc (\"$dataset\", \"$percentage\", $isdata, \"$versionnumber\" )" > log/${versionnumber}/${dataset}_${percentage}.txt 2>&1 &
# sleep 5
}
