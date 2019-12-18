package com.tetris.snake.wiskiw.snake_tetrisandroid.items;

import com.tetris.snake.wiskiw.snake_tetrisandroid.Block;
import com.tetris.snake.wiskiw.snake_tetrisandroid.Direction;

public interface MovableMapCreature extends MapCreature {

    Direction getMovingDirection();

    boolean addToBody(Block block);


}
