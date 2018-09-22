//
// Created by raphael on 22/09/18.
//

#include <memory>
#include <thread>
#include "sound/Microphone.hpp"
#include "sound/Speaker.hpp"


int main()
{
    std::unique_ptr<sound::Microphone>  mic(new sound::Microphone());
    std::unique_ptr<sound::Speaker>  speak(new sound::Speaker());

    if (!mic)
        return (84);
    mic->start();
    speak->start();
    for (int i = 0;i < 100;i++){
        std::vector<SAMPLE> tmp = mic->getCopyRecords();
        speak->addFrames(tmp);
        mic->removeRecords(tmp.size());
        Pa_Sleep(100);
    }
    mic->stop();
    speak->stop();
    Pa_Terminate();
    return (0);
}