include ../init.mk

CFLAGS:=${CFLAGS} -fPIC

all: test_overpaint matlab_overpaint
hr: hot_restart	

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

test_overpaint: overpaint.o test_overpaint.o ../utils/utils.o
	@echo "* Building overpaint"
	${CC} -o $@ overpaint.o test_overpaint.o ../utils/utils.o ${CFLAGS}

hot_restart: hot_restart.o overpaint.o ../utils/utils.o ../utils/createB.o
	@echo "* Building hot_restart"
	${CC} -o $@ $^ ${CFLAGS}
	
%.mex.o: %.c
	${CC} ${MATLABCFLAGS} -c $< -o $@

matlab_overpaint: MatlabOverpaint.mex.o ../utils/utils.o overpaint.o ../utils/MatlabHelper.mex.o
	@echo "* Building matlab_Overpaint"
	${MATLABCC} -largeArrayDims -o MatlabOverpaint.mexa64 MatlabOverpaint.mex.o overpaint.o ../utils/utils.o ../utils/MatlabHelper.mex.o ${LIBFLAGS} -largeArrayDims

clean:
	@echo "* Cleaning up overpaint"
	rm -f hot_restart test_overpaint MatlabOverpaint.mexa64 *.o


