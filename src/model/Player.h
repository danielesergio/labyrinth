//
// Created by dsergio on 02/08/16.
//

#ifndef LABYRINTH_PLAYER_H
#define LABYRINTH_PLAYER_H


#include "../utils/position.h"
#include "../utils/Direction.h"

namespace dsergio {
    class Player {
    public:
        Player(const position &current_position_, Direction current_direction);

        position nextPosition(bool =true);
        void changeDirection(bool =true);

        void setCurrentPosition(const position &current_position_);

        const position &getCurrentPosition() const;

        Direction getCurrentDirection() const;

    private:
        position current_position_;
        Direction current_direction_;
    };
}


#endif //LABYRINTH_PLAYER_H