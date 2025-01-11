package core;

import java.lang.Math;

import tileengine.TERenderer;
import tileengine.TETile;
import tileengine.Tileset;

import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class World {
    private static final int ROOM_NUM = 8;
    private static final int MIN_SIZE = 8;
    private static final int MAX_SIZE = 20;
    private final Random r;
    public TETile[][] world;
    private final long seed;
    private int roomNum;
    private int width;
    private int height;
    public List<Room> roomList;


    public World(long seed, int width, int height) {
        this.seed = seed;
        this.r = new Random(seed);
        this.width = width;
        this.height = height;
        roomList = new LinkedList<>();
        roomNum=0;
        initializeWorld();
        generateWorld();
    }

    public void initializeWorld() {
        //create world
        this.world = new TETile[width][height];
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                world[x][y] = Tileset.NOTHING;
            }
        }
    }


    /**
     * generate the whole world
     */
    public void generateWorld() {
        generateRooms();
        connectRooms();
        addWalls();

    }

    private void generateRooms() {
        int attempts = 0;
        while (roomNum < ROOM_NUM && attempts < 1000) {
            Room room = generateRandomRoom();
            if (isValidRoom(room)) {
                addRoom(room);
                roomList.add(room);
                roomNum++;
            }
            attempts++;
        }

    }

    private boolean isValidRoom(Room room) {
        //intersect with others
        for (Room otherRooms : roomList) {
            if (room.intersects(otherRooms))
                return false;
        }
        return true;
    }

    private Room generateRandomRoom() {
        int roomWidth = r.nextInt(MIN_SIZE, MAX_SIZE);
        int roomHeight = r.nextInt(MIN_SIZE, MAX_SIZE);
        int x = r.nextInt(0, width - roomWidth); //make sure it is in bound
        int y = r.nextInt(0, height - roomHeight);

        return new Room(x, y, roomWidth, roomHeight);
    }

    private void addRoom(Room room) {
        for (int x = room.getX(); x < room.getX() + room.getWidth(); x++) {
            for (int y = room.getY(); y < room.getY() + room.getHeight(); y++) {
                world[x][y] = Tileset.FLOOR;
            }
        }
    }

    private void connectRooms() {
        for (int i = 0; i < roomList.size() - 1; i++) {
            Room room1 = roomList.get(i);
            Room room2 = roomList.get(i + 1);
            connect(room1, room2);
        }
    }

    private void connect(Room room1, Room room2) {
        int x1 = room1.getCenterX();
        int y1 = room1.getCenterY();
        int x2 = room2.getCenterX();
        int y2 = room2.getCenterY();

        //decide whether horizontal first or vertical first
        switch (r.nextInt(2)) {
            case 0:
                createHorizonHall(x1, x2, y1);
                createVerticalHall(y1, y2, x1);
                break;
            case 1:
                createVerticalHall(y1, y2, x1);
                createHorizonHall(x1, x2, y1);
                break;
        }
    }

    private void createVerticalHall(int y1, int y2, int x) {
        for (int y = Math.min(y1, y2); y <= Math.max(y1, y2); y++) {
            world[x][y] = Tileset.FLOOR;
        }
    }

    private void createHorizonHall(int x1, int x2, int y) {
        for (int x = Math.min(x1, x2); x <= Math.max(x1, x2); x++) {
            world[x][y] = Tileset.FLOOR;
        }
    }

    /**
     * check all 8 directions, if it is NOTHING,replace it with wall.
     */
    private void addWalls() {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (world[x][y] == Tileset.FLOOR)
                    checkNearByWall(x, y);
            }
        }
    }

    /**
     * check 8 direction of the given coordinate, mark as wall if is NOTHING
     */
    private void checkNearByWall(int x, int y) {
        for (int m = y - 1; m <= y + 1; m++) {
            for (int n = x - 1; n <= x + 1; n++) {
                if (m >= 0 && m < height && n >= 0 && n < width) {
                    if (world[n][m] == Tileset.NOTHING) {
                        world[n][m] = Tileset.WALL;
                    }
                }
            }
        }


    }
}
