#include "utils.h"

int main(){

	int len1 = 10;
	int len2 = 3;
	/* initialization of a vector */
	long* vec = vecallocl(len1);
	long* vec2 = vecallocl(len2);
	int i;
	for(i=0;i<len1;i++)	vec[i] = i;
	for(i=0;i<len2;i++) vec2[i] = 100+i;

	print_vec_inline(vec,len1);
	print_vec_inline(vec2,len2);
	printf("----\n");

 long* vec3 = mix_alternate(vec,len1,vec2,len2);
	long* vec4 = mix_spread(vec,len1,vec2,len2);
	print_vec_inline(vec4,len1+len2);
	print_vec_inline(vec3,len1+len2);

	vecfreel(vec3);
	vecfreel(vec4);
	vecfreel(vec);
	vecfreel(vec2);
	return 0;
}

