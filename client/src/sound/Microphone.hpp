//
// Created by raphael on 22/09/18.
//

#ifndef CLIENT_MICROPHONE_HPP
#define CLIENT_MICROPHONE_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <mutex>
#include <portaudio.h>
#include "Config.hpp"

namespace sound {

    class Microphone {
    public:
        Microphone(int &volume);
        ~Microphone();

        void start();
        void stop();

        bool isRecording();
        std::vector<std::vector<SAMPLE>>  &getRecords();
        void increaseFrameIndexBy(int);
        std::mutex  &getLock();
        std::vector<SAMPLE> getNextSample();
        const float   getVolume() const;
    private:
        int _frameIndex;
        std::vector<std::vector<SAMPLE>>  _records;
        std::mutex  _lock;

        bool _record;
        PaStream    *_stream;
        int &_volume;
    };
};

#endif //CLIENT_MICROPHONE_HPP
