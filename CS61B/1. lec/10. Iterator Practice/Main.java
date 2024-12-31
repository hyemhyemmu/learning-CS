import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;

public class Main {
    public static void main(String[] args) {
        // 编写代码,使用Iterator遍历并打印出以下ArrayList中的所有元素
        ArrayList<String> fruits = new ArrayList<>(Arrays.asList("苹果", "香蕉", "橙子", "葡萄"));

        Iterator<String> iterator=fruits.iterator();

        while (iterator.hasNext())
        {
            String current_fruit=iterator.next();
            System.out.println(current_fruit);
        }
    }
}
