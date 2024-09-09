//
// Created by arthur on 9/6/24.
//

#pragma once

#include <QGraphicsWidget>

namespace GameFourInARow {

    enum class ChessPlayer {
        First = 1,
        Second,
        Win
    };

    class ChessMan : public QGraphicsWidget {
    public:
        ChessMan(ChessPlayer player, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
        int getSize();

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
