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
#include "ChessAnimation.h"
#include "ChessAudio.h"
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

namespace GameFourInARow {

    void ChessAnimation::addAnimation(ChessMan *chess, QGraphicsScene *scene) {
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

        QSequentialAnimationGroup *animation_group = new QSequentialAnimationGroup();
        animation_group->addAnimation(animation);
        animation_group->addAnimation(animation2);
        animation_group->start();

        ChessAudio::instance()->play(AudioType::AudioChessDrop);
    }
}