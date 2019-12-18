package by.pdu.dormitory.mapper;

import by.pdu.dormitory.domain.OtherRoom;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface OtherRoomMapper {
    List<OtherRoom> getOtherRoom();

    void insertOtherRoom(String name);

    void updateOtherRoom(@Param("id") Long id, @Param("name") String name);

    void deleteOtherRoom(Long id);
}
