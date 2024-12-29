import java.util.ArrayList;
import java.util.List;

public class JavaExercises {

    //method 1:make dice
    public static int[] makeDice() {
        return new int[]{1, 2, 3, 4, 5, 6};
    }

    //method 2:
    public static String[] makeOrder(String customer) {
        if (customer.equals("Ergun")) {
            return new String[]{"beyti", "pizza", "hamburger", "tea"};
        } else if (customer.equals("Erik")) {
            return new String[]{"sushi", "pasta", "avocado", "coffee"};
        } else {
            //default output
            return new String[3];
        }
    }

    //method 3:
    public static int findMinMax(int[] array) {
        assert array.length != 0;
        int max = array[0];
        int min = array[0];
        for (int i : array) {
            if (i > max)
                max = i;
            if (i < min)
                min = i;
        }
        return max - min;

    }

    //method4: hailstone
    public static List<Integer> hailstone(int n) {
        assert n > 0;
        List<Integer> lst = new ArrayList<>();
        hailstone_helper(n, lst);
        return lst;
    }

    public static void hailstone_helper(int n, List<Integer> lst) {
        lst.add(n);
        if (n == 1)
            return;
        else if (n % 2 == 0) {
            hailstone_helper(n / 2, lst);
        } else {
            hailstone_helper(3 * n + 1, lst);
        }
    }

}
