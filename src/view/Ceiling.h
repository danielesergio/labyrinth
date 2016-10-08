//
// Created by dsergio on 01/08/16.
//

#ifndef LABYRINTH_CEILING_H
#define LABYRINTH_CEILING_H


#include "baseOpenGlEntity.h"

namespace dsergio {
    class Ceiling : public baseOpenGlEntity {
    public:
        Ceiling(const std::string, float =1, GLfloat =1);

//        virtual void draw() override;

        virtual void draw(const position =position()) override;

    private:
        float size_;
    };
}


#endif //LABYRINTH_CEILING_H