package by.pdu.dormitory.domain;

import lombok.Data;

@Data
public class Room {
    private Long id;
    private Double square;
    private Long countBets;
    private Unit unit;

    public String toString(){
        return "Блок: "+unit.getNumber() +" койки: "+countBets;
    }
}
