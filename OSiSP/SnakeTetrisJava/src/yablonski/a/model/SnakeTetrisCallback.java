package yablonski.a.model;

public interface SnakeTetrisCallback {

    void onGameUpdate(int score);

    void onGameOver(int score);
}
