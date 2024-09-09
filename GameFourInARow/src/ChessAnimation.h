//
// Created by arthur on 9/9/24.
//

#pragma once

#include "ChessMan.h"
#include <QGraphicsScene>

namespace GameFourInARow {
    class ChessAnimation {
    public:
        static void addAnimation(ChessMan *chess, QGraphicsScene* scene);
    };
}
