package by.pdu.dormitory.mapper;

import by.pdu.dormitory.domain.Employee;
import by.pdu.dormitory.domain.Faculty;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface EmployeeMapper {
    List<Employee> getEmployee();

    void insertEmployee(@Param("FIO") String FIO,@Param("postId") Long postId,@Param("otherRoomId") Long otherRoomId);

    void updateEmployee(@Param("id") Long id, @Param("FIO") String FIO,@Param("postId") Long postId,@Param("otherRoomId") Long otherRoomId);

    void deleteEmployee(Long id);
}
