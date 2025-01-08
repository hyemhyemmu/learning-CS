import edu.princeton.cs.algs4.EdgeWeightedDigraph;
import edu.princeton.cs.algs4.DirectedEdge;

public class DAGLGT extends DAGSPT {
    public DAGLGT(EdgeWeightedDigraph G, int s) {
        super(negateEdgeWeights(G), s);
    }


    private static EdgeWeightedDigraph negateEdgeWeights(EdgeWeightedDigraph G) {
        EdgeWeightedDigraph negatedGraph = new EdgeWeightedDigraph(G.V());
        for (int v = 0; v < G.V(); v++) {
            for (DirectedEdge e : G.adj(v)) {
                negatedGraph.addEdge(new DirectedEdge(e.from(), e.to(), -e.weight()));
            }
        }
        return negatedGraph;
    }

    @Override
    public double distTo(int v) {
        // 取反以还原为最长路径距离
        return -super.distTo(v);
    }
}
