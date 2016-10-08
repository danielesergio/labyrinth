//
// Created by dsergio on 01/08/16.
//

#ifndef LABYRINTH_POSITION_H
#define LABYRINTH_POSITION_H


#include "GL/glut.h"

namespace dsergio {
    class position {
    public:

        position(float x = 0, float y = 0, float z = 0);

        position(const position&);

        float getX() const;

        void setX(float x);

        float getZ() const;

        void setZ(float z);

        float getY() const;

        void setY(float y);

        bool operator==(const position &rhs) const;

        bool operator!=(const position &rhs) const;

        bool operator<(const position &rhs) const;

        bool operator>(const position &rhs) const;

        bool operator<=(const position &rhs) const;

        bool operator>=(const position &rhs) const;

    private:
        float x_;
        float y_;
        float z_;


    };
}


#endif //LABYRINTH_POSITION_H