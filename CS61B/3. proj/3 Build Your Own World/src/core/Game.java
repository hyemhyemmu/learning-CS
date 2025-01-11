package core;

import edu.princeton.cs.algs4.StdDraw;
import tileengine.TERenderer;
import tileengine.TETile;
import tileengine.Tileset;

import java.io.*;

public class Game {
    private static final String SAVE_FILE = "game.save";
    private boolean colonPressed = false;
    private static final int WIDTH = 70;
    private static final int HEIGHT = 50;
    private World world;
    private TERenderer ter;
    private GameState currentState;
    private StringBuilder seedInput;
    private Avatar avatar;
    private long seed;

    public Game() {
        //initialize render
        ter = new TERenderer();
        ter.initialize(WIDTH, HEIGHT);
        currentState = GameState.MENU;
        seedInput = new StringBuilder();
    }

    public void start() {
        while (true) {
            switch (currentState) {
                case MENU -> renderMenu();
                case SEED_INPUT -> renderSeed();
                case MAIN_GAME -> renderGame();
            }
        }
    }

    private void renderMenu() {
        // Clear screen
        StdDraw.clear();
        TETile[][] menu = new TETile[WIDTH][HEIGHT];
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                menu[x][y] = Tileset.NOTHING;
            }
        }

        // Draw menu text
        String title = "CS 61B: THE GAME";
        String newGame = "New Game (N)";
        String loadGame = "Load Game (L)";
        String quit = "Quit (Q)";

        StdDraw.text((double) WIDTH / 2 - (double) title.length() / 2, (double) HEIGHT / 2 + 2, title);
        StdDraw.text((double) WIDTH / 2 - (double) newGame.length() / 2, (double) HEIGHT / 2, newGame);
        StdDraw.text((double) WIDTH / 2 - (double) loadGame.length() / 2, (double) HEIGHT / 2 - 1, loadGame);
        StdDraw.text((double) WIDTH / 2 - (double) quit.length() / 2, (double) HEIGHT / 2 - 2, quit);

        StdDraw.show();
        ter.renderFrame(menu);
    }

    public void handleKeyPress(char key) {
        //switch to current state to handle more specifically
        switch (currentState){
            case MENU -> handleMenuInput(key);
            case SEED_INPUT -> handleSeedInput(key);
            case MAIN_GAME -> handleGameInput(key);
        }
    }

    private void handleMenuInput(char key) {
        switch (Character.toLowerCase(key)){
            case 'n'->{
                currentState=GameState.SEED_INPUT;
                seedInput=new StringBuilder();
            }
            case 'l'->loadGame(); //local stats input
            case 'q'->System.exit(0);
        }
    }

    // new screen that allow user to enter seed
    private void renderSeed(){
        StdDraw.clear();
        TETile[][] seedScreen = new TETile[WIDTH][HEIGHT];
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                seedScreen[x][y] = Tileset.NOTHING;
            }
        }

        String prompt = "Enter seed:";
        String seed = seedInput.toString();
        String start = "Press S to start";

        StdDraw.text((double) WIDTH /2 - (double)prompt.length()/2, (double)HEIGHT/2 + 1,prompt);
        StdDraw.text((double)WIDTH/2 - (double)seed.length()/2, (double)HEIGHT/2,seed);
        StdDraw.text((double)WIDTH/2 - (double)start.length()/2, (double)HEIGHT/2 - 1,start);

        StdDraw.show();
        ter.renderFrame(seedScreen);
    }

    private void handleSeedInput(char key) {
        if (Character.isDigit(key))
            seedInput.append(key);
        else if(Character.toLowerCase(key)=='s'&&!seedInput.isEmpty()){
            seed= Long.parseLong(seedInput.toString());
            startNewGame(seed);
            currentState=GameState.MAIN_GAME;
        }
    }

    private void startNewGame(long seed){
        World world=new World(seed,WIDTH,HEIGHT);
        avatar = new Avatar(world);
    }

    private void renderGame(){
        // Clear the canvas first
        StdDraw.clear();

        // Render the world
        ter.renderFrame(world.world);

        // Show the drawn content
        StdDraw.show();
    }

    private void handleGameInput(char key) {
        if (key == ':') {
            colonPressed = true;
            // Wait for next key
            return;
        }

        if (colonPressed) {
            if (Character.toLowerCase(key) == 'q') {
                saveGame();
                System.exit(0);
            }
            colonPressed = false;
            return;
        }


        switch (Character.toLowerCase(key)) {
            case 'w' -> avatar.moveUp();
            case 's' -> avatar.moveDown();
            case 'a' -> avatar.moveLeft();
            case 'd' -> avatar.moveRight();
        }
    }

    private void saveGame() {
        try (ObjectOutputStream out = new ObjectOutputStream(
                new FileOutputStream(SAVE_FILE))) {
            GameSave save = new GameSave(world, avatar, world.getSeed());
            out.writeObject(save);
            System.out.println("Game saved successfully!");
        } catch (IOException e) {
            System.out.println("Failed to save game: " + e.getMessage());
        }
    }

    private void loadGame() {
        try (ObjectInputStream in = new ObjectInputStream(
                new FileInputStream(SAVE_FILE))) {
            GameSave save = (GameSave) in.readObject();
            this.world = save.getWorld();
            this.avatar = save.getAvatar();
            this.avatar.setWorld(world); // 重新连接world引用
            currentState = GameState.MAIN_GAME;
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("Failed to load game: " + e.getMessage());
            // 保持在主菜单状态
        }
    }


    private enum GameState {
        MENU,
        SEED_INPUT,
        MAIN_GAME
    }



}

