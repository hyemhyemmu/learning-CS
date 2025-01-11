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
     * check if this room intersectsWithBuffer with another room
     */
    public boolean intersectsWithBuffer(Room other,int buffer) {
        return !(x + width + buffer < other.x || other.x + other.width + buffer < x ||
                y + height + buffer < other.y || other.y + other.height + buffer < y);
    }

    // Getters
    public int getX() { return x; }
    public int getY() { return y; }
    public int getWidth() { return width; }
    public int getHeight() { return height; }
    public int getCenterX() { return x + width / 2; }
    public int getCenterY() { return y + height / 2; }

}
