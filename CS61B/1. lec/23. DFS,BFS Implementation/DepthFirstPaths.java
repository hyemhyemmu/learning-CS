import edu.princeton.cs.algs4.Graph;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

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
public class DepthFirstPaths {
    private boolean[] marked;
    private int[] edgeTo;
    private int s; //starting vertex
    private int[] disTo; //distance to the source point

    public DepthFirstPaths(Graph G, int s) {
        this.s=s;
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];     // initialize edgeTo array
        disTo = new int[G.V()];      // initialize disTo array
        for (int i = 0; i < G.V(); i++) {
            disTo[i] = -1;           // initialize distances to -1
        }
        //length of "marked" is the size of all the vertexes
        validateVertex(s);
        disTo[s] = 0;
        dfs(G, s);
    }

    private void dfs(Graph G, int v) {
        marked[v] = true;
        for (int n : G.adj(v)) {
            if (!marked[n]) {
                edgeTo[n] = v;
                disTo[n] = disTo[v] + 1;
                dfs(G, n);
            }
        }
    }

    private void validateVertex(int v) {
        int V = marked.length;
        if (v < 0 || v >= V)
            throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V - 1));
    }


    //return the path from source to v
    public Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v)) return null;
        List<Integer> path = new ArrayList<>();
        for (int x = v; x != s; x = edgeTo[x]) {
            path.add(x);
        }
        path.add(s);
        Collections.reverse(path);
        return path;
    }


    //whether if there is a path from source to v
    public boolean hasPathTo(int v) {
        validateVertex(v);
        return marked[v];
    }

    public int disTo(int v) {
        validateVertex(v);
        if (!hasPathTo(v))
            throw new IllegalArgumentException("There is no path from source to the point you entered");
        return disTo[v];
    }

}