//
// Created by dsergio on 16/09/16.
//

#include <cstddef>
#include "RoundState.h"
#include "BasicGameRules.h"

namespace dsergio {
    RoundState* RoundState::instance_ =  NULL;



    GameState RoundState::getGameState() const {
        return game_state_;
    }


    /**
     * metodo che decrementa il tempo restante alla fine del gioco
     * e aggiorna lo stato del gioco
     * @return il tempo restante
     */
    int RoundState::decrementTimeLeft() {
        game_state_ = game_rules_->checkGameEnd(active_alert, --time_left_, 0);
        return time_left_;
    }

    int RoundState::getTime_left_() const {
        return time_left_;
    }

    int RoundState::getActive_alert() const {
        return active_alert;
    }

    void RoundState::setActive_alert(int active_alert) {
        this->active_alert = active_alert;
    }

    /**
     * metodo che decrementa gli allarmi attivi e
     * aggiorna lo stato del gioco
     */
    void RoundState::decrement_active_alert() {
        game_state_ = game_rules_->checkGameEnd(--active_alert, time_left_, 0);
        this->active_alert;
    }

    RoundState* RoundState::getInstance() {
        if( instance_ == NULL){
            init(60, false);
        }
        return instance_;
    }

    /**
     * metodo che inizializza lo stato del gioco
     * @param time tempo a disposizione del giocatore
     * @param sound tipo di gestione del suono
     */
    void RoundState::init(int time, bool sound) {
        instance_ = new RoundState();
        instance_->time_left_ = time;
        instance_->sound_proof_ = sound;
        instance_->game_rules_ = BasicGameRules::getInstance();
    }

    bool RoundState::isSoundproof() const {
        return sound_proof_;
    }

    /**
     * metodo che ritorna la stringa di fine gioco in base allo stato finale
     * @return
     */
    std::string RoundState::getEndGameMessage() {
        switch(game_state_){
            case WIN:
                return "Hai vinto!";
            case LOSE:
                return "Hai perso!";
            default:
                return "";
        }


    }

    RoundState::RoundState() {
    }

    RoundState::~RoundState() {
        delete game_rules_;
    }
}
