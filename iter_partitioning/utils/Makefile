.SILENT:

all: createB

createB:
	@echo ==Building createB==
	gcc -O3 -o createB createB.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm
	/usr/local/matlab/bin/mex -o MatlabCreateB.mexa64 MatlabCreateB.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm -largeArrayDims

reorder:
	@echo ==Building test_reorder==
	gcc -O3 -o test_reorder test_reorder.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm

clean: clean_createB

clean_createB:
	@echo ==Cleaning createB==
	rm createB
	rm MatlabCreateB.mexa64	
