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
echo "" > mmc.dat
for val in "${vals[@]}"
do
   echo "" > mmc_aux_1.dat
   export OMP_NUM_THREADS="${val}"
   for i in {1..7}
   do
      ./mmc "${vals}" 34816 34816 1 off | awk $info '/^Data/ { print "'${val}'" " " $3}' >> mmc_aux_1.dat
      echo "${val} ${i} test finished"
   done
   cat mmc_aux_1.dat | awk $info '{n = $1; sum += $2}; END{print n, sum/7}' >> mmc.dat
done
cat mmc.dat | awk '$0 != "" {print $0}'
gnuplot < mmc.p