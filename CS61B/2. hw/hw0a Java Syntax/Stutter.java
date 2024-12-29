public class Stutter {
    public static String stutter(String s) {
        String output = "";
        for (int i = 0; i < s.length(); i++) {
            output += s.charAt(i);
            output += s.charAt(i);
        }
        return output;
    }

    public static void main(String[] args) {
        System.out.println(stutter("hello"));
    }
}
