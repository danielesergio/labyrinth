//
// Created by dsergio on 11/09/16.
//

#ifndef LABYRINTH_BASICGAMERULES_H
#define LABYRINTH_BASICGAMERULES_H


#include "GameRules.h"

namespace dsergio {

    class BasicGameRules : public GameRules {
    public:
        virtual GameState checkGameEnd(int activeAlarm, int timeleft, int actionDone) override;
        static BasicGameRules* getInstance();

    private:
        static BasicGameRules* instance_;
    };
}


#endif //LABYRINTH_BASICGAMERULES_H