package by.pdu.dormitory.mapper;

import by.pdu.dormitory.domain.Property;
import by.pdu.dormitory.domain.Unit;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface UnitMapper {
    List<Unit> getUnit();

    void insertUnit(Long number);

    void updateUnit(@Param("id") Long id, @Param("number") Long number);

    void deleteUnit(Long id);
}
