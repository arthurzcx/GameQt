//
// Created by arthur on 9/6/24.
//

#pragma once

#include "ChessBoard.h"
#include "ChessMan.h"

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
        ChessBoard *board_ = nullptr;
        std::vector<ChessBoard::Grid> winner_grids_{};
    };

}