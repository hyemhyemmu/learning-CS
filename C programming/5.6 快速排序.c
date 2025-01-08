#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

void swap(int arr[], int i, int j) {
    int temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (i < j) {
        while (i<=high&&arr[i] > pivot) {
            i++;
        }

        while (j>=low&&arr[j] < pivot) {
            j--;
        }

        if (i < j) {
            swap(arr, i, j);
        }
    }

    swap(arr,low, j);
    return j;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
    int pivotIndx = partition(arr, low, high);
        quickSort(arr, low, pivotIndx - 1);
        quickSort(arr, pivotIndx + 1, high);
    }
}


void printArray(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main()
{
    int arr[100];
    for (int i = 0; i < 100; i++) {
        arr[i] = rand() % 10000; // 随机生成数组
    }
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("原数组: ");
    printArray(arr, size);

    clock_t start = clock();
    quickSort(arr, 0, size - 1);

    // 记录结束时间
    clock_t end = clock();

    printf("排序后: ");
    printArray(arr, size);

    // 计算运行时间
    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000; // 转换为微秒
    printf("运行时间: %.0f 微秒\n", timeTaken);

    return 0;
}