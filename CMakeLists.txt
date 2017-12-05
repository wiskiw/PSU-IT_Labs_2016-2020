cmake_minimum_required(VERSION 3.8)
project(Course_Paper)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        GameStructs.h
        modules/player/ModulePlayer.cpp
        modules/player/ModulePlayer.h
        io/IOProcessor.cpp io/IOProcessor.h
        modules/background/ModuleBackground.cpp
        modules/background/ModuleBackground.h
        modules/bullets/ModuleBullet.cpp
        modules/bullets/ModuleBullet.h
        PREFERENCES.h
        modules/enemy/ModulEnemy.cpp
        modules/enemy/ModulEnemy.h
        utils/Utils.cpp utils/Utils.h
        modules/enemy/units/Drawer/Painter.h
        ui/UI.cpp ui/UI.h
        modules/enemy/units/EnemyGenerator.cpp
        modules/enemy/units/EnemyGenerator.h
        modules/enemy/units/Aimer/Aimer.h
        modules/enemy/units/Drawer/Painter.cpp
        modules/enemy/units/Mover/Mover.cpp
        modules/enemy/units/Aimer/Aimer.cpp
        gp-elements/gun/gpeGun.cpp
        gp-elements/gun/gpeGun.h
        gp-elements/gun/list/gun-list.cpp
        gp-elements/bullet/list/bullet-list.cpp
        gp-elements/bullet/list/bullet-list.h
        gp-elements/gun/list/gun-list.h)

add_executable(Course_Paper ${SOURCE_FILES})


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})