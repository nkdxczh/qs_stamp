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
    queues=16
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
