package by.pdu.dormitory.domain;

import lombok.Data;

@Data
public class Post {
    private Long id;
    private String name;

    @Override
    public String toString() {
        return name;
    }
}
