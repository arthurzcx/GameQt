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

#pragma once

#include <QGraphicsWidget>

namespace GameFourInARow {

    enum class ChessPlayer {
        None = 0,
        First,
        Second,
        Win
    };

    class ChessMan : public QGraphicsWidget {
    public:
        ChessMan(ChessPlayer player, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
        int getSize();
        void setSize(int size);

        void setChessPlayer(ChessPlayer type);
        ChessPlayer getChessPlayer();

        void setPosInit(const QPointF &pos);
        QPointF getPosInit() const;
        void setPosFinal(const QPointF &pos);
        QPointF getPosFinal() const;

    private:
        ChessPlayer player_ = ChessPlayer::First;
        int size_ = 40;

        QPointF pos_init_{};
        QPointF pos_final_{};
    };

} // GameFourInARow
