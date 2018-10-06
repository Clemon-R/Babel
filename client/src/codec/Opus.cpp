//
// Created by raphael on 23/09/18.
//

#include "Opus.hpp"
#include "../Exception.hpp"

Opus::Opus() : _decoder(nullptr), _encoder(nullptr)
{
    int err;

    std::cout << "opus: init encoder/decoder...\n";
    _encoder = opus_encoder_create(SAMPLE_RATE, CHANNELS, APPLICATION, &err);
    if (err < 0)
        throw Exception("opus: impossible to init the encoder\n" + std::string(opus_strerror(err)));
    _decoder = opus_decoder_create(SAMPLE_RATE, CHANNELS, &err);
    if (err < 0)
        throw Exception("opus: impossible to init the decoder\n" + std::string(opus_strerror(err)));
    std::cout << "opus: initiated\n";
}

Opus::~Opus()
{
    std::cout << "opus: destroying...\n";
    if (_encoder)
        opus_encoder_destroy(_encoder);
    if (_decoder)
        opus_decoder_destroy(_decoder);
    std::cout << "opus: destroyed\n";
}

std::tuple<unsigned char *, int>    Opus::encode(const std::vector<SAMPLE> &values)
{
    int nbBytes = 0;
    int i = 0;
    float   *in = new float[values.size()];
    unsigned char   *result = new unsigned char[MAX_PACKET_SIZE];

	;
    if (!_encoder)
        throw Exception("opus: no encoder initiated");
    else if (values.size() != SAMPLE_SIZE*CHANNELS || values.size() == 0)
        return (std::tuple<unsigned char *, int>(nullptr, 0));
    for (const SAMPLE value : values)
        in[i++] = value;
    nbBytes = opus_encode_float(_encoder, in, SAMPLE_SIZE, result, MAX_PACKET_SIZE);
	delete[] in;
    std::cout << "opus: nbr of bytes - " << nbBytes << std::endl;
    return (std::tuple<unsigned char *, int>(result, nbBytes));
}

std::vector<SAMPLE> Opus::decode(const std::tuple<unsigned char *, int> &values)
{
    std::vector<SAMPLE> result;
    int frame_size = 0;
    float out[SAMPLE_SIZE*CHANNELS];

    if (!_decoder)
        throw Exception("opus: no decoder initiated");
    if (!std::get<0>(values))
        return (result);
    frame_size = opus_decode_float(_decoder, std::get<0>(values), std::get<1>(values), out, SAMPLE_SIZE, 0);
    if (frame_size < 0)
        throw Exception("opus: error while decoding");
    for (int i = 0;i < SAMPLE_SIZE*CHANNELS;i++)
        result.push_back(out[i]);
    std::cout << "opus: nbr of frames - " << result.size() << std::endl;
    return (result);
}