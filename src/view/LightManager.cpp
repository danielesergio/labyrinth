//
// Created by dsergio on 05/08/16.
//

#include "LightManager.h"
#include "../utils/Logger.h"

namespace dsergio {

    const float LightManager::DEFAULT_COLOR[] = {1,1,1,1};

    /**
     * Funzione che crea una fonte di luce luminosa
     * @param pos posizione della fonte luminosa
     * @param offset
     * @param index numero della luce
     * @param color colore della luce
     */
    void LightManager::drawLight(position pos, int index, const float * color) {
        GLfloat  light_position[] = {pos.getX(), pos.getY(), pos.getZ(), 1};
        GLenum  light = (GLenum) (GL_LIGHT0 + index);
        glLightfv(light , GL_AMBIENT, color);
        glLightfv(light, GL_DIFFUSE, color);
        glLightfv(light, GL_SPECULAR, color);
        glLightfv(light, GL_POSITION, light_position);
        glLightf(light, GL_CONSTANT_ATTENUATION, .5);
        glLightf(light, GL_QUADRATIC_ATTENUATION, .5);
        glLightf(light, GL_LINEAR_ATTENUATION, .5);
        glEnable(light);

    }
}
