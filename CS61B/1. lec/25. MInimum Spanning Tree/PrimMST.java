import edu.princeton.cs.algs4.Edge;
import edu.princeton.cs.algs4.EdgeWeightedGraph;
import edu.princeton.cs.algs4.IndexMinPQ;


public class PrimMST {
    private static final double INFINITE = Double.POSITIVE_INFINITY;
    private boolean[] marked;
    private Edge[] edgeTo;
    private double[] distTo;
    private IndexMinPQ<Double> PQ;
    private final EdgeWeightedGraph G;

    public PrimMST(EdgeWeightedGraph G, int s) {
        //s is just a starting point,but we don't actually care about it,so we don't have to store its value
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

        prim(PQ);
    }

    private void prim(IndexMinPQ PQ) {
        while (!PQ.isEmpty()) {
            int e = PQ.delMin();
            marked[e]=true;
            for (Edge w : G.adj(e)) { //for every edge connected to e
                relax(w, e);
            }
        }
    }

    private void relax(Edge w, int e) {
        validateVertex(e);
        int n = w.other(e);  // get the other side vertex connected
        //return once find that the vertex is marked, different from DijkstraSPT,because we may find a better route
        if (marked[n]) return;
        if (w.weight() < distTo[n]) {
            distTo[n] = w.weight();
            edgeTo[n] = w;
            marked[n] = true;
            if (PQ.contains(n)) {
                PQ.decreaseKey(n, distTo[n]);
            } else {
                PQ.insert(n, distTo[n]);
            }

        }
    }


    private void validateVertex(int v) {
        int V = distTo.length;
        if (v < 0 || v >= V) {
            throw new IllegalArgumentException("Vertex " + v + " is not between 0 and " + (V - 1));
        }
    }
}
