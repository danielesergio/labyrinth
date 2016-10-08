//
// Created by dsergio on 03/08/16.
//

#ifndef LABYRINTH_LOGGER_H
#define LABYRINTH_LOGGER_H

#include <string>

namespace dsergio {
    class Logger {
    public:
        static void message(std::string message);
        static bool enable;

    };
}


#endif //LABYRINTH_LOGGER_H