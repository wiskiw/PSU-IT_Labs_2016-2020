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
        modules/enemy/units/Painter/Painter.h
        ui/UI.cpp ui/UI.h
        modules/enemy/units/EnemyConfigurator.cpp
        modules/enemy/units/EnemyConfigurator.h
        modules/enemy/units/Aimer/Aimer.h
        modules/enemy/units/Painter/Painter.cpp
        modules/enemy/units/Mover/Mover.cpp
        modules/enemy/units/Aimer/Aimer.cpp
        gp-elements/gun/gpeGun.cpp
        gp-elements/gun/gpeGun.h
        gp-elements/gun/list/gun-list.cpp
        gp-elements/bullet/list/bullet-list.cpp
        gp-elements/bullet/list/bullet-list.h
        gp-elements/gun/list/gun-list.h
        modules/drop/ModuleDrop.cpp
        modules/drop/ModuleDrop.h
        modules/drop/utils/Painter/Painter.cpp
        modules/drop/utils/Painter/Painter.h
        modules/drop/utils/Action/Action.cpp
        modules/drop/utils/Action/Action.h
        modules/drop/utils/DropConfigurator.cpp
        modules/drop/utils/DropConfigurator.h
        ui/dialog/Dialog.cpp
        ui/dialog/Dialog.h
        resources/MusicManager.cpp
        resources/MusicManager.h
        resources/SoundManager.cpp
        resources/SoundManager.h)

add_executable(Course_Paper ${SOURCE_FILES})


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Course_Paper ${SFML_LIBRARIES})
endif ()