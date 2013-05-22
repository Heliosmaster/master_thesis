include ../init.mk

CFLAGS:= ${CFLAGS} -fPIC

all: test_create_B test_csort test_increment test_random_permutation test_reorder test_split test_update_matrix matlab_createB MatlabHelper.mex.o matlab_convert

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

test_create_B: createB.o test_create_B.o utils.o
	${CC} -o test_create_B test_create_B.o createB.o utils.o ${CFLAGS}

test_%: test_%.o utils.o
	@echo "* Building $@"
	${CC} -o $@ $< utils.o ${CFLAGS}

%.mex.o: %.c
	${CC} ${MATLABCFLAGS} -g -c $< -o $@

matlab_createB: MatlabCreateB.mex.o utils.o MatlabHelper.mex.o
	@echo "* Building matlab_createB"
	${MATLABCC} -largeArrayDims -o MatlabCreateB.mexa64 MatlabCreateB.mex.o MatlabHelper.mex.o utils.o ${LIBFLAGS} -largeArrayDims

matlab_convert: utils.o MatlabHelper.mex.o MatlabConvert.mex.o
	@echo "* Building matlab_convert"
	${MATLABCC} -largeArrayDims -o MatlabConvert.mexa64 MatlabConvert.mex.o MatlabHelper.mex.o utils.o ${LIBFLAGS} -largeArrayDims

clean:
	@echo "* Cleaning up utils"
	rm -f test_create_B test_increment test_random_permutation test_reorder test_split test_update_matrix *.o MatlabCreateB.mexa64 test_csort

