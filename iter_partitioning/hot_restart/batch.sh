#! /bin/bash

# grep average * | sed -r 's/hr-([0-9][0-9]?-[0-1]-[0-1])\.log:average initials\s+([0-9]\.[0-9][0-9])\s+average finals:\s+([0-9]\.[0-9][0-9])/\1: \2 \3/g'

matrix_dir="../../matrices/"
results_dir="../../logs/hr_summary"
if [ ! -d $results_dir]; then
	mkdir $results_dir
fi
for matrix in $matrix_dir*
do
	matrix_name=$(basename "$matrix")
	matrix_name=${matrix_name%.*}
	output_dir="../../logs/hr/$matrix_name"
	echo $matrix_name
	if [ ! -d $output_dir ]; then
		mkdir $output_dir
	fi
	for i in {0..11}
	do
		for j in 0 1
		do
			for k in 0 1
			do
				echo -e "  $i $j $k"
				./hot_restart $matrix $i $j $k &> $output_dir/hr-$i-$j-$k.log
			done
		done
	done
	$(grep average ../../logs/hr/$matrix_name/* | sed -r 's/.*hr-([0-9][0-9]?-[0-1]-[0-1])\.log:average initials\s+([0-9]\.[0-9][0-9])\s+average finals:\s+([0-9]\.[0-9][0-9])/\1: \2 \3/g'>> $results_dir/$matrix_name.txt)


done
