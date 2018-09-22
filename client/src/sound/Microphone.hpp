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
        Microphone();
        ~Microphone();

        void start();
        void stop();

        bool isRecording();
        std::vector<SAMPLE>  &getRecords();
        void increaseFrameIndexBy(int);
        std::vector<SAMPLE> getCopyRecords();
        std::mutex  &getLock();
        void removeRecords(int size);
    private:
        int _frameIndex;
        std::vector<SAMPLE>  _records;
        std::mutex  _lock;

        bool _record;
        PaStream    *_stream;
    };
};

#endif //CLIENT_MICROPHONE_HPP
