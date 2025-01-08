import java.util.Arrays;

public class QuickSort {

    public static void main(String[] args) {
        int[] arr = {38, 27, 43, 3, 9, 82, 10};
        System.out.println("原数组: " + Arrays.toString(arr));
        long startTime = System.nanoTime();
        quickSort(arr, 0, arr.length - 1);
        long endTime = System.nanoTime();
        System.out.println("排序后: " + Arrays.toString(arr));
        System.out.println("运行时间: " + (endTime - startTime) + " 纳秒");
    }

    private static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(arr, low, high);
            quickSort(arr, low, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, high);
        }
    }

    private static int partition(int[] arr, int low, int high) {
        int pivot = arr[low];
        int i = low + 1;//start searching from left, finding those larger than pivot
        int j = high; //start searching from right, finding those smaller than pivot
        while (i < j) {
            //stop when found an element larger than pivot
            while (i <= high && arr[i] <= pivot) {
                i++;
            }
            //stop when found an element smaller than pivot
            while (j >= low && arr[j] >= pivot) {
                j--;
            }
            if (i < j)
                swap(arr, i, j);
        }

        //put pivot in the right spot
        swap(arr, low, j);
        return j;
    }

    // swap elements at index m and n
    private static void swap(int[] arr, int m, int n) {
        int temp;
        temp = arr[m];
        arr[m] = arr[n];
        arr[n] = temp;
    }
}
