cmake_minimum_required(VERSION 3.5)
project(Labyrinth)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp view/baseOpenGlEntity.cpp view/baseOpenGlEntity.h view/cube.cpp view/cube.cpp view/floor.cpp view/floor.h utils/position.cpp utils/position.h model/LabyrinthModel.cpp model/LabyrinthModel.h model/MapElement.h controller/LabyrinthController.cpp controller/LabyrinthController.h view/Ceiling.cpp view/Ceiling.h model/Player.cpp model/Player.h utils/Direction.h utils/OrientationManager.cpp utils/OrientationManager.h view/Axex.cpp view/Axex.h utils/Logger.h utils/Logger.cpp view/Alert.cpp view/Alert.h view/LightManager.cpp view/LightManager.h model/AlertModel.cpp model/AlertModel.h view/AudioManager.cpp view/AudioManager.h model/GameState.h model/GameRules.h model/BasicGameRules.cpp model/BasicGameRules.h model/RoundState.cpp model/RoundState.h model/ExitCode.h)
configure_file(resources/texture/hedge.bmp resources/texture/hedge.bmp COPYONLY)
configure_file(resources/texture/road.bmp resources/texture/road.bmp COPYONLY)
configure_file(resources/texture/sky.bmp resources/texture/sky.bmp COPYONLY)

configure_file(resources/texture/wall.bmp resources/texture/wall.bmp COPYONLY)
configure_file(resources/texture/floor.bmp resources/texture/floor.bmp COPYONLY)
configure_file(resources/texture/ceil.bmp resources/texture/ceil.bmp COPYONLY)

configure_file(resources/scheme resources/scheme)

configure_file(resources/sound/alarm.wav resources/sound/alarm.wav COPYONLY)

add_executable(Labyrinth ${SOURCE_FILES})

target_link_libraries(Labyrinth  -lGL -lGLU -lglut -lopenal -lalut)
