import java.util.Arrays;

public class MergeSort {

    public static void main(String[] args) {
        int[] arr = {38, 27, 43, 3, 9, 82, 10};
        System.out.println("原数组: " + Arrays.toString(arr));

        mergeSort(arr, 0, arr.length - 1);
        System.out.println("排序后: " + Arrays.toString(arr));
    }

    public static void mergeSort(int[] arr, int left, int right) {
        if (left >= right) {
            return;
        }


        int mid = left + (right - left) / 2;

        // 递归分解左半部分和右半部分
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // 合并两个有序数组
        merge(arr, left, mid, right);
    }

    // 合并两个有序数组
    public static void merge(int[] arr, int left, int mid, int right) {
        int[] temp = new int[right - left + 1];
        int i = left;
        int j = mid + 1;
        int k = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        while (j <= right) {
            temp[k++] = arr[j++];
        }

        for (int p = 0; p < temp.length; p++) {
            arr[left + p] = temp[p];
        }
    }
}
