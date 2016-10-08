//
// Created by dsergio on 30/07/16.
//

#include "floor.h"

namespace dsergio {
    floor::floor(const std::string texture, float size, GLfloat R) : baseOpenGlEntity(texture, R), schem_size_(size) {

    }

    /**
     * metodo che disegna il pavimento
     * @param position posizione in cui disegnre il pavimento
     */
    void floor::draw(const position position) {
        glBindTexture(GL_TEXTURE_2D, getTexture()); //ottengo la texture da disegnare

        const GLfloat x = (const GLfloat) (position.getX() * R);
        const GLfloat y = (const GLfloat) (position.getY() * R);
        const GLfloat z = (const GLfloat) (position.getZ() * R);

        glBegin(GL_QUADS);//disegno un quadrato dandogli quattro vert

        glNormal3f(0, 1, 0);//imposto i parametri per l´ombreggiaturaici (righe sucessive)
        glTexCoord2f(1, 1);// imposto le coordinate della texture
        glVertex3f(x + R, y, z);//imposto il primo vertice del quadrato
        glTexCoord2f(0, 1);
        glVertex3f(x,y,z);
        glTexCoord2f(0, 0);
        glVertex3f(x, y, z + R);
        glTexCoord2f(1, 0);
        glVertex3f(x + R, y, z + R);


        glEnd();
    }
}
