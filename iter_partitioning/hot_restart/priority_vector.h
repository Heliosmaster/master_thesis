#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "../utils/utils.h"

long* po_unsorted_concat(struct sparsematrix* A, int flag);
long* pa_unsorted_concat(struct sparsematrix* A, int flag);
long* po_unsorted_random(struct sparsematrix* A);
long* pa_unsorted_random(struct sparsematrix* A);
long* po_unsorted_mix(struct sparsematrix* A, int splitstrategy);
long* pa_unsorted_mix(struct sparsematrix* A, int splitstrategy);
long* po_sorted_simple(struct sparsematrix* A, int widow);
long* pa_sorted_simple(struct sparsematrix* A, int widow);
long* po_sorted_mix(struct sparsematrix* A, int splitstrategy, int widow);
long* pa_sorted_mix(struct sparsematrix* A, int splitstrategy, int widow);
