package core;

import edu.princeton.cs.algs4.StdDraw;
import tileengine.TERenderer;
import tileengine.TETile;

public class Main {

    public static void main(String[] args) {
        Game game = new Game();

        // Set up StdDraw for input handling
        StdDraw.enableDoubleBuffering();

        // Start game loop
        game.start();

        // interactive module
        //but apparently that there is multiple cases
        while (true) {
            if (StdDraw.hasNextKeyTyped()) {
                char key = StdDraw.nextKeyTyped();
                game.handleKeyPress(key);
            }
            StdDraw.pause(10);
        }



    }
}
