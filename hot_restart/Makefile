.SILENT:

all: overpaint
overpaint:
	@echo "==Building Overpaint=="
	gcc -O3 -o Overpaint test_overpainting.c -I../Mondriaan3.11/src/include -L../Mondriaan3.11/src/lib -lMondriaan3 -lm
	/usr/local/matlab/bin/mex -o MatlabOverpaint.mexa64 MatlabOverpaint.c -I../Mondriaan3.11/src/include -L../Mondriaan3.11/src/lib -lMondriaan3 -lm -largeArrayDims
