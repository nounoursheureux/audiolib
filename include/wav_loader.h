#ifndef WAV_LOADER_H
#define WAV_LOADER_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <AL/al.h>

int load_wav(const char* filepath, ALenum* format, ALvoid** data, ALsizei* size, ALsizei* freq)
{
    FILE* fp = fopen(filepath, "rb");
    fseek(fp, 0, SEEK_END);
    size_t filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    unsigned char* buf = (unsigned char*)malloc(sizeof(unsigned char) * filesize);
    fread(buf, 1, filesize, fp);
    if (buf[0] != 'R' || buf[1] != 'I' || buf[2] != 'F' || buf[3] != 'F') {
        fclose(fp);
        free(buf);
        return 1;
    }
    /* int32_t size = buf[4] | (buf[5] << 8) | (buf[6] << 16) | (buf[7] << 24);
    printf("Size: %d\n", size);
    if (buf[8] != 'W' || buf[9] != 'A' || buf[10] != 'V' || buf[11] != 'E') {
        fclose(fp);
        free(buf);
        return 1;
    } */

    if (buf[12] != 0x66 || buf[13] != 0x6D || buf[14] != 0x74 || buf[15] != 0x20) {
        fclose(fp);
        free(buf);
        return 1;
    }

    int32_t block_size = buf[16] | (buf[17] << 8) | (buf[18]<<16) | (buf[19]<<24);
    printf("Block size: %d\n", block_size);

    int16_t audio_format = buf[20] | (buf[21] << 16);
    printf("Audio format: %d\n", audio_format);

    int16_t channels = buf[22] | (buf[23]<<8);
    printf("Channels: %d\n", channels);

    int32_t sample_rate = buf[24] | (buf[25]<<8) | (buf[26]<<16) | (buf[27]<<24);
    printf("Sample rate: %d\n", sample_rate);

    int32_t bytes_per_sec = buf[28] | (buf[29]<<8) | (buf[30]<<16) | (buf[31]<<24);
    printf("Bytes per sec: %d\n", bytes_per_sec);

    int16_t bytes_per_block = buf[32] | (buf[33]<<8);
    printf("Bytes per block: %d\n", bytes_per_block);

    int16_t bits_per_sample = buf[34] | (buf[35]<<8);
    printf("Bits per sample: %d\n", bits_per_sample);

    if (buf[36] != 'd' || buf[37] != 'a' || buf[38] != 't' || buf[39] != 'a') {
        fclose(fp);
        free(buf);
        return 1;
    }

    int32_t data_size = buf[40] | (buf[41]<<8) | (buf[42]<<16) | (buf[43]<<24);
    printf("Data size: %d\n", data_size);

    if (channels == 1) {
        if (bits_per_sample == 8) {
            *format = AL_FORMAT_MONO8;
        } else if (bits_per_sample == 16) {
            *format = AL_FORMAT_MONO16;
        }
    } else if (channels == 2) {
        if (bits_per_sample == 8) {
            *format = AL_FORMAT_STEREO8;
        } else if (bits_per_sample == 16) {
            *format = AL_FORMAT_STEREO16;
        }
    }
    *data = &buf[44];
    *size = data_size;
    *freq = sample_rate;
    fclose(fp);
    return 0;
};
#endif
