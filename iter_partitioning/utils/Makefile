.SILENT:

all: createB increment reorder randperm split update csort

createB:
	@echo ==Building createB==
	gcc -O3 -g -o createB createB.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm
	/usr/local/matlab/bin/mex -o MatlabCreateB.mexa64 MatlabCreateB.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm -largeArrayDims

increment:
	@echo ==Building test_increment==
	gcc -O3 -g -o test_increment test_increment.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

reorder:
	@echo ==Building test_reorder==
	gcc -g -O3 -g -o test_reorder test_reorder.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

randperm:
	@echo ==Building test_random_permutation==
	gcc -O3 -g -o test_random_permutation test_random_permutation.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

split:
	@echo ==Building test_split==
	gcc -O3 -g -o test_split test_split.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

csort:
	@echo ==Building test_csort==
	gcc -O3 -g -o test_csort test_csort.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

update:
	@echo ==Building test_update_matrix==
	gcc -O3 -g -o test_update_matrix test_update_matrix.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

clean: 
	rm createB;
	rm test_increment;
	rm test_reorder;
	rm test_random_permutation;
	rm test_split;
	rm test_csort;
	rm test_update_matrix;

