#include "buffer.hpp"
#include "wav_loader.h"

AudioBuffer::AudioBuffer(std::string filename)
{
    alGenBuffers(1, &m_id);
    ALsizei size, freq;
    ALenum format;
    ALvoid* data;
    load_wav(filename.c_str(), &format, &data, &size, &freq);
    alBufferData(m_id, format, data, size, freq);
}

AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(1, &m_id);
}

ALuint AudioBuffer::getId()
{
    return m_id;
}
