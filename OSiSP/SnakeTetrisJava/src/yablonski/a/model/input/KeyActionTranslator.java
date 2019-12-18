package yablonski.a.model.input;

import java.awt.event.KeyEvent;

public class KeyActionTranslator {

    public interface Callback {

        void goUp();

        void goDown();

        void goRight();

        void goLeft();

        void action();

    }

    private static final int KEY_CODE_UP = 38;
    private static final int KEY_CODE_DOWN = 40;
    private static final int KEY_CODE_RIGHT = 39;
    private static final int KEY_CODE_LEFT = 37;
    private static final int KEY_CODE_ACTION = 32; // space

    private Callback callback;

    public KeyActionTranslator(Callback callback) {
        this.callback = callback;
    }

    public void process(KeyEvent event) {
        switch (event.getKeyCode()) {
            case KEY_CODE_UP:
                callback.goUp();
                break;
            case KEY_CODE_DOWN:
                callback.goDown();
                break;
            case KEY_CODE_RIGHT:
                callback.goRight();
                break;
            case KEY_CODE_LEFT:
                callback.goLeft();
                break;
            case KEY_CODE_ACTION:
                callback.action();
                break;
        }
    }


}
