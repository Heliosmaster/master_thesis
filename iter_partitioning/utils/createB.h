#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "utils.h"

struct sparsematrix createB(struct sparsematrix* Ac, struct sparsematrix* Ar);
struct sparsematrix decomposeB(struct sparsematrix* B, int m, int n);
