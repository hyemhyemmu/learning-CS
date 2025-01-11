package core;

import tileengine.TETile;
import tileengine.Tileset;

import java.io.Serializable;

public class Avatar implements Serializable {
    private int x;
    private int y;
    private World world;
    private static final long serialVersionUID = 1L;

    public Avatar(World world) {
        this.world = world;
        // Find first floor tile from bottom-left
        findStartPosition();
        world.world[x][y] = Tileset.AVATAR;
    }

    private void findStartPosition() {
        for (int y = 0; y < world.world[0].length; y++) {
            for (int x = 0; x < world.world.length; x++) {
                if (world.world[x][y] == Tileset.FLOOR) {
                    this.x = x;
                    this.y = y;
                    return;
                }
            }
        }
    }

    public void moveUp() {
        move(x, y + 1);
    }

    public void moveDown() {
        move(x, y - 1);
    }

    public void moveLeft() {
        move(x - 1, y);
    }

    public void moveRight() {
        move(x + 1, y);
    }

    private void move(int newX, int newY) {
        if (isValidMove(newX, newY)) {
            world.world[x][y] = Tileset.FLOOR;
            x = newX;
            y = newY;
            world.world[x][y] = Tileset.AVATAR;
        }
    }

    private boolean isValidMove(int newX, int newY) {
        return newX >= 0 && newX < world.world.length &&
                newY >= 0 && newY < world.world[0].length &&
                world.world[newX][newY] == Tileset.FLOOR;
    }

    public int getX() { return x; }
    public int getY() { return y; }

    public void setWorld(World world) {
        this.world = world;
    }
}
