package com.tetris.snake.wiskiw.snake_tetrisandroid.items;

import com.tetris.snake.wiskiw.snake_tetrisandroid.Block;

import java.util.ArrayList;

public interface MapCreature {

    ArrayList<Block> getBody();

    void recolor(int color);

}
