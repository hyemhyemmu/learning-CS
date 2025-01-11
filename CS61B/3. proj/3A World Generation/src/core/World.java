package core;

import java.lang.Math;

import tileengine.TETile;
import tileengine.Tileset;

import java.util.*;

public class World {
    private static final int ROOM_NUM = 12;
    private static final int MIN_SIZE = 5;
    private static final int MAX_SIZE = 17;
    private static final int MAX_ATTEMPTS = 1000;
    private final Random r;
    public TETile[][] world;
    private final long seed;
    private int roomNum;
    private final int width;
    private final int height;
    public List<Room> roomList;
    private Set<Point> hallwayPoints;


    public World(long seed, int width, int height) {
        this.seed = seed;
        this.r = new Random(seed);
        this.width = width;
        this.height = height;
        roomList = new LinkedList<>();
        hallwayPoints=new HashSet<>();
        roomNum = 0;
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
     * generate the whole world, regenerate if does not match requirements
     */
    public void generateWorld() {
            initializeWorld();
            generateRooms();
            connectRooms();
            addWalls();
    }


    private void generateRooms() {
        int attempts = 0;
        //when use random, it is always helpful to have a "attempt",
        // in case that program gone into dead loop
        while (roomNum < ROOM_NUM && attempts < MAX_ATTEMPTS) {
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
            if (room.intersectsWithBuffer(otherRooms, 2))
                return false;
        }

        return true;
    }

    private Room generateRandomRoom() {
        int roomWidth = r.nextInt(MIN_SIZE, MAX_SIZE);
        int roomHeight = r.nextInt(MIN_SIZE, MAX_SIZE);
        int x = r.nextInt(1, width - roomWidth - 2);
        int y = r.nextInt(1, height - roomHeight - 2);

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
        //user Kruskal's for help
        UnionFind uf = new UnionFind(roomList.size());
        PriorityQueue<Edge> edges = new PriorityQueue<>();

        for (int i = 0; i < roomList.size(); i++) {
            for (int j = i + 1; j < roomList.size(); j++) {
                Room r1 = roomList.get(i);
                Room r2 = roomList.get(j);
                int dist = Math.abs(r1.getCenterX() - r2.getCenterX()) +
                        Math.abs(r1.getCenterY() - r2.getCenterY());
                edges.offer(new Edge(i, j, dist));
            }
        }

        //Kruskal's
        while (!edges.isEmpty()) {
            Edge edge = edges.poll();

            //if not connected yet
            if (!uf.isConnected(edge.from, edge.to)) {
                connectWithTurns(roomList.get(edge.from), roomList.get(edge.to));
                uf.connect(edge.from, edge.to);
            }
        }
    }

    private void connectWithTurns(Room room1, Room room2) {
        int x1 = room1.getCenterX();
        int y1 = room1.getCenterY();
        int x2 = room2.getCenterX();
        int y2 = room2.getCenterY();

        // randomly choose turning point
        int turnX = x1;
        int turnY = y2;

        if (r.nextBoolean()) {
            turnX = x2;
            turnY = y1;
        }

        // create hallway
        createHallway(x1, y1, turnX, turnY);
        createHallway(turnX, turnY, x2, y2);
    }

    private void createHallway(int x1, int y1, int x2, int y2) {
        int minX = Math.min(x1, x2);
        int maxX = Math.max(x1, x2);
        int minY = Math.min(y1, y2);
        int maxY = Math.max(y1, y2);

        // create while recording hall positions
        for (int x = minX; x <= maxX; x++) {
            for (int y = minY; y <= maxY; y++) {
                if (world[x][y] != Tileset.FLOOR) {
                    world[x][y] = Tileset.FLOOR;
                    hallwayPoints.add(new Point(x, y));
                }
            }
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

    //UnionFind
    private static class UnionFind {
        private int[] parent;

        public UnionFind(int n) {
            parent = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = -1;
            }
        }

        public int find(int n) {
            int root = n;
            while (parent[root] >= 0) {
                root = parent[root];
            }

            //compression
            while (n != root) {
                int temp = parent[n];
                parent[n] = root;
                n = temp;
            }
            return root;
        }

        public void connect(int p, int q) {
            int i = find(p);
            int j = find(q);

            if (i == j)
                return;

            //connect the smaller tree to the larger one
            if (parent[i] < parent[j]) { // i's tree is larger
                parent[i] += parent[j];
                parent[j] = i;
            } else {
                parent[j] += parent[i];
                parent[i] = j;
            }
        }

        public boolean isConnected(int p, int q) {
            return find(p) == find(q);
        }
    }


    //edge class for Kruskal's
    private static class Edge implements Comparable<Edge> {
        int from, to, weight;

        Edge(int from, int to, int weight) {
            this.from = from;
            this.to = to;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge other) {
            return Integer.compare(this.weight, other.weight);
        }
    }
    private static class Point {
        int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}
