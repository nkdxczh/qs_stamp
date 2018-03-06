echo $1 $2 $3 $4
bash build.sh $1 1 $2 3 kmeans $4
cd kmeans
./kmeans -m$3 -n$3 -t0.0001 -p$2 -i inputs/random-n131072-d32-c16.txt -r 1
cd ..
