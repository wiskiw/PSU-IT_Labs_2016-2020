package by.pdu.dormitory.ui.post;

import by.pdu.dormitory.domain.Post;
import by.pdu.dormitory.domain.Property;
import by.pdu.dormitory.mapper.PostMapper;
import by.pdu.dormitory.mapper.PropertyMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.stage.Stage;


public class UpdateController extends SupportWindow {
    private Post post;

    @FXML
    private TextField nameText;

    @FXML
    private void update() {
        try {
            PostMapper postMapper = ctx.getBean("postMapper", PostMapper.class);
            postMapper.updatePost(post.getId(), nameText.getText());
            close(Window.CLICK_EDIT);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void setPost(Post post) {
        this.post = post;
        nameText.setText(post.getName());
    }
}
