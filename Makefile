all:
	gcc -O3 -o Localview Localview.c -IMondriaan3.11/src/include -LMondriaan3.11/src/lib -lMondriaan3 -lm
	/usr/local/matlab/bin/mex -o MatlabLocalview.mexa64 MatlabLocalview.c -IMondriaan3.11/src/include -LMondriaan3.11/src/lib -lMondriaan3 -lm -largeArrayDims
