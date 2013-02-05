#! /bin/bash
for i in {1..10}
do
	echo "$i iteration"
	./Mondriaan3.11/tools/Mondriaan ./matrices/stanford.mtx 2 0.03 >> output_dfl001-$i.txt
done

