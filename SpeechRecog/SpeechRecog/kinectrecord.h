#ifndef KINECTRECORD_H
#define KINECTRECORD_H

#include "libfreenect.h"
#include "libfreenect_audio.h"
#include "timer.h"
#include "speechrecogwrapper.h"
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <string>

// Heavily modified, check this for reference: https://github.com/adamstark/AudioFile/blob/master/AudioFile.cpp
// Checkk around line 562
// P.S. this little shit is little endian
const unsigned char wavheader[] = {
    0x52, 0x49, 0x46, 0x46, // ChunkID = "RIFF"
    0x00, 0x00, 0x00, 0x00, // Chunksize (will be overwritten later)
    0x57, 0x41, 0x56, 0x45, // Format = "WAVE"
    0x66, 0x6d, 0x74, 0x20, // Subchunk1ID = "fmt "
    0x10, 0x00, 0x00, 0x00, // Subchunk1Size = 16
    0x01, 0x00, 0x01, 0x00, // AudioFormat = 1 (linear quantization) | NumChannels = 1
    0x80, 0x3e, 0x00, 0x00, // SampleRate = 16000 Hz
//    0x00, 0xfa, 0x00, 0x00, // ByteRate = SampleRate * NumChannels * BitsPerSample/8 = 64000
    0x00, 0x7d, 0x00, 0x00, // ByteRate = SampleRate * NumChannels * BitsPerSample/8 = 64000
//    0x04, 0x00, 0x20, 0x00, // BlockAlign = NumChannels * BitsPerSample/8 = 4 | BitsPerSample = 32
    0x02, 0x00, 0x10, 0x00, // BlockAlign = NumChannels * BitsPerSample/8 = 4 | BitsPerSample = 16
    0x64, 0x61, 0x74, 0x61, // Subchunk2ID = "data"
    0x00, 0x00, 0x00, 0x00, // Subchunk2Size = NumSamples * NumChannels * BitsPerSample / 8 (will be overwritten later)
};

class KinectRecord
{
private:

    typedef struct {
        FILE* logfiles[4];
        int samples;
    } capture;

    pthread_t freenect_thread;

    static pthread_mutex_t audiobuf_mutex;
    static pthread_cond_t audiobuf_cond;

    static freenect_context* f_ctx;
    static freenect_device* f_dev;
    static int die;

    static int testIndex;
    static Timer timer;

    static const int32_t THRESHOLD = 3500000;
    static const int THRESHOLD_TRIGGER = 15;
    static int thresholdSampleCap;

    static SpeechRecogWrapper speechRecogWrapper;

    enum RecordingState {
        Stop,
        Start,
        Pause,
    };

    static RecordingState recordState;
    static capture state;

    static void in_callback(freenect_device* dev, int num_samples,
                     int32_t* mic1, int32_t* mic2,
                     int32_t* mic3, int32_t* mic4,
                     int16_t* cancelled, void *unknown);

    static void cleanup(int sig);
    static void *keepThreadRunning(void *state);

    static void setupFile();
    static void cleanupFile();
    static bool checkThreshold(int32_t* mic);
    static bool checkTimeOut(int32_t* mic);



public:
    KinectRecord();

    void initialize(void *ptr);
};

#endif // KINECTRECORD_H
