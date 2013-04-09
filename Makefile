.SILENT:

all: create_b #localview 
localview:
	@echo ==Localview==
	gcc -O3 -o Localview test_localview.c -IMondriaan3.11/src/include -LMondriaan3.11/src/lib -lMondriaan3 -lm
	/usr/local/matlab/bin/mex -o MatlabLocalview.mexa64 MatlabLocalview.c -IMondriaan3.11/src/include -LMondriaan3.11/src/lib -lMondriaan3 -lm -largeArrayDims
create_b:
	@echo ==createB==
	gcc -O3 -o createB createB.c -IMondriaan3.11/src/include -LMondriaan3.11/src/lib -lMondriaan3 -lm
	/usr/local/matlab/bin/mex -o MatlabCreateB.mexa64 MatlabCreateB.c -IMondriaan3.11/src/include -LMondriaan3.11/src/lib -lMondriaan3 -lm -largeArrayDims
