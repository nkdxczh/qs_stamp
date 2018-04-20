tries=5
threads=80
queues=120
repeats=1
benchmark=$1
opt=$2

path=data/$benchmark$opt/

rm -r $path
mkdir $path

if [[ "$benchmark" = "genome" ]];
then
    queues=88
fi
if [[ "$benchmark" = "intruder" ]];
then
    queues=40
fi
if [[ "$benchmark" = "kmeans" ]];
then
    queues=72
fi
if [[ "$benchmark" = "ssca2" ]];
then
    queues=98
fi
if [[ "$benchmark" = "vacation" ]];
then
    queues=120
fi

seer_mac="-DUSE_SEER-DUSE_TX_LOCKS-DUSE_CPU_LOCKS-DUSE_HTM_LOCKS-DUSE_GRADIENT_DESCENT"
cd ..

threads=8
queues=0
bash build.sh $tries 1 $threads 3 $benchmark "" $queues
bash build.sh $tries 1 $threads 3 $benchmark \"-DUSE_HLE\" $queues
bash build.sh $tries 1 $threads 3 $benchmark \"-DUSE_SCM\" $queues
bash build.sh $tries 1 $threads 3 $benchmark \"${seer_mac}\" $queues

for v in 1 2 3 4 5 6 7 8
do
    echo $v
    #echo "~~~~" >> "tests/"$path"qs_output"
    #echo $v >> "tests/"$path"qs_output"
    echo "~~~~" >> "tests/"$path"rtm_output"
    echo $v >> "tests/"$path"rtm_output"
    echo "~~~~" >> "tests/"$path"hle_output"
    echo $v >> "tests/"$path"hle_output"
    echo "~~~~" >> "tests/"$path"scm_output"
    echo $v >> "tests/"$path"scm_output"
    echo "~~~~" >> "tests/"$path"seer_output"
    echo $v >> "tests/"$path"seer_output"
    threads=$v
    #echo ./run.sh $tries $threads $clusters \"-DUSE_QS\" $queues
    #./run.sh $tries $threads \"-DUSE_QS\" $queues $repeats $benchmark $opt >> "tests/"$path"qs_output"
    #./run.sh $tries $threads \"\" 0 $repeats $benchmark $opt
    #./run.sh $tries $threads \"-DUSE_HLE\" 0 $repeats $benchmark $opt
    #./run.sh $tries $threads \"-DUSE_SCM\" 0 $repeats $benchmark $opt
    #./run.sh $tries $threads $seer_mac 0 $repeats $benchmark $opt
    ./run.sh $tries $threads \"\" 0 $repeats $benchmark $opt >> "tests/"$path"rtm_output"
    ./run.sh $tries $threads \"-DUSE_HLE\" 0 $repeats $benchmark $opt >> "tests/"$path"hle_output"
    ./run.sh $tries $threads \"-DUSE_SCM\" 0 $repeats $benchmark $opt >> "tests/"$path"scm_output"
    ./run.sh $tries $threads $seer_mac 0 $repeats $benchmark $opt >> "tests/"$path"seer_output"
done
cd tests
