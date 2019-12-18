package by.pdu.dormitory.ui.otherRoom;

import by.pdu.dormitory.domain.OtherRoom;
import by.pdu.dormitory.domain.Post;
import by.pdu.dormitory.mapper.OtherRoomMapper;
import by.pdu.dormitory.mapper.PostMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;


public class UpdateController extends SupportWindow {
    private OtherRoom otherRoom;

    @FXML
    private TextField nameText;

    @FXML
    private void update() {
        try {
            OtherRoomMapper otherRoomMapper = ctx.getBean("otherRoomMapper", OtherRoomMapper.class);
            otherRoomMapper.updateOtherRoom(otherRoom.getId(), nameText.getText());
            close(Window.CLICK_EDIT);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void setOtherRoom(OtherRoom otherRoom) {
        this.otherRoom = otherRoom;
        nameText.setText(otherRoom.getName());
    }
}
