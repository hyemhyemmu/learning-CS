package core;

import java.io.Serializable;

public class GameSave implements Serializable {
    private static final long serialVersionUID = 1L;

    private final World world;
    private final Avatar avatar;
    private final long randomSeed;

    //what we want to save: world, avatar, seed
    public GameSave(World world, Avatar avatar, long randomSeed) {
        this.world = world;
        this.avatar = avatar;
        this.randomSeed = randomSeed;
    }

    public World getWorld() {
        return world;
    }

    public Avatar getAvatar() {
        return avatar;
    }

    public long getRandomSeed() {
        return randomSeed;
    }
}
