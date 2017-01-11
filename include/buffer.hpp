#ifndef AUDIO_BUFFER_HPP
#define AUDIO_BUFFER_HPP
#include <string>
#include <AL/al.h>

class AudioBuffer
{
public:
    AudioBuffer(std::string filename);
    ~AudioBuffer();

    ALuint getId();
private:
    ALuint m_id;
};
#endif
