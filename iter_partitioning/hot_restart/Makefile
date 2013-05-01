.SILENT:

all: overpaint

overpaint:
	@echo ==Building overpaint==
	gcc -O3 -o Overpaint test_overpainting.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm
	/usr/local/matlab/bin/mex -o MatlabOverpaint.mexa64 MatlabOverpaint.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm -largeArrayDims

clean: clean_overpaint

clean_overpaint:
	@echo ==Cleaning overpaint==
	rm Overpaint
	rm MatlabOverpaint.mexa64
