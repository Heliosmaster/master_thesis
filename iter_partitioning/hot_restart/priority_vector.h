#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "../utils/utils.h"

void get_pa_unsorted(struct sparsematrix* A, long** cut_rows, int* length_cut_rows, long** cut_cols, int* length_cut_cols, long** uncut_rows, int* length_uncut_rows, long** uncut_cols, int* length_uncut_cols);
void get_po_sorted(struct sparsematrix* A, int widow, long** sorted_rows, long** sorted_cols);
void get_pa_sorted(struct sparsematrix* A, int widow, long** sorted_cut_rows, int* length_cut_rows, long** sorted_cut_cols, int* length_cut_cols, long** sorted_uncut_rows, int* length_uncut_rows, long** sorted_uncut_cols, int* length_uncut_cols);

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
long* po_sorted_concat(struct sparsematrix* A, int widow, int flag);
long* pa_sorted_concat(struct sparsematrix* A, int widow, int flag);
