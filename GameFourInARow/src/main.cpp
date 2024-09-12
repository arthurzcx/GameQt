#include <QApplication>
#include <QPushButton>
#include <QSizePolicy>

#include "ChessMan.h"
#include "ChessBoard.h"
#include "ChessView.h"
#include "ChessScene.h"

using namespace GameFourInARow;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QGraphicsScene scene(0, 0, 500, 500);
    scene.setBackgroundBrush(Qt::white);

    ChessView view(&scene);
    view.setFrameStyle(0);
    view.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view.resize(500,500);
    view.setFixedSize(500,500);
    view.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    view.show();
    return QApplication::exec();
}
