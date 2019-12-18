package by.pdu.dormitory.domain;

import lombok.Data;

@Data
public class Employee {
    private Long id;
    private String FIO;
    private Post post;
    private OtherRoom otherRoom;
}
