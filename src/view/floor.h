//
// Created by dsergio on 30/07/16.
//

#ifndef LABYRINTH_FLOOR_H
#define LABYRINTH_FLOOR_H


#include "baseOpenGlEntity.h"

namespace dsergio {
    class floor: public baseOpenGlEntity {
    public:
        floor(const std::string, float =1, GLfloat =1);

//        virtual void draw() override;

        virtual void draw(const position =position()) override;

    private:
        float schem_size_;
    };
}


#endif //LABYRINTH_FLOOR_H