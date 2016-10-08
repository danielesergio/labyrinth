//
// Created by dsergio on 05/08/16.
//

#include "AlertModel.h"

namespace dsergio {

    AlertModel::AlertModel(bool active, int x, int z) : active_(active) {
        position_ = position(x, 0, z);
    }

    void AlertModel::disableAlarm() {
        this->active_ = false;
    }

    bool AlertModel::isActive() const {
        return active_;
    }

    const position AlertModel::getPosition() const {
        return position_;
    }

}
