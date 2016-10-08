//
// Created by dsergio on 01/08/16.
//

#include "position.h"
#include "string"

namespace dsergio {

    float position::getX() const {
        return x_;
    }

    void position::setX(float x_) {
        position::x_ = x_;
    }

    float position::getZ() const {
        return z_;
    }

    void position::setZ(float z_) {
        position::z_ = z_;
    }

    float position::getY() const {
        return y_;
    }

    bool position::operator==(const position &rhs) const {
        return x_ == rhs.x_ &&
               y_ == rhs.y_ &&
               z_ == rhs.z_;
    }

    bool position::operator<(const position &rhs) const {
//        // z_ rappresentano le righe della matrice dello schema;
//        if(z_ < rhs.z_)
//            return true;
//        // x_ rappresentano le colonne della matrice dello schema;
//        if(x_ < rhs.x_)
//            return true;
//        return y_ < rhs.y_;
        int tot = z_*1000 + x_;
        int tot2 = rhs.z_ * 1000 + rhs.z_;
        std::string val1 = std::to_string(z_)+"_"+std::to_string(x_)+"_"+std::to_string(y_);
        std::string val2 = std::to_string(rhs.z_)+"_"+std::to_string(rhs.x_)+"_"+std::to_string(rhs.y_);
        return val1<val2;
    }

    bool position::operator>(const position &rhs) const {
        return rhs < *this;
    }

    bool position::operator<=(const position &rhs) const {
        return !(rhs < *this);
    }

    bool position::operator>=(const position &rhs) const {
        return !(*this < rhs);
    }

    bool position::operator!=(const position &rhs) const {
        return !(rhs == *this);
    }

    void position::setY(float y_) {
        position::y_ = y_;
    }

    position::position(float x_, float y_, float z_) : x_(x_), y_(y_), z_(z_) {}

    position::position(const position& pos) : position(pos.x_, pos.y_, pos.z_) {}



}
