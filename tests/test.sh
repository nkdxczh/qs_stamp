tries=5
threads=3
clusters=40
queues=2

echo "" > output

cd ..
for v in {1..3..1}
do
    echo $v
    echo $v >> tests/output
    queues=$v
    #echo ./run.sh $tries $threads $clusters \"-DUSE_QS\" $queues
    ./run.sh $tries $threads $clusters \"-DUSE_QS\" $queues >> tests/output
done
cd tests
