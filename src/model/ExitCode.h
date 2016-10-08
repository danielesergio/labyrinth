//
// Created by dsergio on 17/09/16.
//

#ifndef LABYRINTH_EXITCODE_H
#define LABYRINTH_EXITCODE_H

namespace dsergio {
    enum ExitCode{
        OK,
        PLAYER_NOT_FOUND,
        ALERT_NOT_FOUND,
        CONFIGURATION_FILE_NOT_FOUND,
        CONFIGURATION_FILE_BAD,
        TEXTURE_NOT_FOUND,
        TOO_MUCH_ALERT
    };
}
#endif //LABYRINTH_EXITCODE_H
