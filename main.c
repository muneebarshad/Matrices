#include <stdio.h> 
#include "assignment3.h"
#include "list.c"
int main() { 
	int n = 100, m = 100; 
	HBnodePtr L = createHBlist(n,m); 
	printf("HB list\n"); 
	printHBlist(L); 
	printf("\n");
	printf("SL list\n"); 
	SLnodePtr P = flattenList(L); 
	printSLlist(P); 
	printf("\n");
//	freeSLlist(P); 
//	freeHBlist(L); 
	return 0;
}
