package core;

import edu.princeton.cs.algs4.StdDraw;
import tileengine.TERenderer;
import tileengine.TETile;

public class Main {
    private static final int WIDTH = 70;
    private static final int HEIGHT = 50;

    public static void main(String[] args) {
        StdDraw.setCanvasSize(WIDTH * 16, HEIGHT * 16);
        StdDraw.setXscale(0, WIDTH);
        StdDraw.setYscale(0, HEIGHT);
        StdDraw.enableDoubleBuffering();
        Game game = new Game();
        game.start();
    }
}
