#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/* map a function onto a int array*/

void print_array(int arr[], int n);

void mutate_map(int arr[], int sz, int(*fp)(int)) {
    for (int i = 0; i < sz; i++) {
        arr[i] = (*fp)(arr[i]);
    }
}



int multiply2(int x) { return 2 * x; }
int multiply10(int x) { return 10 * x; }

int main() {
	int arr[] = { 3,1,4 };
    int sz = sizeof(arr) / sizeof(arr[0]);
    print_array(arr, sz);
    mutate_map(arr, sz, &multiply2);
    print_array(arr, sz);
    mutate_map(arr, sz, &multiply10);
    print_array(arr, sz);
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}