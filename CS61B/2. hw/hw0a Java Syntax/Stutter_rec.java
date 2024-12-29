public class Stutter_rec {
    public static String stutter(String s){
        if (s.isEmpty()){
            return "";
        }
        return s.charAt(0)+""+s.charAt(0)+stutter(s.substring(1));
    }

    public static void main(String[] args) {
        System.out.println(stutter("Hello"));
        System.out.println(stutter("Cristiano Ronaldo"));
    }
}
