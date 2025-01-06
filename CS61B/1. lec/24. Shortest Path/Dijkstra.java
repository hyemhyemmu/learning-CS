import edu.princeton.cs.algs4.Graph;
import edu.princeton.cs.algs4.IndexMinPQ;
import edu.princeton.cs.algs4.Queue;

public class Dijkstra_NonDirected {
    private int[] edgeTo;
    private int[] distTo;
    private IndexMinPQ<Integer> PQ;
    private static final int INFINITE = Integer.MAX_VALUE;
    private static final int DEFAULT_WEIGHT = 1;
    private int s;
    private Graph G;

    public Dijkstra_NonDirected(Graph G, int s) {
        this.G = G;
        this.edgeTo = new int[G.V()];
        this.distTo = new int[G.V()];
        this.PQ = new IndexMinPQ<>(G.V());
        this.s = s;

        // 初始化distTo数组
        for (int v = 0; v < G.V(); v++) {
            distTo[v] = INFINITE;
            edgeTo[v] = -1;
            PQ.insert(v, distTo[v]);
        }
        distTo[s] = 0;
        PQ.changeKey(s, distTo[s]);

        dijkstra(PQ, s);
    }

    private void dijkstra(IndexMinPQ<Integer> pq, int s) {
        while (!pq.isEmpty()) {
            int v = pq.delMin();
            //relax all the adjacent vertex
            for (int w : G.adj(v)) {
                relax(v, w);
            }
        }
    }

    private void relax(int v, int w) {
        if (distTo[v] + DEFAULT_WEIGHT < distTo[w]) {
            distTo[w] = distTo[v] + DEFAULT_WEIGHT;
            edgeTo[w] = v;
            PQ.changeKey(w, distTo[w]); // 更新w的距离
        }
    }

    public int distTo(int v) {
        validateVertex(v);
        return distTo[v];
    }

    private void validateVertex(int v) {
        int V = distTo.length;
        if (v < 0 || v >= V) {
            throw new IllegalArgumentException("Vertex " + v + " is not between 0 and " + (V - 1));
        }
    }

    public Iterable<Integer> pathTo(int v) {
        validateVertex(v);
        if (distTo[v] == INFINITE) return null;
        Queue<Integer> path = new Queue<>();
        for (int x = v; x != s; x = edgeTo[x]) {
            path.enqueue(x);
        }
        path.enqueue(s);
        return path;
    }
}