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

#include "ChessMan.h"
#include <QGraphicsWidget>

namespace GameFourInARow {
    class ChessBoard : public QGraphicsWidget {
    public:
        ChessBoard(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
        ~ChessBoard();

        struct Grid {
            int x_ = 0;
            int y_ = 0;
            int size_ = 50;
            int row_ = 0;
            int col_ = 0;
            ChessPlayer player_ = ChessPlayer::None;

            Grid() :
                    x_(0), y_(0), size_(50), player_(ChessPlayer::None) {}
            Grid(int x, int y, int size, ChessPlayer player) :
                    x_(x), y_(y), size_(size), player_(player) {}
        };

    public:
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

        void setGridSize(int grid_size);
        int getGridSize();
        QPoint getGridPos(const Grid &grid);
        QPoint getGridPosInit(const Grid &grid);
        void setBoardSize(int pos_x, int pos_y, int size);

        bool getGridAvailable(const QPoint &pos, Grid &grid, ChessPlayer type);
        bool isPlayerWin(const Grid &grid, ChessPlayer type, std::vector<Grid> &win_grids);
        /// After the function isPlayerWin(...) called, and then you can call this function to verify if it is a draw.
        bool isMatchDraw();

    private:
        bool isHorizontalWin(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids);
        bool isVerticalWin(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids);
        bool isNegative45Win(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids);
        bool isPositive45Win(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids);

    private:
        QPoint pos_;
        QSize size_;
        int rows_ = 8;
        int cols_ = 8;
        int grid_size_ = 50;
        int space_ = 5;
        std::vector<std::vector<Grid>> grids_{};
    };
}