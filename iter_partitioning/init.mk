.SILENT:
.PRECIOUS: %.o

CC := gcc
MATLABCC:= /usr/local/matlab/bin/mex
LIBFLAGS:= -I../../Mondriaan3.11/src/include -L../../Mondriaan3.11/src/lib -lMondriaan3 -lm
CFLAGS:= -O3 -g ${LIBFLAGS}
MATLABCFLAGS:= -DUSE_MATLAB -fPIC -pthread -Wall -O333 -DTIME -DUNIX -march=native -I/usr/local/matlab/extern/include ${LIBFLAGS} -DMATLAB_MEX_FILE
