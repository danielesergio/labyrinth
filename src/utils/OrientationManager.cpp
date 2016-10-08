//
// Created by dsergio on 03/08/16.
//

#include "OrientationManager.h"

namespace dsergio {
    float OrientationManager::getAngleFromDirection(Direction direction) {
        switch (direction){
            case SUD:
                return 180.f;
            case EST:
                return 270.f;
            case WEST:
                return 90.f;
            default:
                return 0.f;

        }
    }
}
