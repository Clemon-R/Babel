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
    std::vector<std::vector<SAMPLE>>::iterator   it = data->getFrames().begin();

    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    if (!data || !data->isSpeaking())
        return (paComplete);
    else if (it == data->getFrames().end())
        return (paContinue);
    //std::cout << "speaker: nbr frame - " << it->size() << std::endl;
    for (const SAMPLE value : *it){
        *speaker++ = value * data->getVolume();
    }
    data->getLock().lock();
    data->getFrames().erase(it);
    data->getLock().unlock();
    data->increaseFrameIndexBy(framesPerBuffer);
    return (paContinue);
}

namespace sound
{
    Speaker::Speaker(int &volume) : _state(false), _stream(nullptr), _volume(volume)
    {
        //std::cout << "speaker: init...\n";
        //std::cout << "speaker: initiated\n";
    }

    Speaker::~Speaker()
    {
        //std::cout << "speaker: destroying...\n";
        if (isSpeaking())
            stop();
        //std::cout << "speaker: destroyed\n";
    }

    void Speaker::start()
    {
        PaStreamParameters  outputParameters;
        PaError             err = paNoError;

        _frameIndex = 0;
        outputParameters.device = Pa_GetDefaultOutputDevice();
        if (outputParameters.device == paNoDevice)
            throw Exception("speaker: no default device found");
        outputParameters.channelCount = CHANNELS;
        outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;
        _state = true;
        err = Pa_OpenStream(
                &_stream,
                nullptr,
                &outputParameters,
                SAMPLE_RATE,
                SAMPLE_SIZE,
                paClipOff,
                playCallback,
                this);
        if (err != paNoError)
            throw Exception("speaker: impossible to init the stream");
        err = Pa_StartStream(_stream);
        if (err != paNoError)
            throw Exception("speaker: error while starting the stream");
        //std::cout << "speaker: on\n";
    }

    void Speaker::stop()
    {
        _state = false;
        if(Pa_CloseStream(_stream) != paNoError)
            throw Exception("microphone: error while closing");
        _stream = nullptr;
        //std::cout << "speaker: off\n";
    }

    bool Speaker::isSpeaking()
    {
        return (_state && _stream);
    }

    std::vector<std::vector<SAMPLE>> &Speaker::getFrames()
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
        if (values.size() == 0)
            return;
        _lock.lock();
        _frames.push_back(values);
        _lock.unlock();
    }

    const float Speaker::getVolume() const
    {
        return (_volume / 100.0F);
    }
}