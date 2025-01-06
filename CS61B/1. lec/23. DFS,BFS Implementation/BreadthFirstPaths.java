import edu.princeton.cs.algs4.Graph;
import edu.princeton.cs.algs4.Queue;


/**
 * Graph API
 * public class Graph {
 * Graph(int V) // create a V-vertex graph with no edges
 * Graph(In in) // read a graph from input stream in
 * int V() // number of vertices
 * int E() // number of edges
 * void addEdge(int v, int w) // add edge v-w to this graph
 * Iterable<Integer> adj(int v) // vertices adjacent to v
 * String toString() // string representation
 * }
 */
public class BreadthFirstPaths {
    private boolean[] marked;
    private int[] edgeTo;
    private int[] disTo;
    private int s;
    private Queue<Integer> fringe;

    //constructor
    public BreadthFirstPaths(Graph G, int s) {
        this.s = s;
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        disTo = new int[G.V()];
        for (int i = 0; i < G.V(); i++) {
            disTo[i] = -1;
        }
        bfs(G, s);
    }

    private void bfs(Graph G, int s) {
        Queue<Integer> fringe = new Queue<Integer>();
        fringe.enqueue(s);
        marked[s]=true;
        disTo[s]=0;
        //recursively processing until queue is empty
        while (!fringe.isEmpty()){
            // v is the element that we will process next
            int v=fringe.dequeue();
            for (int w:G.adj(v)){
                if (!marked[w]){
                    fringe.enqueue(w);
                    marked[w]=true;
                    edgeTo[w]=v;
                    disTo[w]=disTo[v]+1;
                }
            }

        }

    }


    private void validateVertex(int v) {
        int V = marked.length;
        if (v < 0 || v >= V)
            throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V - 1));
    }
}
