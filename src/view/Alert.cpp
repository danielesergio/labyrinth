//
// Created by dsergio on 05/08/16.
//

#include "Alert.h"
#include "LightManager.h"
#include "AudioManager.h"

namespace dsergio {

    const float Alert::kRedLight[] = {1,0,0,1};
    const float Alert::kGreenLight[] = {0,1,0,1};

    Alert::Alert(const std::string texture, const GLfloat R) : cube(texture, R/2) {

    }

    /**
     * metodo che disegna un all'allarme alla posizione indicata
     * e che inizializzato il suono
     * @param position1 posizione in cui disegnare l'allarme
     */
    void Alert::draw(const position position1) {
        position pos = position(position1.getX()*2 + R, position1.getY()*2 , position1.getZ()*2 + R);// centro il cubo
        cube::draw(pos); //disegno un cubo che rappresenta l'allarme (dimensioni minori di quelle usare per i muri)
        if(source_map_.find(position1) == source_map_.end()){// se non è già stata creata una fonte sonora in quel punto la creo
            ALuint* source = new ALuint();
            AudioManager::create_source(source, true, &position1);
            source_map_.insert(std::pair<position, ALuint*> (position1, source));
        }
    }

    /**
     * metodo che si occuppa di disegnare una sergente luminosa a forma di sfera sopra il cubo
     * @param pos
     * @param lightNumber
     * @param active
     */
    void Alert::drawLight(position pos, int lightNumber, bool active) {
        float correctPositionFactor = R * 2; // calcolo il fattore di correzzione per posizione la sfera al centro della casella del labirinto
        position spherePosition = position(position(pos.getX()*correctPositionFactor + R, pos.getY()*correctPositionFactor + R +R/2, pos.getZ()*correctPositionFactor + R));
        if(active){ //se l'allarme è attivo disegno una luce rossa altrimenti la disegno verde
            drawSphere(spherePosition, kRedLight);
            LightManager::drawLight(spherePosition, lightNumber,  kRedLight);
            return;
        }
        drawSphere(spherePosition, kGreenLight);
        LightManager::drawLight(spherePosition, lightNumber,  kGreenLight);
        AudioManager::disable_source(source_map_.at(pos));
    }

    /**
     * metodo che disegna la sfera
     * @param pos posizione sfera
     * @param color colore sfera
     */
    void Alert::drawSphere(const position pos, const float color[]) {
        glDisable(GL_LIGHTING); //disabilito la luce e le texture 2d per non interferire con il colore della sfera
        glDisable(GL_TEXTURE_2D);
        glColor3f(color[0],color[1],color[2]);//imposto il colore della sfera
        glPushMatrix();// salvo la matrice nello stack
        glTranslatef(pos.getX(), pos.getY(), pos.getZ());// mi posizione nel punto dove disegno la sfera
        glutSolidSphere(R/4, 50, 50); //disegno la sfera
        glPopMatrix(); // ripristino la matrice precedentemente salvata
        glEnable(GL_LIGHTING); //riabilito la luce e le texture 2d
        glEnable(GL_TEXTURE_2D);

    }

}
