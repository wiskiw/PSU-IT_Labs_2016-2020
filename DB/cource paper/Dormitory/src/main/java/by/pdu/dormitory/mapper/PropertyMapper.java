package by.pdu.dormitory.mapper;

import by.pdu.dormitory.domain.Property;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface PropertyMapper {
    List<Property> getProperty();

    void insertProperty(String name);

    void updateProperty(@Param("id") Long id, @Param("name") String name);

    List<Property> getPropertyTenant(Long id);

    void deleteProperty(Long id);
}
