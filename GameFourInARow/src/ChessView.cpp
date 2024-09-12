//
// Created by arthur on 9/6/24.
//

#include "ChessView.h"
#include "ChessBoard.h"
#include "ChessAnimation.h"

#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QMessageBox>

namespace GameFourInARow {
    ChessView::ChessView(QGraphicsScene *scene, QWidget *parent) :
            QGraphicsView(scene, parent) {
        init();
    }

    void ChessView::init() {
        scene()->clear();
        winner_grids_.clear();
        player_cur_ = ChessPlayer::First;
        if (scene()->items().size() < 2) {
//            auto board_size = std::min(rect().width() * 0.8, rect().height() * 0.8);
            auto board = new ChessBoard;
            board->setGeometry(40, 100, 400, 400);
            scene()->addItem(board);

            head_man_ = new ChessMan(ChessPlayer::First);
            head_man_->setPos(225, 50);
            scene()->addItem(head_man_);

            head_text_ = scene()->addText(tr("Player ") + (player_cur_ == ChessPlayer::First ? "1" : "2"));
            head_text_->setPos(50, 50);
        }
    }

    void ChessView::resizeEvent(QResizeEvent *event) {
        fitInView(scene()->sceneRect());
        QGraphicsView::resizeEvent(event);
    }

    bool ChessView::event(QEvent *event) {
        if (event->type() == QEvent::Type::MouseButtonPress) {
            auto btn_event = (QMouseEvent *) event;
            if (btn_event->button() == Qt::LeftButton) {
                auto pos = btn_event->pos();
                auto items = scene()->items();
                for (auto &item: items) {
                    auto board = dynamic_cast<ChessBoard *>(item);
                    if (!board) continue;
                    ChessBoard::Grid grid;
                    if (board->getGridAvailable(pos, grid, player_cur_)) {
                        auto pos_grid = board->getGridPos(grid);
                        auto pos_grid_init = board->getGridPosInit(grid);
                        auto item_chess = head_man_;
                        auto size_chess = item_chess->getSize();
                        auto x_offset = (board->getGridSize() - size_chess) / 2.0;
                        auto y_offset = (board->getGridSize() - size_chess) / 2.0;
                        QPointF pos_final = {pos_grid.x() + x_offset, pos_grid.y() + y_offset};
                        item_chess->setPosFinal(pos_final);
                        QPointF pos_init = {pos_grid_init.x() + x_offset, 50};
                        item_chess->setPosInit(pos_init);
                        ChessAnimation::addAnimation(item_chess, scene());
                        if (board->isPlayerWin(grid, player_cur_, winner_grids_)) {
                            assert(winner_grids_.size() == 4);
                            for (auto &gird_idx: winner_grids_) {
                                auto item_win = new ChessMan(ChessPlayer::Win);
                                scene()->addItem(item_win);
                                auto pos_chess = board->getGridPos(gird_idx);
                                item_win->setPos({pos_chess.x() + x_offset, pos_chess.y() + y_offset});
                            }
                            auto winner = tr("Player ") + (player_cur_ == ChessPlayer::First ? tr("1") : tr("2"));
                            QMessageBox::warning(0, tr("Congratulations!"), winner + " wins!");
                            init();
                            return QGraphicsView::event(event);
                        } else if (board->isMatchDraw()) {
                            QMessageBox::warning(0, tr("It's a draw."), tr("Nobody wins! Restart!"));
                            init();
                            return QGraphicsView::event(event);
                        }
                        player_cur_ = (player_cur_ == ChessPlayer::First) ? ChessPlayer::Second
                                                                          : ChessPlayer::First;
                        head_man_ = new ChessMan(player_cur_);
                        head_man_->setPos(225, 50);
                        scene()->addItem(head_man_);
                        head_text_->setPlainText(tr("Player ") + (player_cur_ == ChessPlayer::First ? "1" : "2"));
                    }
                }

            }
        }
        return QGraphicsView::event(event);
    }

}