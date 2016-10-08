//
// Created by dsergio on 06/08/16.
//

#include <string>
#include <AL/al.h>
#include <AL/alut.h>
#include "AudioManager.h"
#include "../utils/Logger.h"

using namespace std;

namespace dsergio {

    ALuint AudioManager::background_buffer_;
    ALuint AudioManager::alert_buffer_;
    std::vector<ALuint*> AudioManager::source_list_;
    /**
     * metodo che inizializza la libreria per la gestione audio
     * @param argc
     * @param argv
     */
    void AudioManager::initialized(int  argc, char ** argv) {
        alutInit (&argc, argv);
        int error = alGetError();
        if (error)
            Logger::message(alutGetErrorString(error));

        background_buffer_ = alutCreateBufferFromFile ("resources/sound/alarm.wav");
        alert_buffer_ = alutCreateBufferFromFile ("resources/sound/alarm.wav");
    }

    /**
     * metodo che crea la sorgente audio
     * @param source puntatore alla sorgente
     * @param isAlert booleano che indica se la sorgente è un allarme
     * @param pos posizione della sorgente
     */
    void AudioManager::create_source(ALuint* source, bool isAlert, const position *pos) {
        ALuint buffer;
        isAlert ? buffer = alert_buffer_ : buffer = background_buffer_;//scelta della musica

        //configurazione sorgente sonora
        alGenSources (1, source);
        alSourcei (*source, AL_BUFFER, buffer);

        alDistanceModel(AL_EXPONENT_DISTANCE); // tipo di attenuazione audio
        alSource3f(*source, AL_POSITION, pos->getX(), pos->getY(), pos->getZ());// posizione della sorgente
        alSource3f(*source, AL_DIRECTION, 0, 1, 0);// direzione della sorgente
        alSourcei(*source, AL_LOOPING, AL_TRUE); //loop audio
        alSourcef(*source, AL_REFERENCE_DISTANCE, 3);// distanza dalla sorgente all´interno della quale non c´è attenuazione
        alSourcef(*source, AL_ROLLOFF_FACTOR, 3);//moltiplicatore fattore di attenuazione
        alSourcef(*source, AL_MIN_GAIN, 0.0); //volume minimo
        alSourcef(*source, AL_MAX_GAIN, 1.0); //volume massimo
        alSourcePlay (*source);// avvio sorgente
        source_list_.push_back(source);
    }

    /**
     * metodo che stoppa la sorgente
     * @param source
     */
    void AudioManager::disable_source(ALuint* source) {
        alSourceStop(*source);
    }

    /**
     * metodo che aggiorna la posizione dell´ascoltatore rispetto alla sorgente
     * @param pos posizione ascoltatore
     */
    void AudioManager::updateListenerPosition(position *pos) {
        alListener3f(AL_POSITION, pos->getX(), pos->getY(), pos->getZ());
    }

    void AudioManager::exit() {
        alutExit();
    }

    void AudioManager::disableAllSource() {
        for(std::vector<ALuint*>::size_type i = 0; i != source_list_.size(); i++) {
            disable_source(source_list_[i]);
        }
    }


}
