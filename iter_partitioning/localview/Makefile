include ../init.mk

CFLAGS:=${CFLAGS} -fPIC

all: test_localview matlab_localview

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

test_localview: localview.o test_localview.o ../utils/utils.o
	@echo "* Building localview"
	${CC} -o $@ localview.o test_localview.o ../utils/utils.o ${CFLAGS}

%.mex.o: %.c
	${CC} ${MATLABCFLAGS} -c $< -o $@

matlab_localview: MatlabLocalview.mex.o ../utils/utils.o localview.o
	@echo "* Building matlab_localview"
	${MATLABCC} -largeArrayDims -o MatlabLocalview.mexa64 MatlabLocalview.mex.o localview.o ../utils/utils.o ${LIBFLAGS} -largeArrayDims

clean:
	@echo "* Cleaning up localview"
	rm -f test_localview MatlabLocalview.mexa64 *.o
