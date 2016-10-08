//
// Created by dsergio on 01/08/16.
//

#include <iostream>
#include "Ceiling.h"

namespace dsergio {

    Ceiling::Ceiling(const std::string texture, float size, GLfloat R) : baseOpenGlEntity(texture, R), size_(size)  {

    }

    /**
     * metodo che disegna il soffitto
     * @param position
     */
    void Ceiling::draw(const position position) {
        glBindTexture(GL_TEXTURE_2D, getTexture());//ottengo la texture da disegnare


        const GLfloat x = position.getX() * R;
        const GLfloat y = position.getY() * R;
        const GLfloat z = position.getZ() * R;


        glBegin(GL_QUADS);//disegno un quadrato dandogli quattro vertici (righe sucessive)
        glNormal3f(0, -1, 0);//imposto i parametri per l´ombreggiatura
        glTexCoord2f(1, 1);// imposto le coordinate della texture
        glVertex3f(x, y + R,z);//imposto il primo vertice del quadrato
        glTexCoord2f(0, 1);
        glVertex3f(x + R, y + R, z);
        glTexCoord2f(0, 0);
        glVertex3f(x + R, y + R, z + R);
        glTexCoord2f(1, 0);
        glVertex3f(x, y + R, z + R);
        glEnd();

    }
}
