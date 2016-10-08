//
// Created by dsergio on 01/08/16.
//

#include "LabyrinthModel.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "../utils/Logger.h"
#include "RoundState.h"
#include "ExitCode.h"

namespace dsergio {
    using namespace std;

    int LabyrinthModel::getUnit() const {
        return unit_;
    }

    /**
     * metodo che carica il labirinto da file
     * @param file_path path del file da caricare
     *
     */
    void LabyrinthModel::load(string file_path) {

        ifstream is(file_path);     // apro il file
        if(is.fail()){
            exit(CONFIGURATION_FILE_NOT_FOUND); // se fallisco chiudo il programma con codice di errore
        }
        string labyrinth_length_string, time, soundproof;
        char c;
        try{ // cerco di leggere dei parametri dal file di configurazione
            getline (is,labyrinth_length_string);
            scheme_size_ = stoi(labyrinth_length_string);
            getline (is,time);
            getline (is, soundproof);
            RoundState::init(atoi(time.c_str()), soundproof == "T");
        } catch(std::invalid_argument e){
            exit(CONFIGURATION_FILE_BAD);// se informazioni sbagliate esco dal programma
        } catch(std::exception e){
            exit(CONFIGURATION_FILE_BAD);
        }
        this->scheme_ = new MapElement*[scheme_size_];
        for(int i = 0; i < scheme_size_; i++){
            this->scheme_[i] = new MapElement[scheme_size_];
        }
        int current_row = 0;
        int current_column = 0;
        string message;
        AlertModel* alert;
        int active_alert = 0;
        bool check_player = false;
        bool check_alert = false;
        while (is.get(c)){//inizializzo la mappa del labirinto, la posizione degli allarmi e del giocatore
            if(current_column > scheme_size_ || current_row > scheme_size_ -1){
                exit(CONFIGURATION_FILE_BAD);
            } else if( c == kNewLineCharacter && current_column < scheme_size_){
                exit(CONFIGURATION_FILE_BAD);
            } else if( c == kNewLineCharacter){
                current_row++;
                if(current_row < scheme_size_)
                current_column = 0;
            } else {
                c = (char) toupper(c);
                switch(c){
                    case 'X':
                        this->scheme_[current_row][current_column++] = WALL;
                        break;
                    case ' ':
                        this->scheme_[current_row][current_column++] = EMPTY;
                        break;
                    case '*':
                        message = "Allarme trovato! x:"+ std::to_string(current_column)+" y: ";
                        message += std::to_string(current_row);
                        Logger::message(message);
                        active_alert++;
                        alert = new AlertModel(true, current_column, current_row);
                        this->alert_list_.insert(std::pair<position, AlertModel*> (alert->getPosition(), alert));
                        this->scheme_[current_row][current_column++] = ALERT;
                        check_alert = true;
                        break;
                    case 'S':
                    case 'W':
                    case 'N':
                    case 'E':
                        message = "Player trovato! x:"+ std::to_string(current_column)+" y: ";
                        message += std::to_string(current_row)+" Direzione: "+c;
                        Logger::message(message);
                        this->player_ = new Player(position(current_column * unit_, 0, current_row * unit_),
                                                   static_cast<Direction > (c));
                        this->scheme_[current_row][current_column++] = EMPTY;
                        check_player = true;
                    default:
                        break;
                }
            }
        }
        is.close();// chiuso lo stream;
        //controllo che il file si configurata correttamente altrimenti esco con un codice di errore
        if( current_row < scheme_size_ -1) {
            exit(CONFIGURATION_FILE_BAD);
        }
        if( current_column < scheme_size_){
            exit(CONFIGURATION_FILE_BAD);
        }
        if(!check_player){
            exit(PLAYER_NOT_FOUND);
        }
        if(!check_alert){
            exit(ALERT_NOT_FOUND);
        }
        if(active_alert>6){
            exit(TOO_MUCH_ALERT);
        }
        RoundState::getInstance()->setActive_alert(active_alert);// setto il numero di allarmi attivi nello stato del gioco
    }

    /**
     * metodo che disabilità l´allarme che ho davanti (se esiste)
     */
    void LabyrinthModel::disableAlarm() {
        position current_position = player_->nextPosition(true);//stimo la posizione davanti al giocatore
        MapElement mapElement = getElemAtPosition((int)current_position.getZ()/unit_,(int)current_position.getX()/unit_);//ottengo cosa c´è nella posizione davanti al giocatore
        string message = "disattivazione Allarme! x:"+ std::to_string(current_position.getZ()/unit_)+" y: ";
        message += std::to_string(std::floor(current_position.getX()/unit_));
        Logger::message(message);
        if(mapElement == ALERT){ // se davanti al giocatore ho un Alert lo disattivo
            AlertModel * alertModel = alert_list_.at(position(current_position.getX()/unit_,0,current_position.getZ()/unit_));
            if(alertModel->isActive()){//se l´allarme è attivo
                RoundState::getInstance()->decrement_active_alert();//decremento il numero di allarmi attivi nel labirinto
                alertModel->disableAlarm();//disabilitò l´allarme
            }
        }
    }



    /**
     * metodo che verifica il tipo di elemento del labirinto in una data posizione
     * @param riga
     * @param colonna
     * @return
     */
    MapElement LabyrinthModel::getElemAtPosition(int riga, int colonna) {
        //controllo per non fare uscire il giocatore dal labirinto
        if(riga<0 || riga>scheme_size_-1 || colonna < 0 || colonna > scheme_size_-1){
            return WALL;
        }
        return this->scheme_[riga][colonna];
    }


    int LabyrinthModel::getSchemeSize() const {
        return scheme_size_;
    }

    position LabyrinthModel::getPlayerPosition() {
        return this->player_->getCurrentPosition();
    }

    Direction LabyrinthModel::getPlayerDirection() {
        return this->player_->getCurrentDirection();
    }

    //metodo che controlla se una posizione è occupabile (non deve essere un muro o un allarme)
    bool LabyrinthModel::isAvviablePosition(int x, int z) {
        MapElement mapElement = getElemAtPosition(z/unit_,x/unit_);
        return mapElement == EMPTY;
    }

    /**
     * metodo che muove il giocatore
     * @param isRotation se vero rotazione, altrimenti traslazione
     * @param action se rotazione vero indica il verso della rotazione altrimenti indica il verso della traslazione
     * @return
     */
    bool LabyrinthModel::movePlayer(bool isRotation, bool action) {
        if(isRotation){
            player_->changeDirection(action);//compio una rotazione del giocatore
            return true;
        }
        position pos = player_->nextPosition(action);// ottengo la prossima posizione del giocatore
        if(isAvviablePosition((int)pos.getX(), (int)pos.getZ())){// se la posizione è occupabile
            player_->setCurrentPosition(pos);// aggiorno la posizione del giocatore con la nuova posizione
            return true;
        }
        return false;
    }

    const char LabyrinthModel::kNewLineCharacter = '\n';
    const string LabyrinthModel::kPathLabyrinthScheme = "resources/scheme";

    LabyrinthModel::LabyrinthModel(int unit) {
        unit_ = unit;
    }

    std::map<position, AlertModel *>::iterator LabyrinthModel::getBeginAlertIterator() {
        return alert_list_.begin();
    }

    std::map<position, AlertModel *>::iterator LabyrinthModel::getEndAlertIterator() {
        return alert_list_.end();
    }

    LabyrinthModel::~LabyrinthModel() {
        MapElement** scheme_;

        for(int i=0; i<scheme_size_; i++){
            delete scheme_[i];
        }
        delete scheme_;
        delete player_;
        for(std::map<position, AlertModel *>::iterator i = alert_list_.begin(); i!= alert_list_.end(); i++){
            delete i->second;
        }
    }
}
