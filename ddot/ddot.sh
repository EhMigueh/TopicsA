#!/bin/bash
i=0
vals[0]=1

while [ $i -lt 4 ]
do
   valtmp=${vals[$(($i))]}
   newval=$(echo "$valtmp * 2" | bc)
   i=$(($i + 1))
   vals[$i]=$newval
done
unset LC_ALL
export LC_NUMERIC=C
echo "" > ddot.dat
for val in "${vals[@]}"
do
   echo "" > ddot_aux_1.dat
   export OMP_NUM_THREADS="${val}"
   for i in {1..7}
   do
      ./ddot "${vals}" 268435456 1 off | awk $info '/^Data/ { print "'${val}'" " " $3}' >> ddot_aux_1.dat
      echo "${val} ${i} test finished"
   done
   cat ddot_aux_1.dat | awk $info '{n = $1; sum += $2}; END{print n, sum/7}' >> ddot.dat
done
cat ddot.dat | awk '$0 != "" {print $0}'
gnuplot < ddot.p