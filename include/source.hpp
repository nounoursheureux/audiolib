#ifndef AUDIO_SOURCE_HPP
#define AUDIO_SOURCE_HPP
#include <AL/al.h>
#include "buffer.hpp"

class AudioSource
{
public:
    AudioSource();
    ~AudioSource();
    void setBuffer(AudioBuffer& buffer);
    void play();
    bool isPlaying();

private:
    ALuint m_id;
};
#endif
