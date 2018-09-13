tries=5
threads=80
queues=120
repeats=1
benchmark=$1
opt=$2

QS_MOD=6

path=data/$benchmark$opt/

rm -r $path
mkdir $path

if [[ "$benchmark" = "genome" ]];
then
<<<<<<< HEAD
    queues=88
    queues=2
    QS_MOD=1
=======
    queues=16
>>>>>>> c753563da6243f9d3b81b883ed4264b80f0ba0a1
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
    queues=64
fi
if [[ "$benchmark" = "vacation" ]];
then
    queues=64
fi
if [[ "$benchmark" = "yada" ]];
then
    queues=32
fi

seer_mac="-DUSE_SEER-DUSE_TX_LOCKS-DUSE_CPU_LOCKS-DUSE_HTM_LOCKS-DUSE_GRADIENT_DESCENT"
cd ..

<<<<<<< HEAD
threads=32
queues=1
bash build.sh $tries 1 $threads 3 $benchmark "-DUSE_QS -DQS_MOD=$QS_MOD" $queues
#bash build.sh $tries 1 $threads 3 $benchmark "" $queues
#bash build.sh $tries 1 $threads 3 $benchmark \"-DUSE_HLE\" $queues
#bash build.sh $tries 1 $threads 3 $benchmark \"-DUSE_SCM\" $queues
#bash build.sh $tries 1 $threads 3 $benchmark \"${seer_mac}\" $queues

for v in 1 2 3 4
do
    echo $v
    echo "~~~~" >> "tests/"$path"qs_output"
    echo $v >> "tests/"$path"qs_output"
    #echo "~~~~" >> "tests/"$path"rtm_output"
    #echo $v >> "tests/"$path"rtm_output"
    #echo "~~~~" >> "tests/"$path"hle_output"
    #echo $v >> "tests/"$path"hle_output"
    #echo "~~~~" >> "tests/"$path"scm_output"
    #echo $v >> "tests/"$path"scm_output"
    #echo "~~~~" >> "tests/"$path"seer_output"
    #echo $v >> "tests/"$path"seer_output"
    threads=$v
    #echo ./run.sh $tries $threads $clusters \"-DUSE_QS\" $queues
    ./run.sh $tries $threads \"-DUSE_QS\" $queues $repeats $benchmark $opt >> "tests/"$path"qs_output"
    #./run.sh $tries $threads \"\" 0 $repeats $benchmark $opt >> "tests/"$path"rtm_output"
    #./run.sh $tries $threads \"-DUSE_HLE\" 0 $repeats $benchmark $opt >> "tests/"$path"hle_output"
    #./run.sh $tries $threads \"-DUSE_SCM\" 0 $repeats $benchmark $opt >> "tests/"$path"scm_output"
    #./run.sh $tries $threads $seer_mac 0 $repeats $benchmark $opt >> "tests/"$path"seer_output"
=======
threads=64
bash build.sh $tries 1 $threads 3 $benchmark \"-DUSE_QS\" $queues

for v in 1 2 4 8 16 32 64
do
    echo $benchmark $v qs $queues
    echo "~~~~" >> "tests/"$path"qs_output"
    echo $v >> "tests/"$path"qs_output"
    threads=$v
    ./run.sh $tries $threads \"-DUSE_QS\" 0 $repeats $benchmark $opt >> "tests/"$path"qs_output"
done

c='threads=64

bash build.sh $tries 1 $threads 3 $benchmark "" $queues

for v in 1 2 4 8 16 32 64
do
    echo $benchmark $v rtm
    echo "~~~~" >> "tests/"$path"rtm_output"
    echo $v >> "tests/"$path"rtm_output"
    threads=$v
    ./run.sh $tries $threads \"\" 0 $repeats $benchmark $opt >> "tests/"$path"rtm_output"
done

threads=64
bash build.sh $tries 1 $threads 3 $benchmark \"-DUSE_HLE\" $queues

for v in 1 2 4 8 16 32 64
do
    echo $benchmark $v hle
    echo "~~~~" >> "tests/"$path"hle_output"
    echo $v >> "tests/"$path"hle_output"
    threads=$v
    ./run.sh $tries $threads \"-DUSE_HLE\" 0 $repeats $benchmark $opt >> "tests/"$path"hle_output"
done

threads=64
bash build.sh $tries 1 $threads 3 $benchmark \"-DUSE_SCM\" $queues

for v in 1 2 4 8 16 32 64
do
    echo $benchmark $v scm
    echo "~~~~" >> "tests/"$path"scm_output"
    echo $v >> "tests/"$path"scm_output"
    threads=$v
    ./run.sh $tries $threads \"-DUSE_SCM\" 0 $repeats $benchmark $opt >> "tests/"$path"scm_output"
>>>>>>> c753563da6243f9d3b81b883ed4264b80f0ba0a1
done

threads=64
bash build.sh $tries 1 $threads 3 $benchmark "-DUSE_SEER -DUSE_TX_LOCKS -DUSE_CPU_LOCKS -DUSE_HTM_LOCKS -DUSE_GRADIENT_DESCENT" $queues

for v in 1 2 4 8 16 32 64
do
    echo $benchmark $v seer
    echo "~~~~" >> "tests/"$path"seer_output"
    echo $v >> "tests/"$path"seer_output"
    threads=$v
    ./run.sh $tries $threads \"\" 0 $repeats $benchmark $opt >> "tests/"$path"seer_output"
done'

cd tests
