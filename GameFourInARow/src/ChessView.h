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

#include "ChessBoard.h"
#include "ChessMan.h"
#include "ChessPlayer.h"
#include <QGraphicsView>
#include <vector>

namespace GameFourInARow {

    class ChessView : public QGraphicsView {
    Q_OBJECT
    public:
        ChessView(QGraphicsScene *scene, QWidget *parent = NULL);

    private:
        void init();
        void initHeadMan();

    protected:
        void resizeEvent(QResizeEvent *event) override;
        bool event(QEvent *event) override;

    private:
        ChessPlayer player_cur_ = ChessPlayer::First;
        ChessMan *head_man_ = nullptr;
        QGraphicsTextItem *head_text_ = nullptr;
        ChessPlayerIcon *player_icon_ = nullptr;
        ChessBoard *board_ = nullptr;
        std::vector<ChessBoard::Grid> winner_grids_{};
    };

}