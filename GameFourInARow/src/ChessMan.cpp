//
// Created by arthur on 9/6/24.
//

#include "ChessMan.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

namespace GameFourInARow {
    ChessMan::ChessMan(ChessPlayer player, QGraphicsItem *parent, Qt::WindowFlags wFlags)
            : QGraphicsWidget(parent, wFlags), player_(player) {
        setMaximumSize(size_, size_);
    }

    void ChessMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        painter->setRenderHint(QPainter::Antialiasing);
        auto pen = painter->pen();
        auto color = (player_ == ChessPlayer::First ? Qt::red : Qt::blue);
        if (player_ == ChessPlayer::Win) {
            color = Qt::white;
        }
        pen.setColor(color);
        painter->setPen(pen);
        painter->setBrush(color);

        auto rt = rect();
        auto center = rt.center();
        auto size = std::min(rt.width(), rt.height()) / (player_ == ChessPlayer::Win ? 2.0 : 1.0);
        rt.setX(center.x() - size / 2);
        rt.setY(center.y() - size / 2);
        rt.setWidth(size);
        rt.setHeight(size);
        painter->drawEllipse(rt);
    }

    void ChessMan::setChessPlayer(ChessPlayer type) {
        player_ = type;
        update();
    }
    ChessPlayer ChessMan::getChessPlayer() {
        return player_;
    }
    int ChessMan::getSize() {
        return size_;
    }

    void ChessMan::setPosInit(const QPointF &pos) {
        pos_init_ = pos;
    }
    QPointF ChessMan::getPosInit() const {
        return pos_init_;
    }
    void ChessMan::setPosFinal(const QPointF &pos) {
        pos_final_ = pos;
    }
    QPointF ChessMan::getPosFinal() const {
        return pos_final_;
    }
} // GameFourInARow
