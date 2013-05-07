.SILENT:

all: createB

createB:
	@echo ==Building createB==
	gcc -O3 -o createB createB.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm
	/usr/local/matlab/bin/mex -o MatlabCreateB.mexa64 MatlabCreateB.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm -largeArrayDims

increment:
	@echo ==Building test_increment==
	gcc -O3 -o test_increment test_increment.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

reorder:
	@echo ==Building test_reorder==
	gcc -g -O3 -o test_reorder test_reorder.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

randperm:
	@echo ==Building test_random_permutation==
	gcc -O3 -o test_random_permutation test_random_permutation.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm


split:
	@echo ==Building test_split==
	gcc -O3 -o test_split test_split.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

update:
	@echo ==Building test_update_matrix==
	gcc -O3 -g -o test_update_matrix test_update_matrix.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

clean: clean_createB

clean_createB:
	@echo ==Cleaning createB==
	rm createB
	rm MatlabCreateB.mexa64	
