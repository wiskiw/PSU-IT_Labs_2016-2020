package by.pdu.dormitory.domain;

import lombok.Data;

import java.sql.Date;
@Data
public abstract class Tenant {
    protected Long id;
    protected String FIO;
    protected Date birthday;
    protected Date checkDate;
    protected String type;
    protected Unit unit;
    protected Room room;
}
