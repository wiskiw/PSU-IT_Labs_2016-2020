package yablonski.a.presenter;

import yablonski.a.model.SnakeTetris;
import yablonski.a.model.SnakeTetrisCallback;
import yablonski.a.model.input.KeyEventController;
import yablonski.a.view.MainViewInterface;

import java.awt.event.KeyEvent;

public class MainPresenter implements SnakeTetrisCallback {

    private MainViewInterface view;

    private SnakeTetris snakeTetris;
    private KeyEventController keyEventController;

    public MainPresenter(MainViewInterface view, int mapWidth, int mapHeight) {
        this.view = view;
        this.keyEventController = new KeyEventController();
        this.snakeTetris = new SnakeTetris(this, mapWidth, mapHeight, true);
    }

    public void onKeyPress(KeyEvent event) {
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
        snakeTetris.getBlocksToDraw().forEach(block ->
                view.updateSquare(block.getX(), block.getY(), block.getColor()));
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
