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
        auto rt = rect();
        setFixedSize(rt.width(), rt.height());
        setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        scene->setSceneRect(rect());
        init();
        setAlignment(Qt::AlignLeft | Qt::AlignTop);
    }

    void ChessView::init() {
        scene()->clear();
        winner_grids_.clear();
        player_cur_ = ChessPlayer::First;
        if (scene()->items().size() < 2) {
            board_ = new ChessBoard;
            int margin_top = 100;
            auto rt = rect();
            auto board_size = std::min(rt.width(), rt.height() - margin_top);
            board_->setBoardSize((rt.width() - board_size) / 2.0, margin_top, board_size);
            scene()->addItem(board_);

            initHeadMan();

            head_text_ = scene()->addText(tr("Player ") + (player_cur_ == ChessPlayer::First ? "1" : "2"));
            head_text_->setPos(50, 50);
        }
    }

    void ChessView::initHeadMan() {
        auto rt = rect();
        head_man_ = new ChessMan(player_cur_);
        head_man_->setPos((rt.width() - board_->getGridSize()) / 2.0, 10);
        head_man_->setSize(board_->getGridSize());
        scene()->addItem(head_man_);
    }

    void ChessView::resizeEvent(QResizeEvent *event) {
        init();
        /// NOTICE: scene rect is not equal to view rect! Why???
        scene()->setSceneRect(rect());
        QGraphicsView::resizeEvent(event);
    }

    bool ChessView::event(QEvent *event) {
        if (event->type() == QEvent::Type::MouseButtonPress) {
            auto btn_event = (QMouseEvent *) event;
            if (btn_event->button() == Qt::LeftButton) {
                auto pos = btn_event->pos();
                if (!board_) return false;
                ChessBoard::Grid grid;
                if (board_->getGridAvailable(pos, grid, player_cur_)) {
                    auto pos_grid = board_->getGridPos(grid);
                    auto pos_grid_init = board_->getGridPosInit(grid);
                    auto item_chess = head_man_;
                    auto size_chess = item_chess->getSize();
                    auto x_offset = (board_->getGridSize() - size_chess) / 2.0;
                    auto y_offset = (board_->getGridSize() - size_chess) / 2.0;
                    QPointF pos_final = {pos_grid.x() + x_offset, pos_grid.y() + y_offset};
                    item_chess->setPosFinal(pos_final);
                    QPointF pos_init = {pos_grid_init.x() + x_offset, 50};
                    item_chess->setPosInit(pos_init);
                    ChessAnimation::addAnimation(item_chess, scene());
                    if (board_->isPlayerWin(grid, player_cur_, winner_grids_)) {
                        assert(winner_grids_.size() == 4);
                        for (auto &gird_idx: winner_grids_) {
                            auto item_win = new ChessMan(ChessPlayer::Win);
                            scene()->addItem(item_win);
                            auto pos_chess = board_->getGridPos(gird_idx);
                            item_win->setPos({pos_chess.x() + x_offset, pos_chess.y() + y_offset});
                        }
                        auto winner = tr("Player ") + (player_cur_ == ChessPlayer::First ? tr("1") : tr("2"));
                        QMessageBox::warning(0, tr("Congratulations!"), winner + " wins!");
                        init();
                        return QGraphicsView::event(event);
                    } else if (board_->isMatchDraw()) {
                        QMessageBox::warning(0, tr("It's a draw."), tr("Nobody wins! Restart!"));
                        init();
                        return QGraphicsView::event(event);
                    }
                    update();
                    player_cur_ = (player_cur_ == ChessPlayer::First) ? ChessPlayer::Second
                                                                      : ChessPlayer::First;
                    initHeadMan();
                    head_text_->setPlainText(tr("Player ") + (player_cur_ == ChessPlayer::First ? "1" : "2"));
                }

            }
        }
        return QGraphicsView::event(event);
    }

}