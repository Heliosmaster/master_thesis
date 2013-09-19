#! /bin/bash
#grep average * | sed -r 's/hr-([0-9][0-9]?-[0-1]-[0-1])\.log:average initials\s+([0-9]\.[0-9][0-9])\s+average finals:\s+([0-9]\.[0-9][0-9])/\1: \2 \3/g'

cd po
po_dirs=`ls -l | grep -e '^d' | awk '{print $9}'`
results_dir="../../summary"

for dir in $po_dirs
do
	echo ${dir}
	cd $dir
	#	touch $results_dir/po/$dir.txt
	$(grep "average" * | sed -r 's/^hr-([0-9][0-9]?-[0-1]-[0-1])\.log:average initials\s+([0-9]+\.[0-9]+)\s+average finals:\s+([0-9]+\.[0-9]+)*$/\1\t\2\t\3/g' > $results_dir/po/$dir.txt)
	cd ..
done

cd ../pa
pa_dirs=`ls -l | grep -e '^d' | awk '{print $9}'`
for dir in $pa_dirs
do
	echo ${dir}
	cd $dir
	#	touch $results_dir/pa/$dir.txt
	$(grep "average" * | sed -r 's/^hr-([0-9][0-9]?-[0-1]-[0-1])\.log:average initials\s+([0-9]+\.[0-9]+)\s+average finals:\s+([0-9]+\.[0-9]+)*$/\1\t\2\t\3/g' > $results_dir/pa/$dir.txt)
	cd ..
done
