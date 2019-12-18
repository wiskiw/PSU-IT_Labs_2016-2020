package com.tetris.snake.wiskiw.snake_tetrisandroid;

public interface SnakeTetrisCallback {

    void onGameUpdate(int score);

    void onGameOver(int score);
}
