//
// Created by raphael on 22/09/18.
//

#include <memory>
#include <thread>
#include <QtCore/QCoreApplication>
#include "sound/Microphone.hpp"
#include "sound/Speaker.hpp"
#include "codec/Opus.hpp"

int main(int argc, char *argv[])
{
    std::unique_ptr<sound::Microphone>  mic(nullptr);
    std::unique_ptr<sound::Speaker>  speak(nullptr);
    std::unique_ptr<Opus>   codec(nullptr);
    std::tuple<unsigned char *, int>    bin;
    std::vector<SAMPLE> tmp;

    try{
        codec.reset(new Opus());
        speak.reset(new sound::Speaker());
        mic.reset(new sound::Microphone());
        if (!mic)
            return (84);
        mic->start();
        speak->start();
        for (int i = 0;i < 100;i++){
            do {
                speak->addFrames(tmp);
                bin = codec->encode(mic->getNextSample());
                tmp = codec->decode(bin);
                if (std::get<0>(bin))
                    delete [] std::get<0>(bin);
            }while (tmp.size() > 0);
            Pa_Sleep(100);
        }
        mic->stop();
        speak->stop();
        Pa_Terminate();
    }catch (const std::exception &error){
        std::cerr << error.what() << std::endl;
        return (84);
    }
    return (0);
}