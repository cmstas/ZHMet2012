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
	echo "log/${versionnumber} Already exists! Output located in log/${versionnumber}/$dataset.txt"
fi

if [ "$didMakeDir" == "0" ]; then
	echo "log/${versionnumber} created successfully.Output located in log/${versionnumber}/$dataset.txt"
fi

echo "Processing root -b -q \"doAllZ.C (\"$dataset\", \"$percentage\", $isdata)\""
root -b -q "runZLooper.cc (\"$dataset\", \"$percentage\", $isdata)" > log/${versionnumber}/${dataset}.txt 2>&1 &
sleep 5
}
