include ../init.mk

CFLAGS:=${CFLAGS} -fPIC

all: test_overpaint matlab_overpaint
	

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

test_overpaint: overpaint.o test_overpaint.o ../utils/utils.o
	@echo "* Building overpaint"
	${CC} -o $@ overpaint.o test_overpaint.o ../utils/utils.o ${CFLAGS}
	
%.mex.o: %.c
	${CC} ${MATLABCFLAGS} -c $< -o $@

matlab_overpaint: MatlabOverpaint.mex.o ../utils/utils.o overpaint.o
	@echo "* Building matlab_Overpaint"
	${MATLABCC} -largeArrayDims -o MatlabOverpaint.mexa64 MatlabOverpaint.mex.o overpaint.o ../utils/utils.o ${LIBFLAGS} -largeArrayDims

clean:
	@echo "* Cleaning up overpaint"
	rm -f test_overpaint MatlabOverpaint.mexa64 *.o


