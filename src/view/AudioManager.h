//
// Created by dsergio on 06/08/16.
//

#ifndef LABYRINTH_AUDIOMANAGER_H
#define LABYRINTH_AUDIOMANAGER_H


#include "../utils/position.h"
#include <AL/al.h>
#include <vector>

namespace dsergio {
    class AudioManager {
     public:
        static void initialized(int, char **);
        static void updateListenerPosition(position *x );
        static void create_source(ALuint* source, bool isAlertSound, const position *pos);
        static void disable_source(ALuint* source);
        static void disableAllSource();
        static void exit();

    private:
        static ALuint background_buffer_;
        static ALuint alert_buffer_;
        static std::vector<ALuint*>  source_list_;
    };

}


#endif //LABYRINTH_AUDIOMANAGER_H