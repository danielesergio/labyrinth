//
// Created by dsergio on 05/08/16.
//

#ifndef LABYRINTH_LIGHTMANAGER_H
#define LABYRINTH_LIGHTMANAGER_H


#include "../utils/position.h"

namespace dsergio {
    class LightManager {
    public:
        static void drawLight(position, int  = 0, const float [] = DEFAULT_COLOR);

    private:
        static const float DEFAULT_COLOR[];
    };
}


#endif //LABYRINTH_LIGHTMANAGER_H