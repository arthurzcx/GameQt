include(../cmake/qt.cmake)
project(GameFourInARow)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

QT5_WRAP_CPP(
        MOC_FILES
        src/ChessView.h
        src/ChessAnimation.h
)

add_executable(
        GameFourInARow
        ${MOC_FILES}
        src/main.cpp
        src/ChessMan.cpp
        src/ChessBoard.cpp
        src/ChessView.cpp
        src/ChessAnimation.cpp
        src/ChessScene.cpp
)
target_link_libraries(GameFourInARow
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME})
