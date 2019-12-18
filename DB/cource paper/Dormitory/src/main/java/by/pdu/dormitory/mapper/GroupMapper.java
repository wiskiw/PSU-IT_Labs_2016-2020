package by.pdu.dormitory.mapper;

import by.pdu.dormitory.domain.Group;
import by.pdu.dormitory.domain.Inventory;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface GroupMapper {
    List<Group> getGroup();

    void insertGroup(@Param("name") String name,@Param("facultyId") Long facultyId);

    void updateGroup(@Param("id") Long id, @Param("name") String name, @Param("facultyId") Long facultyId);

    void deleteGroup(Long id);
}
