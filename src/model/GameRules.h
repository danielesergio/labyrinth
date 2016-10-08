//
// Created by dsergio on 11/09/16.
//

#ifndef LABYRINTH_GAMERULES_H
#define LABYRINTH_GAMERULES_H

#include "GameState.h"

namespace dsergio {
    class GameRules {
    public:
        virtual GameState checkGameEnd(int activeAlarm, int timeleft, int actionDone)= 0;
    };
}
#endif //LABYRINTH_GAMERULES_H
