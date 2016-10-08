//
// Created by dsergio on 16/09/16.
//

#ifndef LABYRINTH_round_state_H
#define LABYRINTH_round_state_H


#include "GameState.h"
#include "GameRules.h"
#include "string"

namespace dsergio {
    class RoundState {
    public:
        static RoundState* getInstance();

        static void init(int time, bool soundproof);

        GameState getGameState() const;

        int decrementTimeLeft();

        int getActive_alert() const;

        void setActive_alert(int);

        void decrement_active_alert();

        std::string getEndGameMessage();

        int getTime_left_() const;

        bool isSoundproof() const;

        virtual ~RoundState();

    private:
        static RoundState* instance_;
        GameState game_state_;
        GameRules* game_rules_;
        int time_left_ = 0;
        int active_alert = 0;
        bool sound_proof_;

        RoundState();
    };
}


#endif //LABYRINTH_round_state_H