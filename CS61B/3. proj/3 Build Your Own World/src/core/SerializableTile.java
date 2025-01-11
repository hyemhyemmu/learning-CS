package core;

import tileengine.TETile;
import java.awt.Color;
import java.io.Serializable;

public class SerializableTile implements Serializable {
    private static final long serialVersionUID = 1L;

    private final char character;
    private final SerializableColor textColor;
    private final SerializableColor backgroundColor;
    private final String description;
    private final String filepath;
    private final int id;

    public SerializableTile(TETile tile) {
        this.character = tile.character();
        this.textColor = new SerializableColor(tile.getTextColor());
        this.backgroundColor = new SerializableColor(tile.getBackgroundColor());
        this.description = tile.description();
        this.filepath = null; // 文件路径在序列化时不保存
        this.id = tile.id();
    }

    public TETile toTETile() {
        return new TETile(character,
                textColor.toColor(),
                backgroundColor.toColor(),
                description,
                filepath,
                id);
    }

    // 内部类用于序列化Color对象
    private static class SerializableColor implements Serializable {
        private static final long serialVersionUID = 1L;
        private final int red;
        private final int green;
        private final int blue;

        public SerializableColor(Color color) {
            this.red = color.getRed();
            this.green = color.getGreen();
            this.blue = color.getBlue();
        }

        public Color toColor() {
            return new Color(red, green, blue);
        }
    }
}