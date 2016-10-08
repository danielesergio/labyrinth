//
// Created by dsergio on 02/08/16.
//

#include "Player.h"

namespace dsergio {

    Player::Player(const position &current_position_, Direction current_direction) : current_position_(
            current_position_), current_direction_(current_direction) {}

    /**
     * metodo che calcola la nuova posizione del giocatore
     * @param goAhead se vero va avanti, se falso va indietro
     * @return nuova posizione
     */
    position Player::nextPosition(bool goAhead) {
        int quantity_to_add = -1;
        if(goAhead){
            quantity_to_add = 1;
        }
        position next_position = position(current_position_.getX(), current_position_.getY(), current_position_.getZ());
        switch(current_direction_){//in base alla direzione aggiongo/tolgo un passo all´asse corretto
            case NORD:
                next_position.setZ(next_position.getZ() - quantity_to_add);
                break;
            case SUD:
                next_position.setZ(next_position.getZ() + quantity_to_add);
                break;
            case EST:
                next_position.setX(next_position.getX() + quantity_to_add);
                break;
            case WEST:
                next_position.setX(next_position.getX() - quantity_to_add);
                break;
        }
        return next_position;
    }

    /**
     * metodo che compie una rotazione
     * @param clockwise booleano che indica se la rotazione è oraria o antioraria
     */
    void Player::changeDirection(bool clockwise) {
        switch(current_direction_){
            case NORD:
                if(clockwise){
                    current_direction_ = EST;
                }else{
                    current_direction_ = WEST;
                }
                break;
            case SUD:
                if(clockwise){
                    current_direction_ = WEST;
                }else{
                    current_direction_ = EST;
                }
                break;
            case EST:
                if(clockwise){
                    current_direction_ = SUD;
                }else{
                    current_direction_ = NORD;
                }
                break;
            case WEST:
                if(clockwise){
                    current_direction_ = NORD;
                }else{
                    current_direction_ = SUD;
                }
                break;
        }
    }

    void Player::setCurrentPosition(const position &current_position_) {
        Player::current_position_ = current_position_;
    }

    const position &Player::getCurrentPosition() const {
        return current_position_;
    }

    Direction Player::getCurrentDirection() const {
        return current_direction_;
    }

}
