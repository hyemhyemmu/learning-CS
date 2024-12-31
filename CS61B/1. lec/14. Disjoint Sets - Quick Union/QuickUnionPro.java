public class QuickUnionPro implements DisjointSets {
    /**
     * more efficient than QuickUnion: Path Compression and merge by rank
     */
    private int[] parent;

    public QuickUnionPro(int N) {
        parent = new int[N];
        for (int i = 0; i < N; i++) {
            parent[i] = -1;
        }
    }

    private int find(int p) {
        /**
         * All the node seen will be added to the root
         */
        if (parent[p] < 0) {
            return p;
        }
        //把路上遍历到的所有点都指向根节点
        parent[p] = find(parent[p]);
        return parent[p];
    }


    @Override
    public void connect(int p, int q) {
        int i = find(p);
        int j = find(q);
        //如果二者相同，无需合并
        if (i == j) {
            return;
        }
        //比较两个树的大小（通过parent[i]和parent[j]的负值），将较小的树合并到较大的树上。
        //更新较大树的大小，并将较小树的根指向较大树的根。
        if (parent[i] < parent[j]) { // i's tree is larger
            parent[i] += parent[j];
            parent[j] = i;
        } else {
            parent[j] += parent[i];
            parent[i] = j;
        }
        parent[i] = j;


    }

    @Override
    public boolean isConnected(int p, int q) {
        return find(p) == find(q);
    }
}
