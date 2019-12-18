package by.pdu.dormitory.mapper;

import by.pdu.dormitory.domain.Inventory;
import by.pdu.dormitory.domain.Room;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface RoomMapper {
    List<Room> getRoom();

    void insertRoom(@Param("id") Long id,@Param("square")Double square,@Param("countBets") Long countBets,@Param("unitId") Long unitId);

    void updateRoom(@Param("id") Long id,@Param("square")Double square,@Param("countBets") Long countBets,@Param("unitId") Long unitId);

    void deleteRoom(Long id);

    Long nextId();

    void insertInventory(@Param("roomId") Long roomId,@Param("inventoryId") Long inventoryId);

    void deleteInventory(@Param("roomId") Long roomId);

    List<Inventory> getInventory(Long id);

}
