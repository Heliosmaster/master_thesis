#! /bin/bash

# grep average * | sed -r 's/hr-([0-9][0-9]?-[0-1]-[0-1])\.log:average initials\s+([0-9]\.[0-9][0-9])\s+average finals:\s+([0-9]\.[0-9][0-9])/\1: \2 \3/g'

matrix_dir="../../matrices2/"
results_dir="../../logs/hr2/summary"
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
#	./hot_restart $matrix 0 0 0 &> $output_dir/hr-0-0-0.log
#	./hot_restart $matrix 0 1 0 &> $output_dir/hr-0-1-0.log
#	./hot_restart $matrix 2 0 0 &> $output_dir/hr-2-0-0.log
#	./hot_restart $matrix 4 0 0 &> $output_dir/hr-4-0-0.log
#	./hot_restart $matrix 4 1 0 &> $output_dir/hr-4-1-0.log
#	./hot_restart $matrix 8 0 0 &> $output_dir/hr-8-0-0.log
#	./hot_restart $matrix 8 0 1 &> $output_dir/hr-8-0-1.log
#	./hot_restart $matrix 8 1 0 &> $output_dir/hr-8-1-0.log
#	./hot_restart $matrix 8 1 1 &> $output_dir/hr-8-1-1.log

	output_dir="../../logs/hr2/pa/$matrix_name"
	if [ ! -d $output_dir ]; then
		mkdir $output_dir
	fi

	./hot_restart $matrix 1 0 0 &> $output_dir/hr-1-0-0.log
#	./hot_restart $matrix 1 1 0 &> $output_dir/hr-1-1-0.log
#	./hot_restart $matrix 7 1 0 &> $output_dir/hr-7-1-0.log

	#$(grep average ../../logs/hr/$matrix_name/po/* | sed -r 's/.*hr-([0-9][0-9]?-[0-1]-[0-1])\.log:average initials\s+([0-9]\.[0-9][0-9])\s+average finals:\s+([0-9]\.[0-9][0-9])/\1: \2 \3/g'>> $results_dir/$matrix_name.txt)
	#$(grep average ../../logs/hr/$matrix_name/pa/* | sed -r 's/.*hr-([0-9][0-9]?-[0-1]-[0-1])\.log:average initials\s+([0-9]\.[0-9][0-9])\s+average finals:\s+([0-9]\.[0-9][0-9])/\1: \2 \3/g'>> $results_dir/$matrix_name.txt)
done
