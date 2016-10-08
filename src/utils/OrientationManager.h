//
// Created by dsergio on 03/08/16.
//

#ifndef LABYRINTH_ORIENTATIONMANAGER_H
#define LABYRINTH_ORIENTATIONMANAGER_H


#include "Direction.h"

namespace dsergio {
    class OrientationManager {
    public:
        static float getAngleFromDirection(Direction);
    };
}


#endif //LABYRINTH_ORIENTATIONMANAGER_H