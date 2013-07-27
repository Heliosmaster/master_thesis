#! /bin/bash

matrix="../../matrices/$1"
matrix_name=${1%.*}
output_dir="../../logs/hr/$matrix_name"
if [ ! -d $output_dir ]; then
	mkdir $output_dir
fi
echo $matrix
for i in {1..11}
	do
		for j in 0 1
		do
			for k in 0 1
			do
				echo "Doing $i $j $k"
				./hot_restart $matrix $i $j $k &> $output_dir/hr-$i-$j-$k.log
			done
		done
#	./hot_restart $
done
