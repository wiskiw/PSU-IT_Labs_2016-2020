package yablonski.a.model.input;

import java.awt.event.KeyEvent;

public class KeyEventController {

    private KeyEvent lastEvent = null;

    public void onKeyPress(KeyEvent event) {
        lastEvent = event;
    }

    public void tickUpdate() {
        lastEvent = null;
    }

    public boolean hasPress() {
        return lastEvent != null;
    }

    public KeyEvent getPressedKey() {
        return lastEvent;
    }


}
