import edu.princeton.cs.algs4.*;

public class DijkstraSPT {
    private static final double INFINITE = Double.POSITIVE_INFINITY;
    private boolean[] marked;
    private Edge[] edgeTo;
    private double[] distTo;
    private IndexMinPQ<Double> PQ;
    private final int s;
    private final EdgeWeightedGraph G;

    public DijkstraSPT(EdgeWeightedGraph G, int s) {
        this.s = s;
        this.G = G;
        edgeTo = new Edge[G.V()];
        distTo = new double[G.V()];
        marked = new boolean[G.V()];
        PQ = new IndexMinPQ<>(G.V());

        //initialize
        for (int v = 0; v < G.V(); v++) {
            distTo[v] = INFINITE;
            edgeTo[v] = null;
            PQ.insert(v, distTo[v]);
            marked[v] = false;
        }
        distTo[s] = 0;
        PQ.changeKey(s, distTo[s]);

        dijkstra(PQ);
    }

    private void dijkstra(IndexMinPQ<Double> PQ) {
        while (!PQ.isEmpty()) {
            int v = PQ.delMin();
            //marked once take it out of the PQ
            marked[v] = true;
            //relax all the adjacent vertex of v
            // w are all the edges connected to v
            for (Edge w : G.adj(v)) {
                relax(w, v);
            }
        }
    }

    /**
     * relax all the items connected to v
     *
     * @param w edges connected to v
     * @param v index of item whose neighbours need to deal with
     */
    private void relax(Edge w, int v) {
        validateVertex(v);
        //index of items connected to v
        int n = w.other(v);
        if (marked[n]) return;
        if (distTo[v] + w.weight() < distTo[n]) {
            distTo[n] = distTo[v] + w.weight();
            edgeTo[n] = w;
            if (PQ.contains(n)) {
                PQ.decreaseKey(n, distTo[n]);
            } else {
                PQ.insert(n, distTo[n]);
            }

        }
    }

    public double distTo(int v) {
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
        if (distTo[v] == INFINITE) return null;
        Stack<Integer> path = new Stack<>();
        for (int x = v; x != s; x = edgeTo[x].other(x)) {
            path.push(x);
        }
        path.push(s);
        return path;
    }
}