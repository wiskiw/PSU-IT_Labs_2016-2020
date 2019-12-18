package com.tetris.snake.wiskiw.snake_tetrisandroid.items;

import android.graphics.Color;

import com.tetris.snake.wiskiw.snake_tetrisandroid.Block;
import com.tetris.snake.wiskiw.snake_tetrisandroid.Direction;

public interface SnakeCreature extends MovableMapCreature {

    int COLOR_HEAD = Color.rgb(222, 215, 73);
    int COLOR_BODY = Color.rgb(222, 160, 64);

    // сдвинуть по направлению движения
    void moveSnake();

    // изменить направления движения
    void setMovingDirection(Direction direction);

    Block getHead();

    void setHead(Block snakeHead, Direction movingDirection);

}
