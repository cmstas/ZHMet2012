#! /bin/bash

function run_looper
{

DATASET=$1
SELECTION=$2
root -b -q "runMainTemplateLooper.C( \"$DATASET\", \"$SELECTION\" )"

}

make -j5
if [ ! "$?" -eq "0" ]; then
	echo "Did not Compile, Exiting"
	exit
fi

# # For inclusive result
# selection="_inclusive"
# run_looper 200 $selection &

# For inclusive result + edge
selection="_inclusive_edge"

dataset="data"
run_looper $dataset $selection

# dataset="data2012A"
# run_looper $dataset $selection

# dataset="data2012B"
# run_looper $dataset $selection

# dataset="data2012C"
# run_looper $dataset $selection

# dataset="data2012D"
# run_looper $dataset $selection

# selection="_inclusive_edge_3jinc"
# run_looper 200 $selection &
# selection="_inclusive_edge_4jinc"
# run_looper 200 $selection &
