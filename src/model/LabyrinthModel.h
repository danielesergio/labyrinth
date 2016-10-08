//
// Created by dsergio on 01/08/16.
//

#ifndef LABYRINTH_MAP_H
#define LABYRINTH_MAP_H


#include <vector>
#include <map>
#include "MapElement.h"
#include "string"
#include "Player.h"
#include "AlertModel.h"
#include "GameState.h"

namespace dsergio {
    using namespace std;

    class LabyrinthModel {
    public:
        LabyrinthModel(int =1);

        void load(string file_path = kPathLabyrinthScheme);

        int getSchemeSize() const;

        MapElement  getElemAtPosition(int, int);

        void disableAlarm();

        bool movePlayer(bool =false, bool =false);

        position getPlayerPosition();

        Direction getPlayerDirection();

        int getUnit() const;

        std::map<position, AlertModel*>::iterator getBeginAlertIterator();

        std::map<position, AlertModel*>::iterator getEndAlertIterator();

        virtual ~LabyrinthModel();

    private:
        bool isAvviablePosition(int, int);
        MapElement** scheme_;
        int scheme_size_;
        int unit_;
        Player* player_;
        std::map<position, AlertModel*> alert_list_;
        static const char kNewLineCharacter;
        static const string kPathLabyrinthScheme;
    };
}


#endif //LABYRINTH_MAP_H