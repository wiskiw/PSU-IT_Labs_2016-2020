package com.tetris.snake.wiskiw.snake_tetrisandroid.presenter;

import com.tetris.snake.wiskiw.snake_tetrisandroid.Block;
import com.tetris.snake.wiskiw.snake_tetrisandroid.SnakeTetris;
import com.tetris.snake.wiskiw.snake_tetrisandroid.SnakeTetrisCallback;
import com.tetris.snake.wiskiw.snake_tetrisandroid.input.ControlButton;
import com.tetris.snake.wiskiw.snake_tetrisandroid.input.KeyEventController;
import com.tetris.snake.wiskiw.snake_tetrisandroid.view.MainViewInterface;

public class MainPresenter implements SnakeTetrisCallback {

    private MainViewInterface view;

    private SnakeTetris snakeTetris;
    private KeyEventController keyEventController;

    public MainPresenter(MainViewInterface view, int mapWidth, int mapHeight) {
        this.view = view;
        this.keyEventController = new KeyEventController();
        this.snakeTetris = new SnakeTetris(this, mapWidth, mapHeight, false);
    }

    public void onKeyPress(ControlButton event) {
        keyEventController.onKeyPress(event);
    }

    public void tickUpdate() {
        if (keyEventController.hasPress()) {
            snakeTetris.onKeyPress(keyEventController.getPressedKey());
        }
        keyEventController.tickUpdate();
        snakeTetris.update();
    }

    private void redrawMap() {
        view.clearGameField();
        for (Block block : snakeTetris.getBlocksToDraw()) {
            view.updateSquare(block.getX(), block.getY(), block.getColor());
        }
    }


    @Override
    public void onGameUpdate(int score) {
        redrawMap();
        view.updateScore(score);
    }

    @Override
    public void onGameOver(int score) {
        view.showMessage("Game Over! Your score: " + score);
    }
}
