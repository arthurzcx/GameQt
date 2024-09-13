//
// Created by arthur on 9/6/24.
//

#include "ChessBoard.h"

#include <QPainter>
#include <QDebug>

namespace GameFourInARow {
    ChessBoard::ChessBoard(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent, wFlags) {
        grids_.resize(rows_);
        for (auto &row: grids_) {
            row.resize(cols_);
        }
        for (std::size_t r = 0; r < rows_; r++) {
            for (std::size_t c = 0; c < rows_; c++) {
                grids_[r][c].row_ = r;
                grids_[r][c].col_ = c;
            }
        }
    }
    ChessBoard::~ChessBoard() {
        grids_.clear();
    }

    void ChessBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        painter->setRenderHint(QPainter::Antialiasing);
        auto pen = painter->pen();
        pen.setWidth(3);
        pen.setColor(Qt::green);
        painter->setBrush(Qt::green);
        painter->setPen(pen);

        auto rt = rect();
        int radius = 20;
        painter->drawRoundedRect(rt, radius, radius);

        /// The shape of board must be square.
        if (std::abs(rt.width() - rt.height()) > 1.0E-5) {
            qDebug() << "Warning: Please set the shape of board as a square.";
            return;
        }

        /// Draw holes for chess.
        painter->setBrush(Qt::white);
        for (auto r = 0; r < rows_; r += 1) {
            for (auto c = 0; c < cols_; c += 1) {
                auto &grid = grids_[r][c];
                painter->drawEllipse(grid.x_, grid.y_, grid.size_, grid.size_);
            }
        }
    }

    void ChessBoard::setGridSize(int grid_size) {
        grid_size_ = grid_size;
        for (auto &row: grids_) {
            for (auto &grid: row) {
                grid.size_ = grid_size_;
            }
        }
    }
    int ChessBoard::getGridSize() {
        return grid_size_;
    }

    QPoint ChessBoard::getGridPos(const Grid &grid) {
        return QPoint(pos_.x() + grid.x_, pos_.y() + grid.y_);
    }
    QPoint ChessBoard::getGridPosInit(const Grid &grid) {
        return QPoint(pos_.x() + grid.x_, 0);
    }
    void ChessBoard::setBoardSize(int pos_x, int pos_y, int size) {
        pos_ = QPoint(pos_x, pos_y);
        size_ = QSize(size, size);
        setGeometry(pos_x, pos_y, size, size);

        int total_space = space_ * (rows_ + 1);
        setGridSize((size - total_space) / rows_);
        for (std::size_t r = 0; r < rows_; r += 1) {
            for (std::size_t c = 0; c < cols_; c += 1) {
                auto &grid = grids_[r][c];
                grid.x_ = (c + 1) * space_ + c * grid_size_;
                grid.y_ = (r + 1) * space_ + r * grid_size_;
            }
        }
    }

    bool
    ChessBoard::getGridAvailable(const QPoint &pos, Grid &grid, ChessPlayer type) {
        if (pos.x() <= pos_.x() ||
            pos.x() >= pos_.x() + size_.width() ||
            pos.y() <= pos_.y() ||
            pos.y() >= pos_.y() + size_.height()) {
            return false;
        }

        auto x_in_board = pos.x() - pos_.x();
        auto col = x_in_board / (grid_size_ + space_);
        for (auto row = rows_ - 1; row >= 0; row--) {
            if (grids_[row][col].player_ == ChessPlayer::None) {
                grids_[row][col].player_ = type;
                grid = grids_[row][col];
                return true;
            }
        }
        return false;
    }

    bool ChessBoard::isPlayerWin(const Grid &grid, ChessPlayer type, std::vector<Grid> &win_grids) {

        auto row_cur = grid.row_;
        auto col_cur = grid.col_;
        if (grids_[row_cur][col_cur].player_ != type) return false;

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
        auto max_col = std::min(col_cur + 3, cols_ - 1);
        for (auto i = min_col; i <= max_col - 3; ++i) {
            if (grids_[row_cur][i].player_ == type &&
                grids_[row_cur][i + 1].player_ == type &&
                grids_[row_cur][i + 2].player_ == type &&
                grids_[row_cur][i + 3].player_ == type) {
                win_grids.clear();
                win_grids.push_back(grids_[row_cur][i]);
                win_grids.push_back(grids_[row_cur][i + 1]);
                win_grids.push_back(grids_[row_cur][i + 2]);
                win_grids.push_back(grids_[row_cur][i + 3]);
                return true;
            }
        }
        return false;
    }

    bool ChessBoard::isVerticalWin(int cur_row, int cur_col, ChessPlayer type, std::vector<Grid> &win_grids) {
        auto min_row = std::max(cur_row - 3, 0);
        auto max_row = std::min(cur_row + 3, rows_ - 1);
        for (auto i = min_row; i <= max_row - 3; ++i) {
            auto i0 = i * cols_ + cur_col;
            auto i1 = (i + 1) * cols_ + cur_col;
            auto i2 = (i + 2) * cols_ + cur_col;
            auto i3 = (i + 3) * cols_ + cur_col;
            if (grids_[i][cur_col].player_ == type &&
                grids_[i + 1][cur_col].player_ == type &&
                grids_[i + 2][cur_col].player_ == type &&
                grids_[i + 3][cur_col].player_ == type) {
                win_grids.clear();
                win_grids.push_back(grids_[i][cur_col]);
                win_grids.push_back(grids_[i + 1][cur_col]);
                win_grids.push_back(grids_[i + 2][cur_col]);
                win_grids.push_back(grids_[i + 3][cur_col]);
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
            } else if (grids_[r][c].player_ != type) {
                cnt_in_a_row = 0;
                win_grids.clear();
            } else {
                win_grids.push_back(grids_[r][c]);
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
            } else if (grids_[r][c].player_ != type) {
                cnt_in_a_row = 0;
                win_grids.clear();
            } else {
                win_grids.push_back(grids_[r][c]);
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
        for (auto r = 0; r < rows_; r++) {
            for (auto c = 0; c < cols_; c++) {
                if (grids_[r][c].player_ == ChessPlayer::None) {
                    return false;
                }
            }
        }
        return true;
    }

}