public class LargerNumber {
    public static int Larger(int x, int y) {
        if (x < y)
            return y;
        return x;
    }

    public static void main(String[] args) {
        System.out.println(Larger(5, 10));
    }
}
