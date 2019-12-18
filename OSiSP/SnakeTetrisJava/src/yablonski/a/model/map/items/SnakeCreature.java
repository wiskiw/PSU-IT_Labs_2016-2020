package yablonski.a.model.map.items;

import yablonski.a.model.Block;
import yablonski.a.model.Direction;

import java.awt.*;

public interface SnakeCreature extends MovableMapCreature {

    Color COLOR_HEAD = new Color(222, 215, 73);
    Color COLOR_BODY = new Color(222, 160, 64);

    // сдвинуть по направлению движения
    void moveSnake();

    // изменить направления движения
    void setMovingDirection(Direction direction);

    Block getHead();

    void setHead(Block snakeHead, Direction movingDirection);

}
