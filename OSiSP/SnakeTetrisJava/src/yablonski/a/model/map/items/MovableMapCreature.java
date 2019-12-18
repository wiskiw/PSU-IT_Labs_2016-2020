package yablonski.a.model.map.items;

import yablonski.a.model.Block;
import yablonski.a.model.Direction;

import java.util.ArrayList;

public interface MovableMapCreature extends MapCreature {

    Direction getMovingDirection();

    boolean addToBody(Block block);


}
