package by.pdu.dormitory.domain;

import lombok.Data;
import lombok.EqualsAndHashCode;

@EqualsAndHashCode(callSuper = true)
@Data
public class Student extends Tenant {
    private Group group;
    {
        type = "Студент";
    }
}
