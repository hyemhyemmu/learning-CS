package tests;

import org.junit.jupiter.api.Test;
import src.Percolation;

import static com.google.common.truth.Truth.assertThat;
import static org.junit.Assert.*;
import static org.junit.jupiter.api.Assertions.fail;

public class PercolationTest {

    /**
     * Enum to represent the state of a cell in the grid. Use this enum to help you write tests.
     * <p>
     * (0) CLOSED: isOpen() returns true, isFull() return false
     * <p>
     * (1) OPEN: isOpen() returns true, isFull() returns false
     * <p>
     * (2) INVALID: isOpen() returns false, isFull() returns true
     *              (This should not happen! Only open cells should be full.)
     * <p>
     * (3) FULL: isOpen() returns true, isFull() returns true
     * <p>
     */
    private enum Cell {
        CLOSED, OPEN, INVALID, FULL
    }

    /**
     * Creates a Cell[][] based off of what Percolation p returns.
     * Use this method in your tests to see if isOpen and isFull are returning the
     * correct things.
     */
    private static Cell[][] getState(int N, Percolation p) {
        Cell[][] state = new Cell[N][N];
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                int open = p.isOpen(r, c) ? 1 : 0;
                int full = p.isFull(r, c) ? 2 : 0;
                state[r][c] = Cell.values()[open + full];
            }
        }
        return state;
    }

    @Test
    public void basicTest() {
        int N = 5;
        Percolation p = new Percolation(N);
        // open sites at (r, c) = (0, 1), (2, 0), (3, 1), etc. (0, 0) is top-left
        int[][] openSites = {
                {0, 1},
                {2, 0},
                {3, 1},
                {4, 1},
                {1, 0},
                {1, 1}
        };
        Cell[][] expectedState = {
                {Cell.CLOSED, Cell.FULL, Cell.CLOSED, Cell.CLOSED, Cell.CLOSED},
                {Cell.FULL, Cell.FULL, Cell.CLOSED, Cell.CLOSED, Cell.CLOSED},
                {Cell.FULL, Cell.CLOSED, Cell.CLOSED, Cell.CLOSED, Cell.CLOSED},
                {Cell.CLOSED, Cell.OPEN, Cell.CLOSED, Cell.CLOSED, Cell.CLOSED},
                {Cell.CLOSED, Cell.OPEN, Cell.CLOSED, Cell.CLOSED, Cell.CLOSED}
        };
        for (int[] site : openSites) {
            p.open(site[0], site[1]);
        }
        assertThat(getState(N, p)).isEqualTo(expectedState);
        assertThat(p.percolates()).isFalse();
    }

    @Test
    public void oneByOneTest() {
        int N = 1;
        Percolation p = new Percolation(N);
        p.open(0, 0);
        Cell[][] expectedState = {
                {Cell.FULL}
        };
        assertThat(getState(N, p)).isEqualTo(expectedState);
        assertThat(p.percolates()).isTrue();
    }

    @Test
    public void testN1() {
        Percolation perc = new Percolation(1);
        assertFalse(perc.isOpen(0, 0));
        perc.open(0, 0);
        assertTrue(perc.isOpen(0, 0));
        assertTrue(perc.isFull(0, 0));
        assertTrue(perc.percolates());
        Percolation perc2 = new Percolation(1);
        assertFalse(perc2.percolates());
    }

    @Test
    public void testN2() {
        Percolation perc = new Percolation(2);
        perc.open(0, 0);
        assertTrue(perc.isOpen(0, 0));
        assertTrue(perc.isFull(0, 0));
        perc.open(1, 0);
        assertTrue(perc.isOpen(1, 0));
        assertTrue(perc.isFull(1, 0));
        assertTrue(perc.percolates());

        Percolation perc3 = new Percolation(2);
        perc3.open(0, 0);
        perc3.open(1, 1);
        assertFalse(perc3.percolates());
        perc3.open(0, 1);
        assertFalse(perc3.percolates());
        perc3.open(1, 0);
        assertTrue(perc3.percolates());
    }

    @Test
    public void testIllegalInput() {
        assertThrows(IllegalArgumentException.class, () -> new Percolation(-1));
        assertThrows(IllegalArgumentException.class, () -> new Percolation(0));
        Percolation perc = new Percolation(2);
        assertThrows(IndexOutOfBoundsException.class, () -> perc.isOpen(2, 0));
        assertThrows(IndexOutOfBoundsException.class, () -> perc.isOpen(0, 2));
        assertThrows(IndexOutOfBoundsException.class, () -> perc.isOpen(-1, 0));
        assertThrows(IndexOutOfBoundsException.class, () -> perc.isOpen(0, -1));
    }

    @Test
    public void testNumberOfOpenSites() {
        Percolation perc = new Percolation(3);
        assertEquals(0, perc.numberOfOpenSites());
        perc.open(0, 0);
        assertEquals(1, perc.numberOfOpenSites());
        perc.open(1, 1);
        assertEquals(2, perc.numberOfOpenSites());
        perc.open(1, 1); // already open
        assertEquals(2, perc.numberOfOpenSites());
    }

    @Test
    public void testIsFull() {
        Percolation perc = new Percolation(3);
        perc.open(0, 0);
        assertTrue(perc.isFull(0, 0));
        perc.open(0, 1);
        assertTrue(perc.isFull(0, 1));
        perc.open(1, 1);
        assertTrue(perc.isFull(1, 1));
        perc.open(2, 1);
        assertTrue(perc.isFull(2, 1));
        assertTrue(perc.percolates());

        Percolation perc2 = new Percolation(3);
        perc2.open(0, 0);
        assertTrue(perc2.isFull(0, 0));
        perc2.open(0, 1);
        assertTrue(perc2.isFull(0, 1));
        perc2.open(1, 1);
        assertTrue(perc2.isFull(1, 1));
        perc2.open(1, 2);
        assertFalse(perc2.isFull(1, 2));
        perc2.open(2, 2);
        assertFalse(perc2.isFull(2, 2));
        assertFalse(perc2.percolates());
        perc2.open(1, 0);
        assertTrue(perc2.isFull(1, 0));
        perc2.open(2, 0);
        assertTrue(perc2.isFull(2, 0));
        assertTrue(perc2.percolates());
    }

    // 大规模测试可能需要更多的资源和时间，这里仅做示例
    @Test
    public void testLargeN() {
        int N = 100;
        Percolation perc = new Percolation(N);
        for (int col = 0; col < N; col++) {
            perc.open(0, col);
            perc.open(N - 1, col);
        }
        assertTrue(perc.percolates());
    }

}
