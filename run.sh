tries=$1
threads=$2
macro=$3
queues=$4
repeats=$5
benchmark=$6
opt=$7

#bash build.sh $tries 1 $threads 3 $benchmark $macro $queues

for i in {1..10}
do

cd $benchmark

if [[ "$benchmark" -eq "genome" ]];
then
    if [[ "$opt" = "-" ]];
    then
        ./genome -g256 -s16 -n16384 -t$threads
    fi
    if [[ "$opt" = "+" ]];
    then
        ./genome -g512 -s32 -n32768 -t$threads
    fi
    if [[ "$opt" = "++" ]];
    then
        ./genome -g16384 -s64 -n16777216 -t$threads
    fi
fi

if [[ "$benchmark" -eq "intruder" ]];
then
    if [[ "$opt" = "-" ]];
    then
        ./intruder -a10 -l4 -n2048 -s1 -t$threads
    fi
    if [[ "$opt" = "+" ]];
    then
        ./intruder -a10 -l16 -n4096 -s1 -t$threads
    fi
    if [[ "$opt" = "++" ]];
    then
        ./intruder -a10 -l128 -n262144 -s1 -t$threads
    fi
fi

if [[ "$benchmark" -eq "kmeans" ]];
then
    if [[ "$opt" = "high" ]];
    then
        ./kmeans -m15 -n15 -t0.05 -i inputs/random-n2048-d16-c16.txt -p$threads -r1
    fi
    if [[ "$opt" = "high+" ]];
    then
        ./kmeans -m15 -n15 -t0.05 -i inputs/random-n16384-d24-c16.txt -p$threads -r1
    fi
    if [[ "$opt" = "high++" ]];
    then
        ./kmeans -m15 -n15 -t0.00001 -i inputs/random-n65536-d32-c16.txt -p$threads -r1
    fi
    if [[ "$opt" = "low" ]];
    then
        ./kmeans -m40 -n40 -t0.05 -i inputs/random-n2048-d16-c16.txt -p$threads -r1
    fi
    if [[ "$opt" = "low+" ]];
    then
        ./kmeans -m40 -n40 -t0.05 -i inputs/random-n16384-d24-c16.txt -p$threads -r1
    fi
    if [[ "$opt" = "low++" ]];
    then
        ./kmeans -m40 -n40 -t0.00001 -i inputs/random-n65536-d32-c16.txt -p$threads -r1
    fi
fi

if [[ "$benchmark" -eq "ssca2" ]];
then
    if [[ "$opt" = "-" ]];
    then
        ./ssca2 -s13 -i1.0 -u1.0 -l3 -p3 -t$threads
    fi
    if [[ "$opt" = "+" ]];
    then
        ./ssca2 -s14 -i1.0 -u1.0 -l9 -p9 -t$threads
    fi
    if [[ "$opt" = "++" ]];
    then
        ./ssca2 -s20 -i1.0 -u1.0 -l3 -p3 -t$threads
    fi
fi

if [[ "$benchmark" -eq "vacation" ]];
then
    if [[ "$opt" = "high" ]];
    then
        ./vacation -n4 -q60 -u90 -r16384 -t4096 -c$threads
    fi
    if [[ "$opt" = "high+" ]];
    then
        ./vacation -n4 -q60 -u90 -r1048576 -t4096 -c$threads
    fi
    if [[ "$opt" = "high++" ]];
    then
        ./vacation -n4 -q60 -u90 -r1048576 -t4194304 -c$threads
    fi
    if [[ "$opt" = "low" ]];
    then
        ./vacation  -n2 -q90 -u98 -r16384 -t4096 -c$threads
    fi
    if [[ "$opt" = "low+" ]];
    then
        ./vacation -n2 -q90 -u98 -r1048576 -t4096 -c$threads
    fi
    if [[ "$opt" = "low++" ]];
    then
        ./vacation  -n2 -q90 -u98 -r1048576 -t4194304 -c$threads
    fi
fi

if [[ "$benchmark" -eq "yada" ]];
then
    if [[ "$opt" = "-" ]];
    then
        ./yada -a20 -i inputs/633.2 -t$threads
    fi
    if [[ "$opt" = "+" ]];
    then
        ./yada -a10 -i inputs/ttimeu10000.2 -t$threads
    fi
    if [[ "$opt" = "++" ]];
    then
        ./yada -a15 -i inputs/ttimeu1000000.2 -t$threads
    fi
fi

cd ..

done
