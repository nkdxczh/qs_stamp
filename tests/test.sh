tries=5
threads=64
clusters=15
queues=2

echo "" > output
echo "" > old_output

cd ..
for v in {5..64..2}
do
    echo $v
    echo $v >> tests/output
    echo $v >> tests/old_output
    queues=$v
    #echo ./run.sh $tries $threads $clusters \"-DUSE_QS\" $queues
    ./run.sh $tries $threads $clusters \"-DUSE_QS\" $queues >> tests/output
    ./run.sh $tries $threads $clusters "" >> tests/old_output
done
cd tests
