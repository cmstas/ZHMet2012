function processsample
{
dataset=$1
isdata=$2
percentage=$3

echo "Processing root -b -q \"doAllZ.C (\"$dataset\", \"$percentage\", $isdata)\""
echo "Output located in log/$dataset.txt"
root -b -q "doAllZ.C (\"$dataset\", \"$percentage\", $isdata)" > log/${dataset}.txt 2>&1 &
sleep 5
}
