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

    QGraphicsScene scene;
    scene.setBackgroundBrush(Qt::white);

    ChessView view(&scene);
    view.setFrameStyle(0);
    view.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    view.show();
    return QApplication::exec();
}
