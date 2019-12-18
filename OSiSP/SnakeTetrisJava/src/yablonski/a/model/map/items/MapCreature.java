package yablonski.a.model.map.items;

import yablonski.a.model.Block;

import java.awt.*;
import java.util.ArrayList;

public interface MapCreature {

    ArrayList<Block> getBody();

    void recolor(Color color);

}
