package by.pdu.dormitory.mapper;


import by.pdu.dormitory.domain.Faculty;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface FacultyMapper {
    List<Faculty> getFaculty();

    void insertFaculty(String name);

    void updateFaculty(@Param("id") Long id,@Param("name") String name);

    void deleteFaculty(Long id);
}
