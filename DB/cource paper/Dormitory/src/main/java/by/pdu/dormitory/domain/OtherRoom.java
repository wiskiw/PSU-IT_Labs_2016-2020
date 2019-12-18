package by.pdu.dormitory.domain;

import lombok.Data;

@Data
public class OtherRoom {
    private Long id;
    private String name;

    @Override
    public String toString() {
        return name;
    }
}
