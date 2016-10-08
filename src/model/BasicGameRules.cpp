//
// Created by dsergio on 11/09/16.
//

#include <cstddef>
#include "BasicGameRules.h"

namespace dsergio {
    BasicGameRules* BasicGameRules::instance_ = NULL;

    BasicGameRules* BasicGameRules::getInstance() {
        if(instance_ == NULL){
            instance_ = new BasicGameRules();
        }
        return instance_;
    }

    /**
     * metodo che controlla se il gioco è finito
     * @param activeAlarm numero di allarmi attivi
     * @param timeleft tempo rimandente
     * @param actionDone azioni eseguite
     * @return
     */
    GameState BasicGameRules::checkGameEnd(int activeAlarm, int timeleft, int actionDone) {
        if(activeAlarm == 0)
            return WIN;
        if(timeleft == 0)
            return LOSE;
        return RUNNING;
    }
}
