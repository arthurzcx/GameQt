include(../cmake/qt.cmake)
project(GameFourInARow)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

qt5_add_big_resources(SOURCES main.qrc)
SOURCE_GROUP("qrc" ${SOURCES})

#set_target_properties(
#        GameFourInARow PROPERTIES
#        CMAKE_INCLUDE_CURRENT_DIR ON
#        CMAKE_AUTOMOC TRUE)

QT5_WRAP_CPP(
        MOC_FILES
        src/ChessView.h
        src/ChessAnimation.h
)

add_executable(
        GameFourInARow
        ${MOC_FILES}
        ${SOURCES}
        src/main.cpp
        src/ChessMan.cpp
        src/ChessBoard.cpp
        src/ChessView.cpp
        src/ChessAnimation.cpp
        src/ChessScene.cpp
        src/ChessAudio.cpp
        src/ChessPlayer.cpp
)
target_link_libraries(GameFourInARow
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Multimedia
)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME})
