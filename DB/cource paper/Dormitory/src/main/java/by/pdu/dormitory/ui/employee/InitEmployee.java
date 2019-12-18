package by.pdu.dormitory.ui.employee;

import by.pdu.dormitory.domain.OtherRoom;
import by.pdu.dormitory.domain.Post;
import by.pdu.dormitory.mapper.OtherRoomMapper;
import by.pdu.dormitory.mapper.PostMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.util.ApplicationContext;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;

public class InitEmployee extends SupportWindow {
    @FXML
    protected TextField nameText;

    @FXML
    protected ComboBox postBox,otherRoomBox;

    @Override
    public void setApplicationContext(ApplicationContext ctx) {
        super.setApplicationContext(ctx);
        PostMapper postMapper = ctx.getBean("postMapper",PostMapper.class);
        ObservableList<Post> posts = FXCollections.observableArrayList(postMapper.getPost());
        postBox.setItems(posts);

        OtherRoomMapper otherRoomMapper = ctx.getBean("otherRoomMapper",OtherRoomMapper.class);
        ObservableList<OtherRoom> otherRooms = FXCollections.observableArrayList(otherRoomMapper.getOtherRoom());
        otherRoomBox.setItems(otherRooms);
    }
}
