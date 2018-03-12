# tries threads class command
echo $1 $2 $3 $4
bash build.sh $1 1 $2 3 kmeans $4
cd kmeans
./kmeans -m$3 -n$3 -t0.01 -p$2 -r1 -i inputs/random-n2048-d16-c16.txt
cd ..
