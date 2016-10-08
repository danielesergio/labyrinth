//
// Created by dsergio on 05/08/16.
//

#ifndef LABYRINTH_ALERTMODEL_H
#define LABYRINTH_ALERTMODEL_H


#include "../utils/position.h"

namespace dsergio {
    class AlertModel {
    public:
        AlertModel(bool active, int x, int z);
        void disableAlarm();

        bool isActive() const;

        const position getPosition() const;

    private:
        bool active_;

        position position_;

    };
}


#endif //LABYRINTH_ALERTMODEL_H