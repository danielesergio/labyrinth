//
// Created by dsergio on 01/08/16.
//

#ifndef LABYRINTH_LABYRINTHCONTROLLER_H
#define LABYRINTH_LABYRINTHCONTROLLER_H


#include "../model/LabyrinthModel.h"
#include "../view/cube.h"
#include "../view/floor.h"
#include "../view/Ceiling.h"
#include "../view/Alert.h"
#include "../model/RoundState.h"

namespace dsergio {
    class LabyrinthController {
    public:
        static LabyrinthController* getInstance();
        void drawScheme();
        position getPlayerPosition();
        Direction getPlayerDirection();
        float getWorldUnit();
        bool movePlayer(bool =false, bool =false);
        int remainedActiveAlarms();
        void  drawAlarmLight();
        void disableAlarm();
        string getEndMessage();
        void decrementTimeToLeft();

        string getTitleBar();
        bool isEndGame();

        virtual ~LabyrinthController();

    private:
        static LabyrinthController* instance_;
        LabyrinthController();
        //model
        LabyrinthModel* model_;
        //view
        cube* cube_;
        floor* floor_;
        Ceiling* ceiling_;
        Alert * alert_;
        RoundState* round_state_;
    };

}


#endif //LABYRINTH_LABYRINTHCONTROLLER_H