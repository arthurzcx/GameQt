//
// Created by arthur on 9/9/24.
//

#include "ChessAnimation.h"
#include <QStateMachine>
#include <QState>
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QTimer>

namespace GameFourInARow {
    void ChessAnimation::addAnimation(ChessMan *chess, QGraphicsScene* scene) {
        auto pos_init = chess->getPosInit();
        auto pos_final = chess->getPosFinal();

        QPropertyAnimation *animation = new QPropertyAnimation(chess, "pos");
        animation->setDuration(1000);
        animation->setStartValue(pos_init);
        animation->setEndValue(pos_final);
        animation->start();

        scene->addItem(chess);
    }
}