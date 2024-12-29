import java.util.List;
import java.util.Map;
import java.util.TreeMap;


public class MapExercises {
    //method 1:
    /*letterToNum:
    This method returns a map from every lower case letter to the number corresponding to its ordering in the alphabet,
    where ‘a’ corresponds to 1 and ‘z’ corresponds to 26.*/
    public static Map<Character, Integer> letterToNum() {
        Map<Character, Integer> lettermap = new TreeMap<>();
        for (char c = 'a'; c <= 'z'; c++) {
            lettermap.put(c, c - 'a' + 1);
        }
        return lettermap;
    }

    //method 2:
    /*squares: This method takes a list List<Integer> nums
    and returns a map from the integers in the list to their squares.
    If the given list is empty, it should return an empty map.*/
    public static Map<Integer, Integer> squares(List<Integer> nums) {
        Map<Integer, Integer> dict = new TreeMap<>();
        if (nums.isEmpty())
            return dict;
        for (int i : nums) {
            dict.put(i, i * i);
        }
        return dict;
    }

    //method 3:
    /*countWords: This method takes a list List<String> words
    and returns a map from words in the list to the number of times they appear.
    If the given list is empty, it should return an empty map.*/
    public static Map<String, Integer> countWords(List<String> words) {
        Map<String, Integer> result = new TreeMap<>();
        if (words.isEmpty())
            return result;
        for (String word : words) {
            result.put(word, result.getOrDefault(word, 1) + 1);
        }
        return result;
    }
}
