//
// Created by arthur on 9/6/24.
//

#pragma once

#include "ChessMan.h"

#include <QGraphicsWidget>

namespace GameFourInARow {
    class ChessBoard : public QGraphicsWidget {
    public:
        ~ChessBoard();

        struct Grid {
            int x_ = 0;
            int y_ = 0;
        };

    public:
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

        void setGridSize(int grid_size);
        int getGridSize();
        QPoint getGridPos(const Grid &grid);
        QPoint getGridPosInit(const Grid &grid);

        bool getGridAvailable(const QPoint &pos, Grid &grid, ChessPlayer type);
        bool isPlayerWin(const Grid &grid, ChessPlayer type, std::vector<Grid> &win_grids);
        /// Warning: After the function isPlayerWin(...) called, and then you can call this function to verify if it is a draw.
        bool isMatchDraw();

    private:
        bool isHorizontalWin(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids);
        bool isVerticalWin(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids);
        bool isNegative45Win(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids);
        bool isPositive45Win(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids);

    private:
        int rows_ = 8;
        int cols_ = 8;
        int grid_size_ = 50;
        ChessPlayer *arr_chess_ = nullptr;
    };
}