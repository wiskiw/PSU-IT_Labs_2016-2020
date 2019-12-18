package by.pdu.dormitory.ui;

import by.pdu.dormitory.mapper.EmployeeMapper;
import by.pdu.dormitory.ui.employee.EmployeeController;
import by.pdu.dormitory.ui.faculty.FacultyController;
import by.pdu.dormitory.ui.group.GroupController;
import by.pdu.dormitory.ui.inventory.InventoryController;
import by.pdu.dormitory.ui.otherRoom.OtherRoomController;
import by.pdu.dormitory.ui.post.PostController;
import by.pdu.dormitory.ui.property.PropertyController;
import by.pdu.dormitory.ui.room.RoomController;
import by.pdu.dormitory.ui.tenant.TenantController;
import by.pdu.dormitory.ui.unit.UnitController;
import by.pdu.dormitory.ui.windows.TabController;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.ApplicationContext;
import javafx.fxml.FXML;
import javafx.scene.control.TableView;


public class MainController extends Window {

    @FXML
    private TableView tenantTable,inventoryTable, facultyTable, propertyTable, postTable, otherTable, unitTable, groupTable, roomTable, employeeTable;

    @Override
    public void setApplicationContext(ApplicationContext ctx) {
        super.setApplicationContext(ctx);
        InventoryController inventoryController = new InventoryController(inventoryTable);
        inventoryController.setApplicationContext(ctx);
        inventoryController.setStage(stage);
        ctx.inject(InventoryController.class, "inventoryController", inventoryController);

        FacultyController facultyController = new FacultyController(facultyTable);
        facultyController.setApplicationContext(ctx);
        facultyController.setStage(stage);
        ctx.inject(FacultyController.class, "facultyController", facultyController);

        PropertyController propertyController = new PropertyController(propertyTable);
        propertyController.setApplicationContext(ctx);
        propertyController.setStage(stage);
        ctx.inject(PropertyController.class, "propertyController", propertyController);

        PostController postController = new PostController(postTable);
        postController.setApplicationContext(ctx);
        postController.setStage(stage);
        ctx.inject(PostController.class, "postController", postController);

        OtherRoomController otherRoomController = new OtherRoomController(otherTable);
        otherRoomController.setApplicationContext(ctx);
        otherRoomController.setStage(stage);
        ctx.inject(OtherRoomController.class, "otherRoomController", otherRoomController);

        UnitController unitController = new UnitController(unitTable);
        unitController.setApplicationContext(ctx);
        unitController.setStage(stage);
        ctx.inject(UnitController.class, "unitController", unitController);

        GroupController groupController = new GroupController(groupTable);
        groupController.setApplicationContext(ctx);
        groupController.setStage(stage);
        ctx.inject(GroupController.class, "groupController", groupController);

        RoomController roomController = new RoomController(roomTable);
        roomController.setApplicationContext(ctx);
        roomController.setStage(stage);
        ctx.inject(RoomController.class, "roomController", roomController);

        EmployeeController employeeController = new EmployeeController(employeeTable);
        employeeController.setApplicationContext(ctx);
        employeeController.setStage(stage);
        ctx.inject(EmployeeController.class, "employeeController", employeeController);

        TenantController tenantController = new TenantController(tenantTable);
        tenantController.setApplicationContext(ctx);
        tenantController.setStage(stage);
        ctx.inject(TenantController.class, "tenantController", tenantController);

        update();
    }

    @FXML
    private void addInventory() {
        InventoryController inventoryController = ctx.getBean("inventoryController", InventoryController.class);
        inventoryController.add();
    }

    @FXML
    private void updateInventory() {
        InventoryController inventoryController = ctx.getBean("inventoryController", InventoryController.class);
        inventoryController.update();
        update();
    }

    @FXML
    private void removeInventory() {
        InventoryController inventoryController = ctx.getBean("inventoryController", InventoryController.class);
        inventoryController.remove();
        update();
    }

    @FXML
    private void addFaculty() {
        FacultyController facultyController = ctx.getBean("facultyController", FacultyController.class);
        facultyController.add();
    }

    @FXML
    private void updateFaculty() {
        FacultyController facultyController = ctx.getBean("facultyController", FacultyController.class);
        facultyController.update();
        update();
    }

    @FXML
    private void removeFaculty() {
        FacultyController facultyController = ctx.getBean("facultyController", FacultyController.class);
        facultyController.remove();
        update();
    }

    @FXML
    private void addProperty() {
        PropertyController propertyController = ctx.getBean("propertyController", PropertyController.class);
        propertyController.add();
    }

    @FXML
    private void updateProperty() {
        PropertyController propertyController = ctx.getBean("propertyController", PropertyController.class);
        propertyController.update();
        update();
    }

    @FXML
    private void removeProperty() {
        PropertyController propertyController = ctx.getBean("propertyController", PropertyController.class);
        propertyController.remove();
        update();
    }

    @FXML
    private void addPost() {
        PostController postController = ctx.getBean("postController", PostController.class);
        postController.add();
    }

    @FXML
    private void updatePost() {
        PostController postController = ctx.getBean("postController", PostController.class);
        postController.update();
        update();
    }

    @FXML
    private void removePost() {
        PostController postController = ctx.getBean("postController", PostController.class);
        postController.remove();
        update();
    }

    @FXML
    private void addOtherRoom() {
        OtherRoomController otherRoomController = ctx.getBean("otherRoomController", OtherRoomController.class);
        otherRoomController.add();
    }

    @FXML
    private void updateOtherRoom() {
        OtherRoomController otherRoomController = ctx.getBean("otherRoomController", OtherRoomController.class);
        otherRoomController.update();
        update();
    }

    @FXML
    private void removeOtherRoom() {
        OtherRoomController otherRoomController = ctx.getBean("otherRoomController", OtherRoomController.class);
        otherRoomController.remove();
        update();
    }

    @FXML
    private void addUnit() {
        UnitController unitController = ctx.getBean("unitController", UnitController.class);
        unitController.add();
    }

    @FXML
    private void updateUnit() {
        UnitController unitController = ctx.getBean("unitController", UnitController.class);
        unitController.update();
        update();
    }

    @FXML
    private void removeUnit() {
        UnitController unitController = ctx.getBean("unitController", UnitController.class);
        unitController.remove();
        update();
    }

    @FXML
    private void addGroup() {
        GroupController groupController = ctx.getBean("groupController", GroupController.class);
        groupController.add();
    }

    @FXML
    private void updateGroup() {
        GroupController groupController = ctx.getBean("groupController", GroupController.class);
        groupController.update();
        update();
    }

    @FXML
    private void removeGroup() {
        GroupController groupController = ctx.getBean("groupController", GroupController.class);
        groupController.remove();
        update();
    }

    @FXML
    private void addRoom() {
        RoomController roomController = ctx.getBean("roomController", RoomController.class);
        roomController.add();
    }

    @FXML
    private void updateRoom() {
        RoomController roomController = ctx.getBean("roomController", RoomController.class);
        roomController.update();
        update();
    }

    @FXML
    private void removeRoom() {
        RoomController roomController = ctx.getBean("roomController", RoomController.class);
        roomController.remove();
        update();
    }

    @FXML
    private void addEmployee() {
        EmployeeController employeeController = ctx.getBean("employeeController", EmployeeController.class);
        employeeController.add();
    }

    @FXML
    private void updateEmployee() {
        EmployeeController employeeController = ctx.getBean("employeeController", EmployeeController.class);
        employeeController.update();
        update();
    }

    @FXML
    private void removeEmployee() {
        EmployeeController employeeController = ctx.getBean("employeeController", EmployeeController.class);
        employeeController.remove();
        update();
    }

    @FXML
    private void addTenant() {
        TenantController tenantController = ctx.getBean("tenantController", TenantController.class);
        tenantController.add();
    }

    @FXML
    private void updateTenant() {
        TenantController tenantController = ctx.getBean("tenantController", TenantController.class);
        tenantController.update();
        update();
    }

    @FXML
    private void removeTenant() {
        TenantController tenantController = ctx.getBean("tenantController", TenantController.class);
        tenantController.remove();
        update();
    }


    public void update() {
        for (TabController controller : ctx.getBeans(TabController.class)) {
            controller.updateView();
        }
    }
}