package core;

import tileengine.TERenderer;
import tileengine.TETile;

public class Main {
    private static final int WIDTH = 70;
    private static final int HEIGHT = 50;

    public static void main(String[] args) {
        //initialize render
        TERenderer ter = new TERenderer();
        ter.initialize(WIDTH, HEIGHT);

        World newWorld=new World(6578897764558030356L,WIDTH,HEIGHT);
        TETile[][] world=newWorld.world;

        //render world
        ter.renderFrame(world);


    }
}
