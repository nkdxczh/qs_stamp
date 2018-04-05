tries=1
threads=1
queues=1
repeats=3
benchmark=$1
opt=$2

path=data/$benchmark$opt/

rm -r $path
mkdir $path

cd ..
for v in 1 2 3 4
do
    echo $v
    echo "~~~~" >> "tests/"$path"qs_output"
    echo $v >> "tests/"$path"qs_output"
    echo "~~~~" >> "tests/"$path"rtm_output"
    echo $v >> "tests/"$path"rtm_output"
    threads=$v
    #echo ./run.sh $tries $threads $clusters \"-DUSE_QS\" $queues
    #./run.sh $tries $threads \"-DUSE_QS\" $queues $repeat $benchmark $opt >> tests/data/output
    #./run.sh $tries $threads \"-DUSE_RTM\" 0 $repeat $benchmark $opt>> tests/data/old_output
    ./run.sh $tries $threads \"-DUSE_QS\" $queues $repeats $benchmark $opt >> "tests/"$path"qs_output"
    ./run.sh $tries $threads \"-DUSE_RTM\" 0 $repeats $benchmark $opt >> "tests/"$path"rtm_output"
done
cd tests
