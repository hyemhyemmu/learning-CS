public class SLList {
    private IntNode List;
    private int size;

    public SLList(int x) {
        List = new IntNode(x, null);
        size = 1;
    }

    //Adds x to the front of the list
    public void addFirst(int x) {
        List = new IntNode(x, List);
        size += 1;
    }

    //Returns the first item of the list
    public int getFirst() {
        return List.first;
    }

    //Adds x to the end of the list
    public void addLast(int x) {
        IntNode p = List; //pointer
        while (p.rest != null) {
            p = p.rest;
        }
        p.rest = new IntNode(x, null);
        size += 1;
    }

//    private static int size(IntNode p) {
//        if (p.rest == null)
//            return 1;
//        return 1 + size(p.rest);
//    }
//
//    //return the size of the list
//    public int size() {
//        return size(List);
//    }

    public int size() {
        return size;
    }

    public static void main(String[] args) {
        SLList L = new SLList(15);
        L.addFirst(10);
        L.addFirst(5);
        L.addLast(99);
        System.out.println(L.getFirst());
        System.out.println(L.size());
    }
}
