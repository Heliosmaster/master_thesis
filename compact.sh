#! /bin/bash
for i in {1..10}
do
	tail -n 11 output_dfl001-$i.txt | head -n1 >> output.txt	
done
