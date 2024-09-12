//
// Created by arthur on 9/11/24.
//

#pragma once

#include <QGraphicsScene>

namespace GameFourInARow {
    class ChessScene : public QGraphicsScene {
    public:
        ChessScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

//        void drawBackground(QPainter *painter, const QRectF &rect) override;
    };

}