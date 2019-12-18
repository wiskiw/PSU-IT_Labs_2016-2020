package by.pdu.dormitory.domain;

import lombok.Data;

@Data
public class Unit {
    private Long number;

    @Override
    public String toString() {
        return number.toString();
    }
}
