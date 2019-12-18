package com.tetris.snake.wiskiw.snake_tetrisandroid.items;

import android.graphics.Color;


// фигура кубика
public interface TetrisCreature extends MovableMapCreature {

    int[] piecColors = {
            Color.rgb(186, 146, 0),
            Color.rgb(143, 186, 0),
            Color.rgb(0, 186, 154),
            Color.rgb(129, 0, 186)
    };

    //сдвинуть вниз
    void moveTetrisDown();

}
