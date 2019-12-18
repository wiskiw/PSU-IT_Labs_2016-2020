package by.pdu.dormitory.mapper;

import by.pdu.dormitory.domain.EmployeeTenant;
import by.pdu.dormitory.domain.Student;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface TenantMapper {
    List<Student> getStudent();

    List<EmployeeTenant> getEmployeeTenant();

    void insertStudent(@Param("number") Long number, @Param("birthday") String birthday, @Param("fio") String fio,@Param("roomId")  Long roomId, @Param("groupId") Long groupId);

    void insertEmployeeTenant(@Param("number") Long number, @Param("birthday") String birthday, @Param("fio") String fio, @Param("roomId")  Long roomId, @Param("work") String work);

    void insertProperty(@Param("number") Long number, @Param("propId") Long propId);

    void removeProperty(@Param("number") Long number);

    void updateEmployeeTenant(@Param("number") Long number, @Param("birthday") String birthday, @Param("fio") String fio, @Param("roomId")  Long roomId, @Param("work") String work);

    void updateStudent(@Param("number") Long number, @Param("birthday") String birthday, @Param("fio") String fio,@Param("roomId")  Long roomId, @Param("groupId") Long groupId);

    void deleteTenant(Long id);
}
