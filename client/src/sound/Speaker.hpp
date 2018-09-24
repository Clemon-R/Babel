//
// Created by raphael on 22/09/18.
//

#ifndef CLIENT_SPEAKER_H
#define CLIENT_SPEAKER_H

#include <iostream>
#include <vector>
#include <mutex>
#include <portaudio.h>
#include "Config.hpp"

namespace sound {
    class Speaker {
    public:
        Speaker();
        ~Speaker();

        void start();
        void stop();

        bool isSpeaking();
        std::vector<std::vector<SAMPLE>>  &getFrames();
        void increaseFrameIndexBy(int);
        std::mutex  &getLock();
        void    addFrames(std::vector<SAMPLE> &values);
    private:
        std::mutex  _lock;
        int _frameIndex;
        bool _state;
        std::vector<std::vector<SAMPLE>> _frames;
        PaStream *_stream;
    };
}

#endif //CLIENT_SPEAKER_H
