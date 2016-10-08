//
// Created by dsergio on 03/08/16.
//

#include "Logger.h"
#include <fstream>

namespace dsergio {

    bool Logger::enable = true;

    void Logger::message(std::string message) {
        if(enable)
            printf ("LOG: %s \n", message.c_str());
    }
}
