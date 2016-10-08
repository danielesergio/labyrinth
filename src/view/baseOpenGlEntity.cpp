//
// Created by dsergio on 30/07/16.
//

#include "baseOpenGlEntity.h"
#include "../model/ExitCode.h"
#include <iostream>

using namespace std;

namespace dsergio {
    const std::string baseOpenGlEntity::TEXTURE_FOLDER = "resources/texture";

    std::map<std::string, GLuint>  baseOpenGlEntity::textureMap = std::map<std::string, GLuint>();



    baseOpenGlEntity::baseOpenGlEntity(string texture, GLfloat R){
        this->R = R;
        if(!texture.empty()){
            baseOpenGlEntity::manageTexture(texture);
            this->texture_ = texture;
        }
    }

    /**
     * metodo che gestische la configurazione delle texture
     * @param fileName
     */
    void baseOpenGlEntity::manageTexture(string fileName) {
        map<string,GLuint>::iterator i = textureMap.find(fileName);
        //loadTexture
        if (i == textureMap.end()) { //se la texture è già stata caricata non la ricarica
            const int bindTextureValue = (int)textureMap.size()+1; //creo il valore numerico a cui associare la texture
            string texturePath = TEXTURE_FOLDER + "/" + fileName; //genero il path della texture

            GLubyte texture[512 * 512 * 3]; //dichiaro la varibile che conterrà la texture
            FILE *fHan = fopen(texturePath.c_str(), "rb");//apro il file che conterra la texture
            if(fHan == NULL) exit(TEXTURE_NOT_FOUND); // se non trovo il file chiudo l´applicazione con un codice di errore
            fread(texture , 512 * 512, 3, fHan); // inizializzo la variabile texture
            fclose(fHan);// chiudo il file

            glBindTexture(GL_TEXTURE_2D, (GLuint) bindTextureValue); //associo la texture ad un valore numerico
            //configura la texture
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 1, GL_RGB, GL_UNSIGNED_BYTE, texture);
            //inserisco la texture in una mappa
            textureMap.insert(std::pair<std::string, GLuint> (fileName, bindTextureValue));
        }
    }

    const GLuint baseOpenGlEntity::getTexture(){
        return textureMap.at(texture_);
    };

}
