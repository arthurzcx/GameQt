/*
 * Copyright (C) 2024 Arthur Zhang <arthur.zhang.cx@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
        auto size = size_ / (player_ == ChessPlayer::Win ? 2.0 : 1.0);
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
    void ChessMan::setSize(int size) {
        size_ = size;
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
