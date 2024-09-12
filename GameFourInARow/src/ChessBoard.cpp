//
// Created by arthur on 9/6/24.
//

#include "ChessBoard.h"

#include <QPainter>
#include <QDebug>

namespace GameFourInARow {
    ChessBoard::~ChessBoard() {
        delete[] arr_chess_;
    }

    void ChessBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        painter->setRenderHint(QPainter::Antialiasing);
        auto pen = painter->pen();
        pen.setWidth(3);
        pen.setColor(Qt::green);
        painter->setBrush(Qt::green);
        painter->setPen(pen);

        auto rt = rect();
        rows_ = rt.width() / grid_size_;
        cols_ = rt.height() / grid_size_;
        if (!arr_chess_) {
            arr_chess_ = new ChessPlayer[rows_ * cols_];
            memset(arr_chess_, 0x00, rows_ * cols_ * sizeof(ChessPlayer));
        }

        painter->drawRoundedRect(rt,20,20);

        painter->setBrush(Qt::white);
        for (auto y = 0; y < rt.height(); y += grid_size_) {
            for (auto x = 0; x < rt.width(); x += grid_size_) {
                painter->drawEllipse(x + 5, y + 5, 40, 40);
            }
        }
    }

    void ChessBoard::setGridSize(int grid_size) {
        grid_size_ = grid_size;
    }
    int ChessBoard::getGridSize() {
        return grid_size_;
    }

    QPoint ChessBoard::getGridPos(const Grid &grid) {
        return QPoint(geometry().x() + grid.x_ * grid_size_, geometry().y() + grid.y_ * grid_size_);
    }
    QPoint ChessBoard::getGridPosInit(const Grid &grid) {
        return QPoint(geometry().x() + grid.x_ * grid_size_, 0);
    }

    bool
    ChessBoard::getGridAvailable(const QPoint &pos, Grid &grid, ChessPlayer type) {
        auto rt = geometry();
        if (pos.x() <= rt.x() || pos.x() >= rt.x() + rt.width() || pos.y() <= rt.y() ||
            pos.y() >= rt.y() + rt.height()) {
            return false;
        }

        auto x_in_board = pos.x() - (int) rt.x();
        auto col = x_in_board / grid_size_;
        for (auto row = rows_ - 1; row >= 0; row--) {
            if (((int) (arr_chess_[row * cols_ + col])) == 0) {
                arr_chess_[row * cols_ + col] = type;
                grid.x_ = col;
                grid.y_ = row;
                return true;
            }
        }
        return false;
    }

    bool ChessBoard::isPlayerWin(const Grid &grid, ChessPlayer type, std::vector<Grid> &win_grids) {
        if (!arr_chess_) return false;
        auto row_cur = grid.y_;
        auto col_cur = grid.x_;
        if (arr_chess_[row_cur * cols_ + col_cur] != type) return false;

        // check 4-direction: horizontal, vertical, 45 degree, -45 degree
        // horizontal
        if (isHorizontalWin(row_cur, col_cur, type, win_grids)) {
            return true;
        }
        // vertical
        if (isVerticalWin(row_cur, col_cur, type, win_grids)) {
            return true;
        }
        //-45 degree
        if (isNegative45Win(row_cur, col_cur, type, win_grids)) {
            return true;
        }
        //+45 degree
        if (isPositive45Win(row_cur, col_cur, type, win_grids)) {
            return true;
        }
        win_grids.clear();
        return false;
    }

    bool ChessBoard::isHorizontalWin(int row_cur, int col_cur, ChessPlayer type, std::vector<Grid> &win_grids) {
        auto min_col = std::max(col_cur - 3, 0);
        auto max_col = std::min(col_cur + 3, cols_);
        for (auto i = min_col; i <= max_col - 3; ++i) {
            auto i0 = row_cur * cols_ + i;
            auto i1 = row_cur * cols_ + i + 1;
            auto i2 = row_cur * cols_ + i + 2;
            auto i3 = row_cur * cols_ + i + 3;
            if (arr_chess_[i0] == type && arr_chess_[i1] == type && arr_chess_[i2] == type && arr_chess_[i3] == type) {
                win_grids.clear();
                win_grids.push_back({i, row_cur});
                win_grids.push_back({i + 1, row_cur});
                win_grids.push_back({i + 2, row_cur});
                win_grids.push_back({i + 3, row_cur});
                return true;
            }
        }
        return false;
    }

    bool ChessBoard::isVerticalWin(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids) {
        auto min_row = std::max(cur_row - 3, 0);
        auto max_row = std::min(cur_row + 3, rows_);
        for (auto i = min_row; i <= max_row - 3; ++i) {
            auto i0 = i * cols_ + cur_col;
            auto i1 = (i + 1) * cols_ + cur_col;
            auto i2 = (i + 2) * cols_ + cur_col;
            auto i3 = (i + 3) * cols_ + cur_col;
            if (arr_chess_[i0] == type && arr_chess_[i1] == type && arr_chess_[i2] == type && arr_chess_[i3] == type) {
                win_grids.clear();
                win_grids.push_back({cur_col, i});
                win_grids.push_back({cur_col, i + 1});
                win_grids.push_back({cur_col, i + 2});
                win_grids.push_back({cur_col, i + 3});
                return true;
            }
        }
        return false;
    }

    bool
    ChessBoard::isNegative45Win(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids) {
        int cnt_in_a_row = 0;
        for (int r = cur_row - 3, c = cur_col - 3; (r <= cur_row + 3) && (c <= cur_col + 3); r++, c++) {
            if (r < 0 || c < 0) {
                cnt_in_a_row = 0;
                win_grids.clear();
            } else if (r >= rows_ || c >= cols_) {
                cnt_in_a_row = 0;
                win_grids.clear();
            } else if (arr_chess_[r * cols_ + c] != type) {
                cnt_in_a_row = 0;
                win_grids.clear();
            } else {
                win_grids.push_back({c, r});
                cnt_in_a_row++;
            }
            if (cnt_in_a_row >= 4) {
                return true;
            }
        }
        win_grids.clear();
        return false;
    }

    bool
    ChessBoard::isPositive45Win(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids) {
        int cnt_in_a_row = 0;
        for (int r = cur_row - 3, c = cur_col + 3; (r <= cur_row + 3) && (c >= cur_col - 3); r++, c--) {
            if (r < 0 || c < 0) {
                cnt_in_a_row = 0;
                win_grids.clear();
            } else if (r >= rows_ || c >= cols_) {
                cnt_in_a_row = 0;
                win_grids.clear();
            } else if (arr_chess_[r * cols_ + c] != type) {
                cnt_in_a_row = 0;
                win_grids.clear();
            } else {
                win_grids.push_back({c, r});
                cnt_in_a_row++;
            }
            if (cnt_in_a_row >= 4) {
                return true;
            }
        }
        win_grids.clear();
        return false;
    }

    bool ChessBoard::isMatchDraw() {
        if (!arr_chess_) return false;
        for (auto r = 0; r < rows_; r++) {
            for (auto c = 0; c < cols_; c++) {
                if (((int) arr_chess_[r * cols_ + c]) == 0) {
                    return false;
                }
            }
        }
        return true;
    }

}