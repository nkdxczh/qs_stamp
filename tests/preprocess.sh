#!/bin/bash
op=0
x=0

time='time'
tx='tx'
conflict='conflict'

echo "" > $time
echo "" > $tx
echo "" > $conflict

alltx=0

while IFS='' read -r line || [[ -n "$line" ]]; 
do
    if [[ ${line:0:1} == [0-9]* ]] ;
    then 
        #echo $line 

        if [[ $op == 0 ]];
        then
            x=$line;
            ((op++));
        elif [[ $op == 1 ]];
        then
            echo $x $line >> $time
            ((op++));
        elif [[ $op == 2 ]];
        then
            echo $x $line >> $tx
            ((op++));
        elif [[ $op == 3 ]];
        then
            echo $x $line >> $conflict
            op=0;
        fi
    fi
done < 'output'

time='old_time'
tx='old_tx'
conflict='old_conflict'

echo "" > $time
echo "" > $tx
echo "" > $conflict

alltx=0

while IFS='' read -r line || [[ -n "$line" ]]; 
do
    if [[ ${line:0:1} == [0-9]* ]] ;
    then 
        #echo $line 

        if [[ $op == 0 ]];
        then
            x=$line;
            ((op++));
        elif [[ $op == 1 ]];
        then
            echo $x $line >> $time
            ((op++));
        elif [[ $op == 2 ]];
        then
            echo $x $line >> $tx
            ((op++));
        elif [[ $op == 3 ]];
        then
            echo $x $line >> $conflict
            op=0;
        fi
    fi
done < 'old_output'
