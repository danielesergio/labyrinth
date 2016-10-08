//
// Created by dsergio on 30/07/16.
//

#include "cube.h"

namespace dsergio {

    cube::cube(const std::string texture, const GLfloat R) : baseOpenGlEntity(texture, R) {
    }

    /**
     * metodo che disegna un cubo
     * @param position posizione in cui disegnare il cubo
     */
    void cube::draw(const position position) {

        glBindTexture(GL_TEXTURE_2D, getTexture());//ottengo la texture del tubo

        //aggiunto per risolvere un fix grafico
        const GLfloat x = (const GLfloat) (position.getX() * R + .001);
        const GLfloat y = position.getY() * R;
        const GLfloat z = (const GLfloat) (position.getZ() * R +.001);

        glBegin(GL_QUADS);//disegno un quadrato dandogli quattro vertici (righe sucessive)

        glNormal3f(0, 0, 1);//imposto i parametri per l´ombreggiatura
        glTexCoord2f(1, 1);// imposto le coordinate della texture
        glVertex3f(x + R, y + R, z + R);//imposto il vertice del primo quadrato
        glTexCoord2f(0, 1);
        glVertex3f(x, y + R, z + R);
        glTexCoord2f(0, 0);
        glVertex3f(x, y, z + R);
        glTexCoord2f(1, 0);
        glVertex3f(x + R, y, z + R);

        glNormal3f(0, 0, -1);
        glTexCoord2f(1, 1);
        glVertex3f(x, y + R, z);
        glTexCoord2f(0, 1);
        glVertex3f(x + R, y + R, z);
        glTexCoord2f(0, 0);
        glVertex3f(x + R, y, z);
        glTexCoord2f(1, 0);
        glVertex3f(x, y, z);

        glNormal3f(1, 0, 0);
        glTexCoord2f(1, 1);
        glVertex3f(x + R, y + R, z);
        glTexCoord2f(0, 1);
        glVertex3f(x + R, y + R, z + R);
        glTexCoord2f(0, 0);
        glVertex3f(x + R, y, z + R);
        glTexCoord2f(1, 0);
        glVertex3f(x + R, y, z);

        glNormal3f(-1, 0, 0);
        glTexCoord2f(1, 1);
        glVertex3f(x, y + R, z + R);
        glTexCoord2f(0, 1);
        glVertex3f(x, y + R, z);
        glTexCoord2f(0, 0);
        glVertex3f(x, y, z);
        glTexCoord2f(1, 0);
        glVertex3f(x, y, z + R);

        //faccia sopra
        glNormal3f(0, 1, 0);
        glTexCoord2f(1, 1);
        glVertex3f(x + R, y + R, z);
        glTexCoord2f(0, 1);
        glVertex3f(x, y + R, z);
        glTexCoord2f(0, 0);
        glVertex3f(x, y + R, z + R);
        glTexCoord2f(1, 0);
        glVertex3f(x + R, y + R, z + R);

        //faccia sotto
        glNormal3f(0, -1, 0);
        glTexCoord2f(1, 1);
        glVertex3f(x, y + R, z);
        glTexCoord2f(0, 1);
        glVertex3f(x + R, y + R, z);
        glTexCoord2f(0, 0);
        glVertex3f(x + R, y + R, z + R);
        glTexCoord2f(1, 0);
        glVertex3f(x, y + R, z + R);

        glEnd();
    }
}
