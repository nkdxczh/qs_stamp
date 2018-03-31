# tries threads class command
bash build.sh $1 1 $2 3 kmeans $4 $5
cd kmeans
./kmeans -m$3 -n$3 -t0.00001 -p$2 -r1 -i inputs/random-n65536-d32-c16.txt
cd ..
