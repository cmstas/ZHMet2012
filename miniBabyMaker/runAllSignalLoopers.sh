#! /bin/bash

function run_looper
{

mt2jcut=$1
SELECTION=$2
root -b -q "runMainTemplateLooper.C( $mt2jcut, \"$SELECTION\" )"

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
run_looper 200 $selection &

selection="_inclusive_edge_3jinc"
run_looper 200 $selection &
selection="_inclusive_edge_4jinc"
run_looper 200 $selection &
