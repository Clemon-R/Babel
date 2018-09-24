//
// Created by raphael on 22/09/18.
//

#include "Microphone.hpp"
#include "../Exception.hpp"

static int  recordCallback(const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData)
{
    sound::Microphone  *data = (sound::Microphone *)userData;
    const SAMPLE    *mic = (const SAMPLE *)inputBuffer;
    std::vector<SAMPLE> result;

    (void)outputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    if (!data || !data->isRecording())
        return (paComplete);
    data->getLock().lock();
    if (inputBuffer == NULL)
    {
        for (int i = 0;i < framesPerBuffer;i++)
        {
            result.push_back(SAMPLE_SILENCE);
            if (CHANNELS == 2)
                result.push_back(SAMPLE_SILENCE);
        }
    } else {
        for (int i = 0;i < framesPerBuffer;i++)
        {
            result.push_back(*mic++);
            if (CHANNELS == 2)
                result.push_back(*mic++);
        }
    }
    data->getRecords().push_back(result);
    std::cout << "microphone: nbr frame - " << result.size() << std::endl;
    data->getLock().unlock();
    data->increaseFrameIndexBy(framesPerBuffer);
    return (paContinue);
}

namespace sound
{
    Microphone::Microphone() : _record(false), _stream(nullptr)
    {
        std::cout << "microphone: init...\n";
        std::cout << "microphone: initiated\n";
    }

    Microphone::~Microphone()
    {
        std::cout << "microphone: destroying...\n";
        if (isRecording())
            stop();
        std::cout << "microphone: destroyed\n";
    }

    void Microphone::start()
    {
        PaStreamParameters  inputParameters;
        PaError             err = paNoError;

        _frameIndex = 0;
        _records.clear();
        err = Pa_Initialize();
        if (err != paNoError)
            throw Exception("microphone: impossible to init the microphone");
        inputParameters.device = Pa_GetDefaultInputDevice();
        if (inputParameters.device == paNoDevice)
            throw Exception("microphone: no default input device found");
        inputParameters.channelCount = CHANNELS;
        inputParameters.sampleFormat = PA_SAMPLE_TYPE;
        inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
        inputParameters.hostApiSpecificStreamInfo = NULL;
        _record = true;
        err = Pa_OpenStream(
                &_stream,
                &inputParameters,
                nullptr,
                SAMPLE_RATE,
                SAMPLE_SIZE,
                paClipOff,
                recordCallback,
                this);
        if (err != paNoError)
            throw Exception("microphone: impossible to init the stream");
        err = Pa_StartStream(_stream);
        if (err != paNoError)
            throw Exception("microphone: impossible to start the stream");
        std::cout << "microphone: on\n";
    }

    void Microphone::stop()
    {
        _record = false;
        if(Pa_CloseStream(_stream) != paNoError)
            throw Exception("microphone: error while closing");
        _stream = nullptr;
        std::cout << "microphone: off\n";
    }

    bool Microphone::isRecording()
    {
        return (_record && _stream);
    }

    std::vector<std::vector<SAMPLE>>  &Microphone::getRecords()
    {
        return (_records);
    }

    void Microphone::increaseFrameIndexBy(int value)
    {
        _frameIndex += value;
    }

    std::mutex  &Microphone::getLock()
    {
        return (_lock);
    }

    std::vector<SAMPLE> Microphone::getNextSample()
    {
        std::vector<std::vector<SAMPLE>>::iterator   current = _records.begin();
        std::vector<SAMPLE> result;

        if (current == _records.end() || current->size() < SAMPLE_SIZE*CHANNELS)
            return (result);
        _lock.lock();
        result = *current;
        _records.erase(current);
        _lock.unlock();
        return (result);
    }
};