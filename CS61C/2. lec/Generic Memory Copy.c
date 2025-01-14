#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* normal version */
void swap_1(int* ptr1, int* ptr2) {
	int temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

/* swap using memcpy */
void swap_2(void* ptr1, void* ptr2,size_t nbytes) {
	char* temp = (char*)malloc(nbytes);  
	if (temp == NULL) {
		return;
	}
	memcpy(temp, ptr1, nbytes);
	memcpy(ptr1, ptr2, nbytes);
	memcpy(ptr2, temp, nbytes);
	free(temp);
}

/* optimized version of swap */
void swap_3(void* ptr1, void* ptr2, size_t nbytes) {
    if (nbytes == sizeof(int)) {
        int temp = *(int*)ptr1;
        *(int*)ptr1 = *(int*)ptr2;
        *(int*)ptr2 = temp;
    }
    else {
        char* temp = (char*)malloc(nbytes);
        if (temp == NULL) {
            return;
        }
        memcpy(temp, ptr1, nbytes);
        memcpy(ptr1, ptr2, nbytes);
        memcpy(ptr2, temp, nbytes);
        free(temp);
    }
}

/* swap the first and the last item of an array */
void swap_end(void* arr, size_t nelems, size_t nbytes) {
    //notice:the char* here is REALLY IMPORTANT as it make sure that the addition is 1 byte)
    swap_3(arr, (char*)arr+(nelems-1), nbytes);
}