package com.tetris.snake.wiskiw.snake_tetrisandroid.items;

import android.graphics.Color;

import com.tetris.snake.wiskiw.snake_tetrisandroid.Block;

import java.util.ArrayList;

public class Food implements MapCreature {

    private ArrayList<Block> body = new ArrayList<>();
    private Block block;

    public static int randomColor() {
        return Color.GREEN;
    }

    public Food(int x, int y, int color) {
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
    public void recolor(int color) {
        block.setColor(color);
    }
}
