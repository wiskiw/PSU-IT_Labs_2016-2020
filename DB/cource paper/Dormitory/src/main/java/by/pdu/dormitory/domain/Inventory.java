package by.pdu.dormitory.domain;

import lombok.Data;

import java.util.Objects;

@Data
public class Inventory {
    private Long id;
    private String name;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Inventory inventory = (Inventory) o;
        return Objects.equals(id, inventory.id);
    }


}
