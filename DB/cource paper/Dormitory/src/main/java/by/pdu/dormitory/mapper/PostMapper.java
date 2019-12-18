package by.pdu.dormitory.mapper;

import by.pdu.dormitory.domain.Post;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface PostMapper {
    List<Post> getPost();

    void insertPost(String name);

    void updatePost(@Param("id") Long id, @Param("name") String name);

    void deletePost(Long id);
}
