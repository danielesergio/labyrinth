//
// Created by dsergio on 30/07/16.
//

#ifndef LABYRINTH_CUBE_H
#define LABYRINTH_CUBE_H


#include "baseOpenGlEntity.h"

namespace dsergio {
    class cube  : public baseOpenGlEntity{
    public:
        cube(const std::string, const GLfloat =1);
        virtual void draw(const position = position()) override;

    };
}


#endif //LABYRINTH_CUBE_H