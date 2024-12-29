public class StarTriangle {
    public static void main(String[] args) {
        String line;
        for (int i = 0; i < 5; i++) {
            line = " ";
            for (int j=0;j<i+1;j++){
                line+="*";
                System.out.println(line);
            }
        }
    }
}
