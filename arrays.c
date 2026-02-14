#include <stdio.h>


#define MAX_IDS 5 // define not global var

int main () {

	int ids[MAX_IDS];
	int arr[] = {2, 4, 8, 12, 16, 18};
	memset(&ids, '\0', sizeof(ids)); // clean the mem

	ids[0] = 4;
	printf("%d\n", ids[0]);
	printf("%d\n", sizeof(ids)); // int = 4 bytes
	printf("%d\n", arr[3]);


}
