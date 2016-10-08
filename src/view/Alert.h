//
// Created by dsergio on 05/08/16.
//

#ifndef LABYRINTH_ALERT_H
#define LABYRINTH_ALERT_H


#include <AL/al.h>
#include "baseOpenGlEntity.h"
#include "cube.h"

namespace dsergio {
    class Alert : public cube{
    public:
        Alert(const std::string, const GLfloat =1);

        void drawLight(position, int, bool = false);

        virtual void draw(const position position1) override;
    private:
        static const float kRedLight[];
        static const float kGreenLight[];
        void drawSphere(const position , const float[] );
        std::map<position,ALuint*> source_map_;
    };
}


#endif //LABYRINTH_ALERT_H