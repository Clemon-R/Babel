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
            data->getRecords().push_back(SAMPLE_SILENCE);
            data->getRecords().push_back(SAMPLE_SILENCE);
        }
    }
    else
    {
        for (int i = 0;i < framesPerBuffer;i++)
        {
            data->getRecords().push_back(*mic++);
            data->getRecords().push_back(*mic++);
        }
    }
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
        if (err != paNoError) {
            std::cerr << "microphone: impossible to init the microphone\n";
            return;
        }
        inputParameters.device = Pa_GetDefaultInputDevice();
        if (inputParameters.device == paNoDevice) {
            std::cerr << "microphone: no default input device found\n";
            return;
        }
        inputParameters.channelCount = 2;
        inputParameters.sampleFormat = PA_SAMPLE_TYPE;
        inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
        inputParameters.hostApiSpecificStreamInfo = NULL;
        _record = true;
        err = Pa_OpenStream(
                &_stream,
                &inputParameters,
                nullptr,
                SAMPLE_RATE,
                FRAMES_PER_BUFFER,
                paClipOff,
                recordCallback,
                this);
        if (err != paNoError) {
            std::cerr << "microphone: impossible to init the stream\n";
            return;
        }
        err = Pa_StartStream(_stream);
        if (err != paNoError) {
            std::cerr << "microphone: impossible to start the stream\n";
            return;
        }
        std::cout << "microphone: on\n";
    }

    void Microphone::stop()
    {
        _record = false;
        if(Pa_CloseStream(_stream) != paNoError) {
            std::cerr << "microphone: error while closing\n";
            return;
        }
        _stream = nullptr;
        std::cout << "microphone: off\n";
    }

    bool Microphone::isRecording()
    {
        return (_record && _stream);
    }

    std::vector<SAMPLE>  &Microphone::getRecords()
    {
        return (_records);
    }

    std::vector<SAMPLE>  Microphone::getCopyRecords()
    {
        std::vector<SAMPLE> result;

        _lock.lock();
        result = _records;
        _lock.unlock();
        return (result);
    }

    void Microphone::increaseFrameIndexBy(int value)
    {
        _frameIndex += value;
    }

    std::mutex  &Microphone::getLock()
    {
        return (_lock);
    }

    void Microphone::removeRecords(int size)
    {
        _lock.lock();
        _records.erase(_records.begin(), _records.begin()+size);
        _lock.unlock();
    }
};