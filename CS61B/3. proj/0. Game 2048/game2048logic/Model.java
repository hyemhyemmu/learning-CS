package game2048logic;

import game2048rendering.Board;
import game2048rendering.Side;
import game2048rendering.Tile;

import java.util.Formatter;


/** The state of a game of 2048.
 *  @author P. N. Hilfinger + Josh Hug
 */
public class Model {
    /** Current contents of the board. */
    private final Board board;
    /** Current score. */
    private int score;

    /* Coordinate System: column x, row y of the board (where x = 0,
     * y = 0 is the lower-left corner of the board) will correspond
     * to board.tile(x, y).  Be careful!
     */

    /** Largest piece value. */
    public static final int MAX_PIECE = 2048;

    /** A new 2048 game on a board of size SIZE with no pieces
     *  and score 0. */
    public Model(int size) {
        board = new Board(size);
        score = 0;
    }

    /** A new 2048 game where RAWVALUES contain the values of the tiles
     * (0 if null). VALUES is indexed by (x, y) with (0, 0) corresponding
     * to the bottom-left corner. Used for testing purposes. */
    public Model(int[][] rawValues, int score) {
        board = new Board(rawValues);
        this.score = score;
    }

    /** Return the current Tile at (x, y), where 0 <= x < size(),
     *  0 <= y < size(). Returns null if there is no tile there.
     *  Used for testing. */
    public Tile tile(int x, int y) {
        return board.tile(x, y);
    }

    /** Return the number of squares on one side of the board. */
    public int size() {
        return board.size();
    }

    /** Return the current score. */
    public int score() {
        return score;
    }


    /** Clear the board to empty and reset the score. */
    public void clear() {
        score = 0;
        board.clear();
    }


    /** Add TILE to the board. There must be no Tile currently at the
     *  same position. */
    public void addTile(Tile tile) {
        board.addTile(tile);
    }

    /** Return true iff the game is over (there are no moves, or
     *  there is a tile with value 2048 on the board). */
    public boolean gameOver() {
        return maxTileExists() || !atLeastOneMoveExists();
    }

    /** Returns this Model's board. */
    public Board getBoard() {
        return board;
    }

    /** Returns true if at least one space on the board is empty.
     *  Empty spaces are stored as null.
     * */
    public boolean emptySpaceExists() {
        // TODO: Task 1. Fill in this function.
        int size=size();
        for (int x=0;x<size;x++){
            for (int y=0;y<size;y++){
                if(tile(x,y)==null){
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Returns true if any tile is equal to the maximum valid value.
     * Maximum valid value is given by MAX_PIECE. Note that
     * given a Tile object t, we get its value with t.value().
     */
    public boolean maxTileExists() {
        // TODO: Task 2. Fill in this function.
        int size = size();
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                Tile t = tile(x, y);
                if (t != null && t.value() == MAX_PIECE) {
                    return true;
                }
            }
        }
        return false;
    }


    /**
     * Returns true if there are any valid moves on the board.
     * There are two ways that there can be valid moves:
     * 1. There is at least one empty space on the board.
     * 2. There are two adjacent tiles with the same value.
     */
    public boolean atLeastOneMoveExists() {
        // TODO: Task 3. Fill in this function.
        int size= board.size();
        //check if there is empty tile
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                if (board.tile(x, y) == null) { // 如果是空格
                    return true;
                }
            }
        }
// check if nearby tile is same
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                Tile t = board.tile(x, y); // 当前 tile
                if (t != null) {
                    int value = t.value();

                    // check right
                    if (x + 1 < size) {
                        Tile right = board.tile(x + 1, y);
                        if (right != null && right.value() == value) {
                            return true;
                        }
                    }

                    // up
                    if (y + 1 < size) {
                        Tile above = board.tile(x, y + 1);
                        if (above != null && above.value() == value) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }



    /**
     * Moves the tile at position (x, y) as far up as possible.
     *
     * Rules for Tilt:
     * 1. If two Tiles are adjacent in the direction of motion (ignoring empty space)
     *    and have the same value, they are merged into one Tile of twice the original
     *    value and that new value is added to the score instance variable
     * 2. A tile that is the result of a merge will not merge again on that
     *    tilt. So each move, every tile will only ever be part of at most one
     *    merge (perhaps zero).
     * 3. When three adjacent tiles in the direction of motion have the same
     *    value, then the leading two tiles in the direction of motion merge,
     *    and the trailing tile does not.
     */
    public void moveTileUpAsFarAsPossible(int x, int y) {
        Tile currTile = board.tile(x, y);
        int myValue = currTile.value();
        int targetY = y;

        // TODO: Tasks 5, 6, and 10. Fill in this function.
        // 获取当前的方块
        Tile tile = board.tile(x, y);
        if (tile == null) {
            return; // 如果当前位置没有方块，不做任何操作
        }

        // 找到最终位置
        int targetRow = y;
        while (targetRow < board.size() - 1 && board.tile(x, targetRow + 1) == null) {
            targetRow++;
        }

        // 如果目标位置不同于当前位置，则移动方块
        if (targetRow != y) {
            board.move(x, targetRow, tile);
        }

        if (tile == null) {
            return; // 如果当前位置没有方块，不做任何操作
        }

        while (targetRow < board.size() - 1 && board.tile(x, targetRow + 1) == null) {
            targetRow++;
        }

        // 检查目标位置是否有可合并的方块
        if (targetRow < board.size() - 1) {
            Tile aboveTile = board.tile(x, targetRow + 1);
            if (aboveTile != null && aboveTile.value() == tile.value() && !aboveTile.wasMerged()) {
                // 合并方块
                board.move(x, targetRow + 1, tile);
                return; // 合并后直接返回
            }
        }

        // 如果无法合并，则移动到目标位置
        if (targetRow != y) {
            board.move(x, targetRow, tile);
        }
    }


    /** Handles the movements of the tilt in column x of board B
     * by moving every tile in the column as far up as possible.
     * The viewing perspective has already been set,
     * so we are tilting the tiles in this column up.
     * */
    public void tiltColumn(int x) {
        // TODO: Task 7. Fill in this function.
        for (int y = 0; y < board.size(); y++) {
            moveTileUpAsFarAsPossible(x, y);
        }
    }

    public void tilt(Side side) {
        // TODO: Tasks 8 and 9. Fill in this function.
        for (int x = 0; x < board.size(); x++) {
            tiltColumn(x);
        }
        board.setViewingPerspective(side);
        for (int x = 0; x < board.size(); x++) {
            tiltColumn(x);
        }
        board.setViewingPerspective(Side.NORTH); // 恢复视角
    }

    /** Tilts every column of the board toward SIDE.
     */
    public void tiltWrapper(Side side) {
        board.resetMerged();
        tilt(side);
    }


    @Override
    public String toString() {
        Formatter out = new Formatter();
        out.format("%n[%n");
        for (int y = size() - 1; y >= 0; y -= 1) {
            for (int x = 0; x < size(); x += 1) {
                if (tile(x, y) == null) {
                    out.format("|    ");
                } else {
                    out.format("|%4d", tile(x, y).value());
                }
            }
            out.format("|%n");
        }
        String over = gameOver() ? "over" : "not over";
        out.format("] %d (game is %s) %n", score(), over);
        return out.toString();
    }

    @Override
    public boolean equals(Object o) {
        return (o instanceof Model m) && this.toString().equals(m.toString());
    }

    @Override
    public int hashCode() {
        return toString().hashCode();
    }
}
