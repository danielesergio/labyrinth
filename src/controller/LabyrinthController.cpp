//
// Created by dsergio on 01/08/16.
//

#include "LabyrinthController.h"
#include "../view/AudioManager.h"

namespace dsergio {
    LabyrinthController* LabyrinthController::instance_ =  NULL;

    LabyrinthController* LabyrinthController::getInstance() {
        if(instance_ == NULL){
            instance_ = new LabyrinthController();
        }
        return instance_;
    }

    /**
     * metodo che disegna la luce di tutti gli allarmi
     */
    void LabyrinthController::drawAlarmLight() {
        typedef std::map<position, AlertModel*>::iterator it_type;

        int i = 1;
        for(it_type iterator = model_->getBeginAlertIterator(); iterator != model_->getEndAlertIterator(); iterator++) {
            this->alert_->drawLight(iterator->first, i++, iterator->second->isActive());
        }

    }

    /**
     * metodo che conta gli allarmi attivi
     * @return numero di allarmi attivi
     */
    int LabyrinthController::remainedActiveAlarms() {
        return   RoundState::getInstance()->getActive_alert();
    }

    /**
     * metodo che disegna lo schema del labirinto.
     * Un implementazione più efficiente dovrebbe disegnare gli elementi dello stesso tipo tutti insieme e
     * poi passare ad un nuovo oggetto. Questa implementazione rimane comunque accettabile nel nostro caso.
     *
     */
    void LabyrinthController::drawScheme() {
        for(int i = 0; i<model_->getSchemeSize(); i++){ //riga i-esima = coordinata z
            for(int j = 0; j<model_->getSchemeSize(); j++){// colonna j-esima = coordinata x
                switch(model_->getElemAtPosition(i,j)){
                    case WALL:
                        cube_->draw(position(j, 0, i));
                        break;
                    case ALERT:
                        alert_->draw(position(j,0,i));
                        break;
                    default:
                        break;
                }
                floor_->draw(position(j, 0, i));
                ceiling_->draw(position(j, 0, i));
            }
        }
    }

    //todo cambiare celo stellato genera un bug nella scrittura del testo
    /**
     * Costruttore del controller
     * @return
     */
    LabyrinthController::LabyrinthController() : cube_(NULL), floor_(NULL), ceiling_(NULL),
                                                 model_(new LabyrinthModel()), round_state_(NULL){
        model_->load();// caricamento dello schema e dei parametri da file
        round_state_ = RoundState::getInstance();
        if(round_state_->isSoundproof()){// in mase alla tipologia di propagazione del suono vengono caricate texture diverse
            cube_ = new cube("wall.bmp",model_->getUnit());
            floor_ = new floor("floor.bmp", model_->getSchemeSize(), model_->getUnit());
            ceiling_ = new Ceiling("ceil.bmp", model_->getSchemeSize(), model_->getUnit());
        } else {
            cube_ = new cube("hedge.bmp",model_->getUnit());
            floor_ = new floor("road.bmp", model_->getSchemeSize(), model_->getUnit());
            ceiling_ = new Ceiling("sky.bmp", model_->getSchemeSize(), model_->getUnit());
        }
        alert_ = new Alert("wall.bmp",  model_->getUnit());
    }


    /**
     * metodo che ritorna la posizione del giocatore
     * @return
     */
    position LabyrinthController::getPlayerPosition() {
        return model_->getPlayerPosition();
    }

    /**
     * metodo che ritorna la direzione del giocatore
     * @return
     */
    Direction LabyrinthController::getPlayerDirection() {
        return model_->getPlayerDirection();
    }

    /**
     * metodo che ritorna il fattore moltiplicativo del mondo
     * @return
     */
    float LabyrinthController::getWorldUnit() {
        return model_->getUnit();
    }

    /**
     * metodo che fa muovere il giocatore
     * @param isRotation booleano che indica se il movimento è una rotazione(true) o un avanzamento/indietreggiamento
     * @param action se vero rotazione oraria o avanzamento, se falso rotazione antioraria o indietreggiamento
     * @return booleano che indica se l´azione ha avuto successo o meno
     */
    bool LabyrinthController::movePlayer(bool isRotation, bool action) {
        if(!model_->movePlayer(isRotation, action)){
            return false;
        }
        position pos = model_->getPlayerPosition();//ottengo la nuova posizione del giocatore
        AudioManager::updateListenerPosition(&pos);// aggiorno la posizione del giocatore rispetto alle sorgenti sonore
        return true;
    }

    /**
     * metodo che disabilità l´allarme che ho davanti
     */
    void LabyrinthController::disableAlarm() {
        model_->disableAlarm();
    }

    /**
     * metodo che ritorna il messaggio di fine gioco
     * @return
     */
    string LabyrinthController::getEndMessage() {
        return RoundState::getInstance()->getEndGameMessage();
    }

    /**
     * metodo che decrementa il tempo rimanente
     */
    void LabyrinthController::decrementTimeToLeft() {
        RoundState::getInstance()->decrementTimeLeft();
    }

    /**
     * metodo che contralla se il gioco e terminato
     * @return true se il gioco e finito, false se il gioco è in corso
     */
    bool LabyrinthController::isEndGame() {
        GameState gameState = RoundState::getInstance()->getGameState();
        return gameState == WIN || gameState == LOSE;

    }

    /**
     * metodo che genera la stringa da mostrare nella barra del titolo
     * @return
     */
    string LabyrinthController::getTitleBar() {
        char direction = static_cast<char>(getPlayerDirection());
        string titleBar = "Labyrinth - Direzione: ";
        titleBar.append(sizeof(direction), direction);
        titleBar += " Allarmi rimasti: " + std::to_string(remainedActiveAlarms());
        titleBar += " Tempo rimasto: " + std::to_string(RoundState::getInstance()->getTime_left_());
        return titleBar;

    }

    LabyrinthController::~LabyrinthController() {
        delete model_;
        delete cube_;
        delete floor_;
        delete ceiling_;
        delete alert_;
        delete round_state_;
        delete instance_;
    }
}
