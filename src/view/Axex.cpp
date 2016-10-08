//
// Created by dsergio on 03/08/16.
//

#include <GL/gl.h>
#include "Axex.h"

namespace dsergio {
    void Axex::draw() {
        glDisable(GL_LIGHTING);
        glColor3f(1.0f,0.0f,.0f); //red color
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(50.0f, 0.0f, 0.0f);
        glEnd();

        glColor3f(0.0f,1.0f,.0f); //green color
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 50.0f, 0.0f);
        glEnd();

        glColor3f(0.0f,0.0f,1.0f); //blue color
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 50.0f);
        glEnd();
        glEnable(GL_LIGHTING);
        //x red
        //y green
        //z blue

    }

}
