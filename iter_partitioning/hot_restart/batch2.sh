#! /bin/bash

# grep average * | sed -r 's/hr-([0-9][0-9]?-[0-1]-[0-1])\.log:average initials\s+([0-9]\.[0-9][0-9])\s+average finals:\s+([0-9]\.[0-9][0-9])/\1: \2 \3/g'

matrix_dir="../../matrices_preliminary/"
results_dir="../../logs/hr_summary"
if [ ! -d $results_dir]; then
	mkdir $results_dir
fi
for matrix in $matrix_dir*
do
	matrix_name=$(basename "$matrix")
	matrix_name=${matrix_name%.*}
	output_dir="../../logs/hr/po/$matrix_name"
	echo $matrix_name
	if [ ! -d $output_dir ]; then
		mkdir $output_dir
	fi
	./hot_restart $matrix 6 0 0 &> $output_dir/hr-6-0-0.log
	./hot_restart $matrix 6 1 0 &> $output_dir/hr-6-1-0.log
	./hot_restart $matrix 8 0 0 &> $output_dir/hr-8-0-0.log
	./hot_restart $matrix 8 0 1 &> $output_dir/hr-8-0-1.log
	./hot_restart $matrix 8 1 0 &> $output_dir/hr-8-1-0.log

	output_dir="../../logs/hr/pa/$matrix_name"
	if [ ! -d $output_dir ]; then
		mkdir $output_dir
	fi

	./hot_restart $matrix 7 0 0 &> $output_dir/hr-7-0-0.log
	./hot_restart $matrix 7 1 0 &> $output_dir/hr-7-1-0.log
	./hot_restart $matrix 9 0 0 &> $output_dir/hr-9-0-0.log
	./hot_restart $matrix 9 0 1 &> $output_dir/hr-9-0-1.log
	./hot_restart $matrix 9 1 0 &> $output_dir/hr-9-1-0.log

#$(grep average ../../logs/hr/$matrix_name/* | sed -r 's/.*hr-([0-9][0-9]?-[0-1]-[0-1])\.log:average initials\s+([0-9]\.[0-9][0-9])\s+average finals:\s+([0-9]\.[0-9][0-9])/\1: \2 \3/g'>> $results_dir/$matrix_name.txt)
done
