include ../init.mk

CFLAGS:= ${CFLAGS} -fPIC

all: test_partition_to_matrix test_mix test_number_nonzeros test_reverse_vector test_cut_and_uncut test_create_B test_csort test_increment test_random_permutation test_cut_uncut test_cut_vector test_reorder test_split test_update_matrix matlab_createB MatlabHelper.mex.o matlab_convert cnv mtx2edges

cnv: MondriaanToMatlab MatlabToMondriaan MatlabToMondriaanToMatlab

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

test_create_B: createB.o test_create_B.o utils.o
	${CC} -o test_create_B test_create_B.o createB.o utils.o ${CFLAGS}

test_%: test_%.o utils.o
	@echo "* Building $@"
	${CC} -o $@ $^ ${CFLAGS}

%.mex.o: %.c
	${CC} ${MATLABCFLAGS} -g -c $< -o $@

mtx2edges: mtx_to_edges.o
	@echo "* Building mtx2edges"
	${CC} -o $@ $< ${CFLAGS}

matlab_createB: MatlabCreateB.mex.o utils.o MatlabHelper.mex.o
	@echo "* Building matlab_createB"
	${MATLABCC} -largeArrayDims -o MatlabCreateB.mexa64 MatlabCreateB.mex.o MatlabHelper.mex.o utils.o ${LIBFLAGS} -largeArrayDims

matlab_convert: utils.o MatlabHelper.mex.o MatlabConvert.mex.o
	@echo "* Building matlab_convert"
	${MATLABCC} -largeArrayDims -o MatlabConvert.mexa64 MatlabConvert.mex.o MatlabHelper.mex.o utils.o ${LIBFLAGS} -largeArrayDims

MondriaanToMatlab: MatlabHelper.mex.o MondriaanToMatlab.mex.o
	@echo "* Building MondriaanToMatlab"
	${MATLABCC} -largeArrayDims -o MondriaanToMatlab.mexa64 MondriaanToMatlab.mex.o MatlabHelper.mex.o ${LIBFLAGS} -largeArrayDims

MatlabToMondriaan: MatlabHelper.mex.o MatlabToMondriaan.mex.o
	@echo "* Building MatlabToMondriaan"
	${MATLABCC} -largeArrayDims -o MatlabToMondriaan.mexa64 MatlabToMondriaan.mex.o MatlabHelper.mex.o ${LIBFLAGS} -largeArrayDims

MatlabToMondriaanToMatlab: MatlabHelper.mex.o MatlabToMondriaanToMatlab.mex.o
	@echo "* Building MatlabToMondriaanToMatlab"
	${MATLABCC} -largeArrayDims -o MatlabToMondriaanToMatlab.mexa64 MatlabToMondriaanToMatlab.mex.o MatlabHelper.mex.o ${LIBFLAGS} -largeArrayDims

clean:
	@echo "* Cleaning up utils"
	rm -f test_create_B test_increment test_random_permutation test_reorder test_split test_update_matrix *.o MatlabCreateB.mexa64 test_csort test_reverse_vector mtx2edges test_cut_and_uncut test_cut_vector test_cut_uncut

