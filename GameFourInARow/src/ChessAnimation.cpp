//
// Created by arthur on 9/9/24.
//

#include "ChessAnimation.h"
#include <QState>>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

namespace GameFourInARow {
    void ChessAnimation::addAnimation(ChessMan *chess, QGraphicsScene* scene) {
        auto pos_orig = chess->scenePos();
        auto pos_init = chess->getPosInit();
        auto pos_final = chess->getPosFinal();

        QPropertyAnimation *animation = new QPropertyAnimation(chess, "pos");
        animation->setDuration(500);
        animation->setStartValue(pos_orig);
        animation->setEndValue(pos_init);

        QPropertyAnimation *animation2 = new QPropertyAnimation(chess, "pos");
        animation2->setDuration(500);
        animation2->setStartValue(pos_init);
        animation2->setEndValue(pos_final);

        QSequentialAnimationGroup* animation_group = new QSequentialAnimationGroup();
        animation_group->addAnimation(animation);
        animation_group->addAnimation(animation2);
        animation_group->start();
    }
}