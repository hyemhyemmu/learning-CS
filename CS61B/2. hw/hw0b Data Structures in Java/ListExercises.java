import java.util.ArrayList;
import java.util.List;


public class ListExercises {
    //method 1:
    /*sum: This method takes a list List<Integer> L and returns the total sum of the elements in that list.
    If the list is empty, the method should return 0.*/
    public static int sum(List<Integer> lst) {
        int sum = 0;
        for (int i : lst) {
            sum += i;
        }
        return sum;
    }

    //method 2:
    /*evens: This method takes a list List<Integer> L and returns a new list containing the even numbers of the given list.
     If there are no even elements, it should return an empty list.*/
    public static List<Integer> evens(List<Integer> lst) {
        List<Integer> result = new ArrayList<>();
        for (int i : lst) {
            if (i % 2 == 0)
                result.add(i);
        }
        return result;
    }

    //method 3:
    /*common: This method takes two lists List<Integer> L1,
     List<Integer> L2 and returns a new list containing the items present
     in both of the two given lists.
    If there are no common items, it should return an empty list.*/

    public static List<Integer> common(List<Integer> L1, List<Integer> L2) {
        List<Integer> result = new ArrayList<>();
        for (int i : L1) {
            if (L2.contains(i))
                result.add(i);
        }
        return result;
    }

    //method 4:
    /*countOccurrencesOfC: This method takes a list and a character List<String> words, char c
    and returns the number of occurrences of the given character in a list of strings.
    If the character does not occur in any of the words, it should return 0.*/
    public static int countOccurrencesOfC(List<String> words,char c){
        int count=0;
        for (String word:words){
            for (int i=0;i<word.length();i++){
                if(word.charAt(i)==c)
                    count++;
            }
        }
        return count;
    }
}
