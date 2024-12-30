public class SentinelSLList {
    //the first item is at sentinel
    private IntNode sentinel;
    private int size;

    //sentinel
    public SentinelSLList() {
        sentinel = new IntNode(0, null);
        size = 0;
    }

    public SentinelSLList(int x) {
        sentinel = new IntNode(0, null);
        sentinel.rest = new IntNode(x, null);
        size = 1;
    }

    //Adds x to the front of the sentinel
    public void addFirst(int x) {
        sentinel.rest = new IntNode(x, sentinel.rest);
        size += 1;
    }

    //Returns the first item of the sentinel
    public int getFirst() {
        return sentinel.rest.first;
    }

    //Adds x to the end of the sentinel
    public void addLast(int x) {
        IntNode p = sentinel; //pointer
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
//    //return the size of the List
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
