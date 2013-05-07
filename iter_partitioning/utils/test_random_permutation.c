#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "utils.c"

int main(){
   srand(time(NULL));

   int i;
   for(i=0;i<5;i++){
	long* vec = random_permutation(10);
	print_vec_inline(vec,10);
   } 
  
}
