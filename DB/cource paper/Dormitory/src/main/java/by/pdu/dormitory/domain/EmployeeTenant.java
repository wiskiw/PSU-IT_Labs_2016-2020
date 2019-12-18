package by.pdu.dormitory.domain;

import lombok.Data;

@Data
public class EmployeeTenant extends Tenant {
    String work;
    {
        type = "Сотрудник";
    }
}
