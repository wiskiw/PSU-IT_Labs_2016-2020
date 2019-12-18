package yablonski.a.model.map.items;

import java.awt.*;

// фигура кубика
public interface TetrisCreature extends MovableMapCreature {

    Color[] piecColors = {
            new Color(186, 146, 0),
            new Color(143, 186, 0),
            new Color(0, 186, 154),
            new Color(129, 0, 186)
    };

    //сдвинуть вниз
    void moveTetrisDown();

}
