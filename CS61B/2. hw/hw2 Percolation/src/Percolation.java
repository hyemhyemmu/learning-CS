package src;

import edu.princeton.cs.algs4.WeightedQuickUnionUF;


public class Percolation {
    private final boolean[][] grid; // 网格，记录每个位置是否是 open 的
    private final WeightedQuickUnionUF uf; // Union-Find 数据结构
    private final int virtualTop; // 虚拟顶部节点
    private final int virtualBottom; // 虚拟底部节点
    private final int n; // 网格的大小 N
    private int openSiteCount; // 记录当前开通的节点数


    public Percolation(int N) {
        if (N <= 0)
            throw new IllegalArgumentException("N must be positive!");
        this.n = N;
        this.grid = new boolean[N][N];
        this.uf = new WeightedQuickUnionUF(N * N + 2); // 包括两个虚拟节点
        this.virtualTop = N * N; // 虚拟顶部节点的索引
        this.virtualBottom = N * N + 1; // 虚拟底部节点的索引
        this.openSiteCount = 0;
    }

    public void open(int row, int col) {
        checkInputValidity(row, col);
        if (grid[row][col])
            return;
        grid[row][col] = true;
        openSiteCount++;

        //check connections
        int currentSite = tranTo1stDim(row, col);
        if (row == 0)
            uf.union(currentSite, virtualTop);
        if (row == n - 1)
            uf.union(currentSite, virtualBottom);

        // 连接与当前站点相邻的 open 站点
        if (row > 0 && isOpen(row - 1, col)) { // 上方站点
            uf.union(currentSite, (row - 1) * n + col);
        }
        if (row < n - 1 && isOpen(row + 1, col)) { // 下方站点
            uf.union(currentSite, (row + 1) * n + col);
        }
        if (col > 0 && isOpen(row, col - 1)) { // 左侧站点
            uf.union(currentSite, row * n + col - 1);
        }
        if (col < n - 1 && isOpen(row, col + 1)) { // 右侧站点
            uf.union(currentSite, row * n + col + 1);
        }

    }

    public boolean isOpen(int row, int col) {
        checkInputValidity(row, col);
        return grid[row][col];
    }

    public boolean isFull(int row, int col) {
        checkInputValidity(row, col);
        return uf.connected(virtualTop, tranTo1stDim(row, col));
    }

    public int numberOfOpenSites() {
        return openSiteCount;
    }

    public boolean percolates() {
        return uf.connected(virtualTop, virtualBottom);
    }

    private void checkInputValidity(int row, int col) {
        if (row < 0 || row >= n || col < 0 || col >= n) {
            throw new IndexOutOfBoundsException("row or col should be in range");
        }
    }

    private int tranTo1stDim(int row, int col) {
        return n * row + col;
    }
}
