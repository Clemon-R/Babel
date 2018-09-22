//
// Created by raphael on 22/09/18.
//

#include "Speaker.hpp"
#include "../Exception.hpp"

static int playCallback( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData )
{
    sound::Speaker  *data = (sound::Speaker *)userData;
    SAMPLE  *speaker = (SAMPLE*)outputBuffer;
    std::vector<SAMPLE>::iterator   it = data->getFrames().begin();

    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    if (!data || !data->isSpeaking())
        return (paComplete);
    else if (data->getFrames().size() == 0 || data->getFrames().size() < framesPerBuffer)
        return (paContinue);
    data->getLock().lock();
    for (int i = 0;i < framesPerBuffer;i++){
        if (it != data->getFrames().end()){
            *speaker++ = *it++;
            *speaker++ = *it++;
        }
    }
    it--;
    data->getFrames().erase(data->getFrames().begin(), it);
    data->getLock().unlock();
    data->increaseFrameIndexBy(framesPerBuffer);
    return (paContinue);
}

namespace sound
{
    Speaker::Speaker() : _stream(nullptr), _state(false)
    {
        std::cout << "speaker: init...\n";
        std::cout << "speaker: initiated\n";
    }

    Speaker::~Speaker()
    {
        std::cout << "speaker: destroying...\n";
        if (isSpeaking())
            stop();
        std::cout << "speaker: destroyed\n";
    }

    void Speaker::start()
    {
        PaStreamParameters  outputParameters;
        PaError             err = paNoError;

        _frameIndex = 0;
        outputParameters.device = Pa_GetDefaultOutputDevice();
        if (outputParameters.device == paNoDevice)
            throw Exception("speaker: no default device found");
        outputParameters.channelCount = 2;
        outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;
        _state = true;
        err = Pa_OpenStream(
                &_stream,
                nullptr,
                &outputParameters,
                SAMPLE_RATE,
                FRAMES_PER_BUFFER,
                paClipOff,
                playCallback,
                this);
        if (err != paNoError)
            throw Exception("speaker: impossible to init the stream");
        err = Pa_StartStream(_stream);
        if (err != paNoError)
            throw Exception("speaker: error while starting the stream");
        std::cout << "speaker: on\n";
    }

    void Speaker::stop()
    {
        _state = false;
        if(Pa_CloseStream(_stream) != paNoError)
            throw Exception("microphone: error while closing");
        _stream = nullptr;
        std::cout << "speaker: off\n";
    }

    bool Speaker::isSpeaking()
    {
        return (_state && _stream);
    }

    std::vector<SAMPLE> &Speaker::getFrames()
    {
        return (_frames);
    }

    void Speaker::increaseFrameIndexBy(int value)
    {
        _frameIndex += value;
    }

    std::mutex  &Speaker::getLock()
    {
        return (_lock);
    }

    void    Speaker::addFrames(std::vector<SAMPLE> &values)
    {
        _lock.lock();
        for (SAMPLE sound : values){
            _frames.push_back(sound);
        }
        _lock.unlock();
    }
}