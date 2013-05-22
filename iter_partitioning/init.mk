.SILENT:
.PRECIOUS: %.o

CC := gcc
MATLABCC:= /usr/local/matlab/bin/mex
LIBFLAGS:= -I../../Mondriaan4RC/src/include -L../../Mondriaan4RC/src/lib -lMondriaan3 -lm
CFLAGS:= -O3 -g ${LIBFLAGS}
MATLABCFLAGS:= -DUSE_MATLAB -fPIC -pthread -Wall -O333 -DTIME -DUNIX -march=native -I/usr/local/matlab/extern/include ${LIBFLAGS} -DMATLAB_MEX_FILE
HOMEDIR := $(CURDIR)
SRC:=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))
