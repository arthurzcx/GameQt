//
// Created by arthur on 9/11/24.
//

#include "ChessScene.h"

#include <QBrush>
#include <QPainter>

namespace GameFourInARow {

    ChessScene::ChessScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
            QGraphicsScene(x, y, width, height, parent) {
        setBackgroundBrush(Qt::green);
    }

//    void ChessScene::drawBackground(QPainter *painter, const QRectF &rect) {
//        auto brush = painter->brush();
//        brush.setColor(Qt::green);
//        painter->drawRect(rect);
//        setBackgroundBrush(Qt::green);
//    }

}