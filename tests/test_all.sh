#declare -a arr=("genome -" "genome +" "genome ++" "intruder -" "intruder +" "intruder ++" "kmeans high" "kmeans high+" "kmeans high++" "kmeans low" "kmeans low+" "kmeans low++" "ssca2 -" "ssca2 +" "ssca2 ++" "vacation high" "vacation high+" "vacation high++" "vacation low" "vacation low+" "vacation low++" "yada -" "yada +" "yada ++")
#declare -a arr=("genome -" "genome +" "intruder -" "intruder +" "kmeans high" "kmeans high+" "kmeans low" "kmeans low+" "ssca2 -" "ssca2 +" "vacation high" "vacation high+" "vacation low" "vacation low+" "yada -" "yada +")
#declare -a arr=("intruder ++" "kmeans high" "kmeans low" "kmeans high+" "kmeans low+" "kmeans high++" "kmeans low++" "ssca2 ++" "vacation high" "vacation low" "vacation high+" "vacation low+" "vacation high++" "vacation low++" "yada ++")
#declare -a arr=("genome ++" "intruder ++" "kmeans high++" "kmeans low++" "ssca2 ++" "vacation high++" "vacation low++" "yada ++")
declare -a arr=("yada -")

for i in "${arr[@]}"
do
    benchmark="$(cut -d' ' -f1 <<<"$i")"
    opt="$(cut -d' ' -f2 <<<"$i")"
    echo $benchmark $opt
    ./test.sh $benchmark $opt
done
