#! /bin/bash

function make_zhists
{
	ismc=$1
	selection_region=$2

	cd zlooper
	echo "running zhist_looper."
	root -b -q "run_zhist_looper.cc(0.0, \"$selection_region\", $ismc )"
	cd -
}

function make_ghists
{
	ismc=$1
	selection_region=$2
	echo "running vtxLooper."
	root -b -q "makeAllvtxHistos.cc($ismc, \"$selection_region\")"
}

function make_all_hists
{

ISMC=$1
SELECTION=$2

make_zhists $ISMC $SELECTION 
make_ghists $ISMC $SELECTION

}

# compile zlooper
echo "Compiling zlooper."
cd zlooper
make -j5
if [ ! "$?" -eq "0" ]; then
	echo "zlooper did not compile, exiting."
	exit
fi
cd -

# compile vtxLooper
echo "Compiling vtxLooper."
make -j5
if [ ! "$?" -eq "0" ]; then
	echo "vtxLooper did not compile, exiting."
	exit
fi

# ismc=true
ismc=false

# root -b -q "makeZhists.cc+($ismc)"
# root -b -q "makeAllvtxHistos.cc($ismc)"

# selection="_bveto_mjjhi_mt2jhi"
# make_all_hists $ismc $selection &

# selection="_bveto_mjjhi_mt2jlo"
# make_all_hists $ismc $selection &

# selection="_bveto_mjjlo_mt2jlo"
# make_all_hists $ismc $selection &

# selection="_bveto_mjjlo_mt2jhi"
# make_all_hists $ismc $selection &

selection="_2btag_mjjhi_mt2jhi"
make_all_hists $ismc $selection &

# selection="_2btag_mjjhi_mt2jlo"
# make_all_hists $ismc $selection &

# selection="_2btag_mjjlo_mt2jhi"
# make_all_hists $ismc $selection &

# selection="_2btag_mjjlo_mt2jlo"
# make_all_hists $ismc $selection &

# selection="_2btag_mt2jlo"
# make_all_hists $ismc $selection &

# selection="_2btag_mt2jhi"
# make_all_hists $ismc $selection &

# selection="_bveto_mt2jlo"
# make_all_hists $ismc $selection &

# selection="_bveto_mt2jhi"
# make_all_hists $ismc $selection &

# selection="_bveto"
# make_all_hists $ismc $selection &
# # make_ghists $ismc $selection &

# selection="_2btag"
# make_all_hists $ismc $selection &
# # make_ghists $ismc $selection &

# selection="_2btag_0genbs"
# make_all_hists $ismc $selection &
# selection="_2btag_1genbs"
# make_all_hists $ismc $selection &
# selection="_2btag_2genbs"
# make_all_hists $ismc $selection &

# selection=""
# make_all_hists $ismc $selection &
# make_zhists $ismc $selection
# make_ghists $ismc $selection
