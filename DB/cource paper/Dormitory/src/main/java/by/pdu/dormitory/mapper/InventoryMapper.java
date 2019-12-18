package by.pdu.dormitory.mapper;


import by.pdu.dormitory.domain.Inventory;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface InventoryMapper {
    List<Inventory> getInventory();

    void insertInventory(@Param("name")String name);

    void updateInventory(@Param("id") Long id,@Param("name") String name);

    void deleteInventory(Long id);

}
