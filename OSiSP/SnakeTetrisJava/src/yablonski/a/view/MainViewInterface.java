package yablonski.a.view;

import javafx.util.Pair;

import java.awt.*;

public interface MainViewInterface {

    boolean updateSquare(int x, int y, Color color);

    void updateScore(int score);

    void showMessage(String msg);

    Pair<Integer, Integer> getGameFieldSize();

    void clearGameField();

}
