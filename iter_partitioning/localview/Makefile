include ../init.mk

CFLAGS:=${CFLAGS} -fPIC

all: test_localview matlab_localview

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

test_localview: localview.o po_localview.o test_localview.o ../utils/utils.o
	@echo "* Building localview"
	${CC} -o $@ $^ ${CFLAGS}

%.mex.o: %.c
	${CC} ${MATLABCFLAGS} -c $< -o $@

matlab_localview: MatlabLocalview.mex.o ../utils/utils.o localview.o ../utils/MatlabHelper.mex.o po_localview.o
	@echo "* Building matlab_localview"
	${MATLABCC} -o MatlabLocalview.mexa64 $^ ${LIBFLAGS} -largeArrayDims

clean:
	@echo "* Cleaning up localview"
	rm -f test_localview MatlabLocalview.mexa64 *.o
