#include <stdlib.h>
#include <time.h>
#include "localview.h"
#include "po_localview.h"
#include "../utils/utils.h"
#include "../utils/MatlabHelper.h"

/* This function provides the actual Matlab interface. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	struct sparsematrix *MondriaanMatrix;

	int flag;
	/* converting from Matlab to Mondriaan */
	MondriaanMatrix = ConvertMatlabToMondriaan(prhs[0]);
	if(nrhs < 2){
		flag = 1;
	} else {
		flag = (int)ExtractDouble(prhs[1]);
	}
	if (flag != 0 && flag != 1) mexErrMsgTxt("Wrong flag");

	/* performing split */
	struct twomatrices lw;
	if(flag){
		lw = localview(MondriaanMatrix);
	} else {
		lw = po_localview(MondriaanMatrix);
	}

	/* separating the two parts */
	struct sparsematrix matrix = lw.Ac;
	struct sparsematrix matrix2 = lw.Ar;

	/* converting back from Mondriaan to Matlab */
	plhs[0] = ConvertMondriaanToMatlab(&matrix);
	plhs[1] = ConvertMondriaanToMatlab(&matrix2);

	MMDeleteSparseMatrix(MondriaanMatrix);
}

