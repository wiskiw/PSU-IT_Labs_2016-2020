package by.pdu.dormitory.ui.post;


import by.pdu.dormitory.domain.OtherRoom;
import by.pdu.dormitory.domain.Post;
import by.pdu.dormitory.domain.Property;
import by.pdu.dormitory.mapper.OtherRoomMapper;
import by.pdu.dormitory.mapper.PostMapper;
import by.pdu.dormitory.mapper.PropertyMapper;
import by.pdu.dormitory.ui.windows.TabController;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import by.pdu.dormitory.util.LoadFXML;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

public class PostController extends TabController {

    private TableView table;

    public PostController(TableView table) {
        super(table);
        this.table = table;
        ObservableList<TableColumn> columnsFaculty = table.getColumns();
        columnsFaculty.get(0).setCellValueFactory(new PropertyValueFactory<Post, Long>("id"));
        columnsFaculty.get(1).setCellValueFactory(new PropertyValueFactory<Post, String>("name"));
    }

    @Override
    public void add() {
        try {
            Stage stage = modalWindow("fxml/post/add.fxml","Добавить должность");
            Object data = stage.getUserData();
            if (data != null && (Integer) data == Window.CLICK_ADD) updateView();
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    @Override
    public void remove() {
        try {
            Post obj = (Post) table.getSelectionModel().getSelectedItem();
            if (obj != null) {
                PostMapper mapper = ctx.getBean("postMapper", PostMapper.class);
                mapper.deletePost(obj.getId());
            }else{
                AlertWindow.errorAlert("Выберите элемент");
            }
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    @Override
    public void updateView() {
        PostMapper postMapper = ctx.getBean("postMapper",PostMapper.class);
        ObservableList<Post> posts = FXCollections.observableArrayList(postMapper.getPost());
        table.setItems(posts);
    }

    @Override
    public void update() {
        try{
            Object obj = table.getSelectionModel().getSelectedItem();
            if (obj == null) {
                AlertWindow.errorAlert("Нет выбранного элемента");
                return;
            }
            Stage update = new Stage();
            LoadFXML loader = ctx.getBean("loader", LoadFXML.class);
            UpdateController controller = (UpdateController)loader.loadModal("fxml/post/update.fxml","Редактировать должность",update,stage);
            controller.setPost((Post) obj);
            update.showAndWait();
            Object data = update.getUserData();
            if (data != null && (Integer) data == Window.CLICK_EDIT) updateView();
        }catch (Exception ex){
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }
}
