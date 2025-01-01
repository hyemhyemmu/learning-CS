package src;

public class UnionFind {
    private int[] set;

    /* Creates a UnionFind data structure holding N items. Initially, all
       items are in disjoint sets. */
    public UnionFind(int N) {
        set = new int[N];
        for (int i = 0; i < N; i++)
            set[i] = -1;
    }

    /* Returns the size of the set V belongs to. */
    public int sizeOf(int v) {
        //check if is legal
        if (v < 0 || v >= set.length) {
            throw new IllegalArgumentException("v is invalid");
        }
        //functions
        int root = find(v);
        return -set[root];
    }

    /* Returns the set of V. If V is the root of a tree, returns the
       negative size of the tree for which V is the root. */
    public int parent(int v) {
        if (v < 0 || v >= set.length) {
            throw new IllegalArgumentException("v is invalid");
        }
        return set[v];
    }

    /* Returns true if nodes/vertices V1 and V2 are connected. */
    public boolean connected(int v1, int v2) {
        return find(v1) == find(v2);
    }

    /* Returns the root of the set V belongs to. Path-compression is employed
       allowing for fast search-time. If invalid items are passed into this
       function, throw an IllegalArgumentException. */
    public int find(int v) {
        //check if is legal
        if (v < 0 || v >= set.length) {
            throw new IllegalArgumentException("v is invalid");
        }
        //functions
        if (set[v] < 0)
            return v;
        set[v] = find(set[v]);
        return set[v];
    }

    /* Connects two items V1 and V2 together by connecting their respective
       sets. V1 and V2 can be any element, and a union-by-size heuristic is
       used. If the sizes of the sets are equal, tie break by connecting V1's
       root to V2's root. Union-ing an item with itself or items that are
       already connected should not change the structure. */
    public void union(int v1, int v2) {
        //check invalidity
        if (v1 < 0 || v2 < 0 || v1 >= set.length || v2 >= set.length)
            throw new IllegalArgumentException("v is invalid");

        //only function when not union itself or union something that already exists！
        int root1 = find(v1);
        int root2 = find(v2);

        if (root1 == root2)
            return;

        if (set[root1] < set[root2]) { // root1的集合更大
            set[root1] += set[root2];
            set[root2] = root1;

        } else {
            set[root2] += set[root1];
            set[root1] = root2;
        }

    }

}

