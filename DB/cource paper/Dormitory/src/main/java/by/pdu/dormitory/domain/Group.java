package by.pdu.dormitory.domain;

import lombok.Data;

@Data
public class Group {
    private Long id;
    private String name;
    private Faculty faculty;

    public String toString(){
        return name;
    }
}
