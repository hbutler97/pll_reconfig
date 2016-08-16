#!/bin/sh

insmod /pll_reconfig/pll_reconfig/driver/dynamic_clock.ko
#for i in `seq 1000 400000`      
#do
#    ./alt_pll_reconfig -f cyclonev -s 6 -i 50000 -o $i |tee -a out.txt
#done

#a=1000
#while [ "$a" -lt 400000 ]
#do
 #   ./alt_pll_reconfig -f cyclonev -s 6 -i 50000 -o $a |tee -a out.txt
 #   a=`expr $a + 100`
#done



for i in `seq 1 5000`      
do

    a=$(shuf -i 1000-400000 -n 1)
   ./alt_pll_reconfig -f cyclonev -s 6 -i 50000 -o $a |tee -a out.txt
done
