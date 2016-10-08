/*
 */

#include <iostream>
#include "GL/freeglut.h"
#include "view/cube.h"
#include "model/LabyrinthModel.h"
#include "controller/LabyrinthController.h"
#include "utils/Logger.h"
#include "utils/OrientationManager.h"
#include "view/LightManager.h"
#include "view/AudioManager.h"
#include "model/ExitCode.h"
#include <algorithm>    // std::min
#include <ctime>
#include <cstring>

using namespace dsergio;


void CambiaDim(int, int);
void DisegnaTutto();
void Azione(unsigned char key, int x, int y);
void UpdateTitleBar();
void initFog();
void initLight();
void timerFunc(int);
void screenMessage(void);
position CorrectView(position pos, Direction dir, float unit);

bool gameEnd = false;
bool endMessageIsVisible = false;

/**
 * Funzione per ridimensionare la finestra
 * @param w larghezza della finestra
 * @param h altezza della finestra
 */
void CambiaDim(int w, int h)
{
    if(h == 0) h = 1;
    glViewport(0, 0, w, h); //modifica dimensioni finestra -> la matrice di proiezione viene modificata
    glMatrixMode(GL_PROJECTION); //le prossime operazioni vengono eseguite sulla matrice di proiezione
    glLoadIdentity(); // sostituisce la matrice corrente con la matrice identità
    glFrustum(-.5, .5, -.5, .5, .5, 1000);
}

/**
 * funzione che stampa un messaggio su una prospettiva 2d
 * @param text messagggio da stampare
 * @param x posizione da cui iniziare a stampare
 * @param y altezza da cui iniziare a stampare
 */
void printMessageAtPosition(const string text, double x, double y)
{
    glRasterPos2d(x, y); // setta la posizione iniziale su cui iniziare a stampare la stringa su un piano 2d
    for (string::const_iterator i = text.begin(); i != text.end(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *i);//stampa tutti i caratteri del stringa text
    }
}

/**
 * Funzione che mostra a schermo una serie di messaggi
 * Invocata alla fine del gioco
 */
void screenMessage(void)
{
    endMessageIsVisible = true;
    AudioManager::disableAllSource();
    glColor3d(1, 1, 1); //colore testo bianco
    glDisable(GL_LIGHTING);//disabilito la luce perchè influisce sul colore
    glDisable(GL_TEXTURE_2D);//disabilito le texture 2d perchè influisce sul colore
    glMatrixMode(GL_PROJECTION); //selezione la matrice di proiezione
    glLoadIdentity(); // sostituisco la matrice di proizione con la matrice identità
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);// imposto una regione di visualizzazione ortogonale a due dimensioni
    glMatrixMode(GL_MODELVIEW); // carico la matrice MODELVIEW
    glLoadIdentity(); // sostituisco la matrice corrente con la matrice l´identità
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // predispongo i buffer per il colore e per la profondità per mostrare i messaggi a video
    printMessageAtPosition("Premi un qualsiasi tasto per  uscire", 0.05, 0.90);
    printMessageAtPosition(LabyrinthController::getInstance()->getEndMessage(), 0.45, 0.5);
    string text="END GAME";
    glutSetWindowTitle( (text.c_str()));
    glutSwapBuffers();
}

/**
 * Funzione che si occuppa di disegnare il labirinto o di mostrare il messaggio di fine gioco
 */
void DisegnaTutto()
{
    if (gameEnd){ // controllo se il gioco è terminato
        screenMessage();// se il gioco è terminato elimino il messaggio
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //predispongo i buffer necessari (per il colore e la profondità)
    glMatrixMode(GL_MODELVIEW);// seleziono la matrice MODELVIEW
    glLoadIdentity();// setto la matrice MODELVIEW uguale all'identità
    Direction direction = LabyrinthController::getInstance()->getPlayerDirection();// ottengo la direzione del giocatore
    float angle = OrientationManager::getAngleFromDirection(direction); // calcolo l'angolo a cui ruotare il labirinto inbase alla direzione
    position pos = LabyrinthController::getInstance()->getPlayerPosition();// ottengo la posizione del giocatore
    float offset = LabyrinthController::getInstance()->getWorldUnit();// ottengo il fattore moltiplicativo del mondo (attualmente fisson a 1)
    position viewPosition = CorrectView(pos,direction, offset);// modifico la posizione in modo tale che il giocatore sia sembre sul bordo del quadrato ed in posizione centrale
    glRotatef(-angle, 0, 1, 0);// ruoto il punto di vista
    glTranslatef(-viewPosition.getX(), -viewPosition.getY(), -viewPosition.getZ());//traslo il punto di vista
    initLight();// inizializzo la luce in modo che sia solidale al giocatore
    initFog();// inizializzo l'effetto nebbia
    glEnable(GL_TEXTURE_2D);// abilito le texture 2d
    LabyrinthController::getInstance()->drawScheme();// invoco la funzione che si occupa di renderizzare il labirinto
    glutSwapBuffers();

}

/**
 * funzione che si occuppa di correggere la posizione corrente in modo tale che il player sia sempre su un lato del quadrato
 * e che sia centrato sul lato
 * @param pos posizione del giocatore
 * @param dir direzione del giocatore
 * @param unit fattore moltiplicativo del mondo
 * @return la posisione corretta
 */
position CorrectView(position pos, Direction dir, float unit){
    float y = std::min(unit/2, .8f); // calcolo l'altezza del punto di vista
    pos.setY(y); //imposto l´altezza del punto di vista
    switch(dir){//eseguo gli aggiustamenti della posizione in base al giocatore
        case SUD:
            pos.setX(pos.getX() + .5f);
            pos.setZ(pos.getZ());
            break;
        case NORD:
            pos.setX(pos.getX() + .5f);
            pos.setZ(pos.getZ() + 1);
            break;
        case EST:
            pos.setZ(pos.getZ() + .5f);
            pos.setX(pos.getX());
            break;
        case WEST:
            pos.setZ(pos.getZ() + .5f);
            pos.setX(pos.getX() + 1);
            break;
    }
    return pos;
}

//todo aggiungere pausa
/**
 * funzione che prende input un tasto della tastiera e che esegue un azione in base ad esso
 * @param Tasto
 */
void Azione(unsigned char Tasto, int, int)
{
    if(endMessageIsVisible){
        AudioManager::exit();
        exit(OK); // se il gioco è finito quando premo un tasto qualsiasi esco dal gioco
    }
    switch(Tasto) { // in base al tasto eseguo un azione (rotazione verso dx o sx, avanzo/indietreggio di una casella, disabilitò un allarme)
        case 'w':
            LabyrinthController::getInstance()->movePlayer(false, true);
            break;
        case 's':
            LabyrinthController::getInstance()->movePlayer(false, false);
            break;
        case 'a':
            LabyrinthController::getInstance()->movePlayer(true, false);
            break;
        case 'd':
            LabyrinthController::getInstance()->movePlayer(true, true);
            break;
        case 32:
            LabyrinthController::getInstance()->disableAlarm();
            break;
        default:
            break;
//        case 'p':
//            break;
    }
    UpdateTitleBar();// aggiorno la barra del titolo con le invormazioni aggiuntive
    glutPostRedisplay();// al prossimo mainloop viene invocata la funzione display (ridisegno la scena)
}

/**
 * funzione che inizializza l'effetto nebbia
 */
void initFog()
{
    GLfloat density = 0.1; //imposto la densità della nebbia
    GLfloat fogColor[4] = {0,0,0, 1.0}; //imposto il colore della nebbia
    glEnable (GL_FOG);// abilito l'effetto nebbia e nelle seguenti istruzioni ne imposto i parametri
    glFogi (GL_FOG_MODE, GL_EXP2);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, density);
    glHint (GL_FOG_HINT, GL_NICEST);
}

/**
 * funzione che gestisce la luce (sia la torcia del giocatore, sia quella degli allarmi)
 */
void initLight(){
    //ottengo le informazioni necessari per disegnare la luce
    Direction direction = LabyrinthController::getInstance()->getPlayerDirection();
    position player_position = LabyrinthController::getInstance()->getPlayerPosition();
    float offset = LabyrinthController::getInstance()->getWorldUnit();
    player_position = CorrectView(player_position,direction, offset);
    LightManager::drawLight(player_position);// disegno la torcia del giocatore
    LabyrinthController::getInstance()->drawAlarmLight();// disegno la luce degli allarmi
}


int main(int argc, char **argv)
{
    Logger::enable = true;
    glutInit(&argc, argv);
    //inizializzazione schermata
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(550, 550);
    glutCreateWindow("");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1.0f);
    glEnable(GL_CULL_FACE);
    AudioManager::initialized(argc, argv);
    glutReshapeFunc(CambiaDim);
    glutKeyboardFunc(Azione);
    glutDisplayFunc(DisegnaTutto);
    glutTimerFunc(1,timerFunc,0);
    glutMainLoop();
    return(ExitCode::OK);
}

/**
 * funzione per gestire il tempo rimanante al giocatore prima di perdere
 * @param value
 */
void timerFunc(int value){
    if (gameEnd){// se il gioco è finito mostro un messaggio a schermo
        screenMessage();
        return;
    }
    UpdateTitleBar();//aggiorno la barra del titolo
    LabyrinthController::getInstance()->decrementTimeToLeft();//decremento il tempo rimantente all'utente
    gameEnd = LabyrinthController::getInstance()->isEndGame();//verifico se il gioco finisce nella prossima iterazione
    glutTimerFunc(1000,timerFunc,0);// richiama la funzione ogni secondo
}

/**
 * funzione che si occuppa di aggiornare la barra del titolo
 */
void UpdateTitleBar(){
    glutSetWindowTitle(LabyrinthController::getInstance()->getTitleBar().c_str());
}
