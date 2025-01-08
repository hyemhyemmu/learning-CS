import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class TrieSet {
    private Node root;
    //each node
    private static class Node{
        boolean isKey;
        Map<Character,Node> map;

        private Node(){
            isKey=false;
            map=new HashMap<>();
        }
    }

    //constructor
    public TrieSet(){
        root=new Node();
    }

    public void add(String word){
        Node current=root;
        for (char c:word.toCharArray()){
            current.map.putIfAbsent(c,new Node());
            current=current.map.get(c);
        }
        current.isKey=true; //end of the word
    }

    public boolean contains(String word){
        Node current=root;
        for (char c:word.toCharArray()){
            if (!current.map.containsKey(c))
                return false;
            current=current.map.get(c);
        }
        return current.isKey;
    }

    public boolean startsWith(String prefix) {
        Node curr = root;
        for (char c : prefix.toCharArray()) {
            if (!curr.map.containsKey(c)) {
                return false;
            }
            curr = curr.map.get(c);
        }
        return true;
    }

    public String longestPrefixOf(String word){
        StringBuilder result=new StringBuilder();
        Node current=root;
        for (char c:word.toCharArray()){
            if (!current.map.containsKey(c))
                break;
            result.append(c);
            current=current.map.get(c);
        }
        return result.toString();
    }
}

