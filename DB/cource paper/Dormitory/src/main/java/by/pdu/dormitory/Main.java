package by.pdu.dormitory;

import by.pdu.dormitory.mapper.*;
import by.pdu.dormitory.ui.windows.Window;
import javafx.application.Application;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import by.pdu.dormitory.util.ApplicationContext;
import by.pdu.dormitory.util.ApplicationContextImpl;
import by.pdu.dormitory.util.LoadFXML;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.Reader;
import java.util.Properties;

public class Main extends Application {
    private ApplicationContext ctx;
    private LoadFXML loader;

    private void loadMappers(SqlSessionFactory sqlSessionFactory) {
        SqlSession session = sqlSessionFactory.openSession();
        ctx.inject(SqlSession.class, "session", session);

        InventoryMapper inventoryMapper = session.getMapper(InventoryMapper.class);
        ctx.inject(InventoryMapper.class, "inventoryMapper", inventoryMapper);

        FacultyMapper facultyMapper = session.getMapper(FacultyMapper.class);
        ctx.inject(FacultyMapper.class, "facultyMapper", facultyMapper);

        PropertyMapper propertyMapper = session.getMapper(PropertyMapper.class);
        ctx.inject(PropertyMapper.class, "propertyMapper", propertyMapper);

        PostMapper postMapper = session.getMapper(PostMapper.class);
        ctx.inject(PostMapper.class, "postMapper", postMapper);

        OtherRoomMapper otherRoomMapper = session.getMapper(OtherRoomMapper.class);
        ctx.inject(OtherRoomMapper.class, "otherRoomMapper", otherRoomMapper);

        UnitMapper unitMapper = session.getMapper(UnitMapper.class);
        ctx.inject(UnitMapper.class, "unitMapper", unitMapper);

        GroupMapper groupMapper = session.getMapper(GroupMapper.class);
        ctx.inject(GroupMapper.class, "groupMapper", groupMapper);

        RoomMapper roomMapper = session.getMapper(RoomMapper.class);
        ctx.inject(RoomMapper.class, "roomMapper", roomMapper);

        EmployeeMapper employeeMapper = session.getMapper(EmployeeMapper.class);
        ctx.inject(EmployeeMapper.class, "employeeMapper", employeeMapper);

        TenantMapper tenantMapper = session.getMapper(TenantMapper.class);
        ctx.inject(TenantMapper.class, "tenantMapper", tenantMapper);
    }

    private void initialize() throws IOException {
        ctx = new ApplicationContextImpl();
        loader = new LoadFXML(ctx);
        ctx.inject(LoadFXML.class, "loader", loader);

        Properties properties = new Properties();
        Reader inputStream = Resources.getResourceAsReader("mybatis-config.xml");
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream, properties);
        sqlSessionFactory.openSession().getConnection();

        ctx.inject(SqlSessionFactory.class, "sqlSessionFactory", sqlSessionFactory);
        loadMappers(sqlSessionFactory);
    }

    @Override
    public void start(Stage primaryStage) throws Exception{
        initialize();
        loader.load("fxml/main.fxml", "Меню", primaryStage);
        primaryStage.getIcons().add(new Image("img/icon.jpg"));
        primaryStage.centerOnScreen();
        primaryStage.show();

        primaryStage.setOnCloseRequest(we -> {
            SqlSession session = ctx.getBean("session", SqlSession.class);
            if (session != null) {
                session.close();
            }
        });
    }

    public static void main(String[] args) {
        launch(args);
    }
}
