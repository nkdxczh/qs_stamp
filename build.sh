#!/bin/sh
rm lib/*.o || true

benchmark=$5

macros=$6

processors=$(grep -c ^processor /proc/cpuinfo)
cores=10


if [[ $processors == 8 ]] ;  then
    cores=4;
fi
if [[ $processors == 16 ]] ;  then
    cores=8;
fi
if [[ $processors == 56 ]] ;  then
    cores=14;
fi
if [[ $processors == 80 ]] ;  then
    cores=10;
fi


for F in $benchmark
do
    cd $F
    rm *.o || true
    rm $F

    if [[ 1 ]]
    then
        make -f Makefile CPU_LOCKS="-DCPU_LOCKS=$cores" HTM_RETRIES="-DHTM_RETRIES=$1" TOTAL_ATTEMPTS="-DTOTAL_ATTEMPTS=$1" APRIORI_LOCK_ATTEMPTS="-DAPRIORI_LOCK_ATTEMPTS=$2" NUMBER_THREADS="-DNUMBER_THREADS=$3" NUMBER_ATOMIC_BLOCKS="-DNUMBER_ATOMIC_BLOCKS=$4" MACROS="$macros -Dnum_q=$7"
    fi
    c='if [[ $7 == 0 ]]
    then
        make -f Makefile CPU_LOCKS="-DCPU_LOCKS=$cores" HTM_RETRIES="-DHTM_RETRIES=$1" TOTAL_ATTEMPTS="-DTOTAL_ATTEMPTS=$1" APRIORI_LOCK_ATTEMPTS="-DAPRIORI_LOCK_ATTEMPTS=$2" NUMBER_THREADS="-DNUMBER_THREADS=$3" NUMBER_ATOMIC_BLOCKS="-DNUMBER_ATOMIC_BLOCKS=$4" MACROS="$macros"
    fi'

    rc=$?
    if [[ $rc != 0 ]] ; then
	echo ""
        echo "=================================== ERROR BUILDING $F - $name ===================================="
	echo ""
        exit 1
    fi
    cd ..
done
