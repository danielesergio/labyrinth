//
// Created by dsergio on 30/07/16.
//

#ifndef LABYRINTH_BASEOPENGLENTITY_H
#define LABYRINTH_BASEOPENGLENTITY_H

#include <map>
#include "string"
#include "GL/glut.h"
#include "../utils/position.h"

namespace dsergio {
    class baseOpenGlEntity {

    public:
        virtual void draw(const position = position()) = 0;
        baseOpenGlEntity(std::string, GLfloat =1);

    protected:
        static void manageTexture(const std::string textureName);
        const GLuint getTexture();
        GLfloat R;

    private:
        static const std::string TEXTURE_FOLDER;
        static std::map<std::string, GLuint> textureMap;

        std::string texture_;
    };
}


#endif //LABYRINTH_BASEOPENGLENTITY_H