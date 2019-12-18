package com.tetris.snake.wiskiw.snake_tetrisandroid.view;

public interface MainViewInterface {

    boolean updateSquare(int x, int y, int color);

    void updateScore(int score);

    void showMessage(String msg);

    void clearGameField();

}
