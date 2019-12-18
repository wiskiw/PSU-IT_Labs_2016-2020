package by.pdu.dormitory.domain;

import lombok.Data;

@Data
public class Faculty {
    private Long id;
    private String name;

    @Override
    public String toString() {
        return name;
    }
}
