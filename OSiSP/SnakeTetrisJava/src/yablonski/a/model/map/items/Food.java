package yablonski.a.model.map.items;

import yablonski.a.model.Block;

import java.awt.*;
import java.util.ArrayList;

public class Food implements MapCreature {

    private ArrayList<Block> body = new ArrayList<>();
    private Block block;

    public static Color randomColor() {
        return Color.GREEN;
    }

    public Food(int x, int y, Color color) {
        block = new Block(x, y, color);
        body.add(block);
    }

    public Food(int x, int y) {
        block = new Block(x, y, randomColor());
        body.add(block);
    }

    public boolean isIn(Block nextBlock) {
        return block.isIn(nextBlock);
    }

    @Override
    public ArrayList<Block> getBody() {
        return body;
    }

    @Override
    public String toString() {
        return "Food {" + block + '}';
    }

    @Override
    public void recolor(Color color) {
        block.setColor(color);
    }
}
