.SILENT:
all: localview

localview:
	@echo "==Building localview=="
	gcc -O3 -o Localview test_localview.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm
	/usr/local/matlab/bin/mex -o MatlabLocalview.mexa64 MatlabLocalview.c -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm -largeArrayDims

clean: clean_localview

clean_localview:
	@echo ==Cleaning localview==
	rm Localview
	rm MatlabLocalview.mexa64	