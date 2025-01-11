package core;

public class Room {
    private final int x;
    private final int y;
    private final int width;
    private final int height;

    public Room(int x, int y, int width, int height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }

    /**
     * check if this room intersects with another room
     */
    public boolean intersects(Room other) {
        return !(x + width + 1 < other.x || other.x + other.width + 1 < x ||
                y + height + 1 < other.y || other.y + other.height + 1 < y);
    }

    // Getters
    public int getX() { return x; }
    public int getY() { return y; }
    public int getWidth() { return width; }
    public int getHeight() { return height; }
    public int getCenterX() { return x + width / 2; }
    public int getCenterY() { return y + height / 2; }

}
