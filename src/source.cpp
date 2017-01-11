#include "source.hpp"

AudioSource::AudioSource()
{
    alGenSources(1, &m_id);
}

AudioSource::~AudioSource()
{
    alDeleteSources(1, &m_id);
}

void AudioSource::setBuffer(AudioBuffer& buffer)
{
    alSourcei(m_id, AL_BUFFER, buffer.getId());
}

void AudioSource::play()
{
    alSourcePlay(m_id);
}

bool AudioSource::isPlaying()
{
    ALint state;
    alGetSourcei(m_id, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}
