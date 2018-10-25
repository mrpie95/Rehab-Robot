#include "kinectrecord.h"

freenect_context* KinectRecord::f_ctx;
freenect_device* KinectRecord::f_dev;

int KinectRecord::die = 0;
int KinectRecord::testIndex = 0;
Timer KinectRecord::timer;
int KinectRecord::thresholdSampleCap = 0;
KinectRecord::RecordingState KinectRecord::recordState = Stop;
KinectRecord::capture KinectRecord::state;

SpeechRecogWrapper KinectRecord::speechRecogWrapper;

KinectRecord::KinectRecord() {

}

bool KinectRecord::checkThreshold(int32_t* mic) {
    if (mic[0] > THRESHOLD) {
        thresholdSampleCap++;

//        printf("Threshold Cap: %d\n", thresholdSampleCap);
        if (thresholdSampleCap > THRESHOLD_TRIGGER) {
            printf("TRIGGERED!\n");
            thresholdSampleCap = 0;
            timer.resetTimer();
            return true;
        }
    } else {
        if (timer.elapsedTimeSecond() > 2) {
            thresholdSampleCap = 0;
            timer.resetTimer();
            printf("Resetting...\n");
        }
    }
    return false;
}

bool KinectRecord::checkTimeOut(int32_t* mic) {
    if (mic[0] > THRESHOLD) {
        thresholdSampleCap++;

        printf("Threshold Cap: %d\n", thresholdSampleCap);
        if (thresholdSampleCap > THRESHOLD_TRIGGER) {
            printf("TRIGGERED!\n");
            thresholdSampleCap = 0;
            timer.resetTimer();
        }
    } else {
        if (timer.elapsedTimeSecond() > 2) {
            thresholdSampleCap = 0;
            timer.resetTimer();
            printf("Resetting...\n");
            return true;
        }
    }
    return false;
}

void KinectRecord::in_callback(freenect_device* dev, int num_samples,
                 int32_t* mic1, int32_t* mic2,
                 int32_t* mic3, int32_t* mic4,
                 int16_t* cancelled, void *unknown) {
    capture* c = (capture*)freenect_get_user(dev);

    if (recordState == Stop) {
        if (checkThreshold(mic1)) {
            printf("STATE: Start\n");
            recordState = Start;
            setupFile();
            return;
        }
    } else if (recordState == Start) {
        if (checkTimeOut(mic1)) {
            printf("STATE: Stop\n");
            recordState = Stop;
            cleanupFile();
            speechRecogWrapper.transcribe("channel1.wav");
            return;
        }

        // Downsampling from 32bit depth audio to 16bit depth audio
        // Divide each sample by 2^16 = 65536
        int16_t* convertedMic1 = (int16_t*) malloc(num_samples * sizeof(int16_t));
        int32_t temporary;
        for (int i = 0; i < num_samples; i++) {
            temporary = mic1[i] / 65536;
            convertedMic1[i] = (int16_t) temporary;
        }


        fwrite(convertedMic1, 1, num_samples*sizeof(int16_t), c->logfiles[0]);
        fwrite(mic2, 1, num_samples*sizeof(int16_t), c->logfiles[1]);
        fwrite(mic3, 1, num_samples*sizeof(int16_t), c->logfiles[2]);
        fwrite(mic4, 1, num_samples*sizeof(int16_t), c->logfiles[3]);
        c->samples += num_samples;

        if (timer.elapsedTimeSecond() > 7) {
            printf("STATE: Stop\n");
            recordState = Stop;
            cleanupFile();
            speechRecogWrapper.transcribe("channel1.wav");
            return;
        }
    }

//    printf("Sample received.  Total samples recorded: %d\n", c->samples);
}

void KinectRecord::cleanup(int sig) {
    printf("Caught SIGINT, cleaning up\n");
    die = 1;
}

void *KinectRecord::keepThreadRunning(void *args) {
    while(!die && freenect_process_events(f_ctx) >= 0) {
        // If we did anything else, it might go here.
        // Alternately, we might split off another thread
        // to do this loop while the main thread did something
        // interesting.

        printf("It's running?\n");
    }
    printf("DIE!");

    capture *state = (capture*) args;

    // Make the WAV header valid for each of the four files
    int i;
    for(i = 0; i < 4 ; i++) {
        char buf[4];
        fseek(state->logfiles[i], 4, SEEK_SET);
        // Write ChunkSize = 36 + subchunk2size
        int chunksize = state->samples * 4 + 36;
        buf[0] = (chunksize & 0x000000ff);
        buf[1] = (chunksize & 0x0000ff00) >> 8;
        buf[2] = (chunksize & 0x00ff0000) >> 16;
        buf[3] = (chunksize & 0xff000000) >> 24;
        fwrite(buf, 1, 4,state->logfiles[i]);

        fseek(state->logfiles[i], 40, SEEK_SET);
        // Write Subchunk2Size = NumSamples * NumChannels (1) * BitsPerSample/8 (4)
        int subchunk2size = state->samples * 4;
        buf[0] = (subchunk2size & 0x000000ff);
        buf[1] = (subchunk2size & 0x0000ff00) >> 8;
        buf[2] = (subchunk2size & 0x00ff0000) >> 16;
        buf[3] = (subchunk2size & 0xff000000) >> 24;
        fwrite(buf, 1, 4,state->logfiles[i]);
        fclose(state->logfiles[i]);
    }
    pthread_exit(NULL);

    return NULL;
}

void KinectRecord::setupFile() {
    state.samples = 0;
//    for (int i = 1; i <= 4; i++) {
//        std::string filename = "channel" + std::to_string(testIndex + i) + ".wav";
//        const char *cstr = filename.c_str();
//        state.logfiles[i - 1] = fopen(cstr, "wb");
//    }
    state.logfiles[0] = fopen("channel1.wav", "wb");
    state.logfiles[1] = fopen("channel2.wav", "wb");
    state.logfiles[2] = fopen("channel3.wav", "wb");
    state.logfiles[3] = fopen("channel4.wav", "wb");
    fwrite(wavheader, 1, 44, state.logfiles[0]);
    fwrite(wavheader, 1, 44, state.logfiles[1]);
    fwrite(wavheader, 1, 44, state.logfiles[2]);
    fwrite(wavheader, 1, 44, state.logfiles[3]);
    freenect_set_user(f_dev, &state);

//    testIndex += 4;
}

void KinectRecord::cleanupFile() {
    int i;
    for(i = 0; i < 4 ; i++) {
        char buf[4];
        fseek(state.logfiles[i], 4, SEEK_SET);
        // Write ChunkSize = 36 + subchunk2size
        int chunksize = state.samples * 4 + 36;
        buf[0] = (chunksize & 0x000000ff);
        buf[1] = (chunksize & 0x0000ff00) >> 8;
        buf[2] = (chunksize & 0x00ff0000) >> 16;
        buf[3] = (chunksize & 0xff000000) >> 24;
        fwrite(buf, 1, 4,state.logfiles[i]);

        fseek(state.logfiles[i], 40, SEEK_SET);
        // Write Subchunk2Size = NumSamples * NumChannels (1) * BitsPerSample/8 (4)
        int subchunk2size = state.samples * 4;
        buf[0] = (subchunk2size & 0x000000ff);
        buf[1] = (subchunk2size & 0x0000ff00) >> 8;
        buf[2] = (subchunk2size & 0x00ff0000) >> 16;
        buf[3] = (subchunk2size & 0xff000000) >> 24;
        fwrite(buf, 1, 4,state.logfiles[i]);
        fclose(state.logfiles[i]);
    }
}

void KinectRecord::initialize(void *ptr) {
    printf("Kinect thread started...\n");
    if (freenect_init(&f_ctx, NULL) < 0) {
            printf("freenect_init() failed\n");
//            return nullptr;
            return;
    }

    freenect_set_log_level(f_ctx, FREENECT_LOG_SPEW);
    freenect_select_subdevices(f_ctx, FREENECT_DEVICE_AUDIO);

    int nr_devices = freenect_num_devices (f_ctx);
    printf ("Number of devices found: %d\n", nr_devices);
    if (nr_devices < 1) {
        freenect_shutdown(f_ctx);
        return;
    }

    int user_device_number = 0;
    if (freenect_open_device(f_ctx, &f_dev, user_device_number) < 0) {
        printf("Could not open device\n");
        freenect_shutdown(f_ctx);
        return;
    }

    freenect_set_audio_in_callback(f_dev, in_callback);
    freenect_start_audio(f_dev);
    signal(SIGINT, cleanup);

//    int status = pthread_create(&freenect_thread, NULL, &keepThreadRunning, (void*) &state);
//    printf("Kinect Audio Thread Running Status: %d\n", status);
    while(!die && freenect_process_events(f_ctx) >= 0) {
        // If we did anything else, it might go here.
        // Alternately, we might split off another thread
        // to do this loop while the main thread did something
        // interesting.
    }

    // Make the WAV header valid for each of the four files
//    int i;
//    for(i = 0; i < 4 ; i++) {
//        char buf[4];
//        fseek(state.logfiles[i], 4, SEEK_SET);
//        // Write ChunkSize = 36 + subchunk2size
//        int chunksize = state.samples * 4 + 36;
//        buf[0] = (chunksize & 0x000000ff);
//        buf[1] = (chunksize & 0x0000ff00) >> 8;
//        buf[2] = (chunksize & 0x00ff0000) >> 16;
//        buf[3] = (chunksize & 0xff000000) >> 24;
//        fwrite(buf, 1, 4,state.logfiles[i]);

//        fseek(state.logfiles[i], 40, SEEK_SET);
//        // Write Subchunk2Size = NumSamples * NumChannels (1) * BitsPerSample/8 (4)
//        int subchunk2size = state.samples * 4;
//        buf[0] = (subchunk2size & 0x000000ff);
//        buf[1] = (subchunk2size & 0x0000ff00) >> 8;
//        buf[2] = (subchunk2size & 0x00ff0000) >> 16;
//        buf[3] = (subchunk2size & 0xff000000) >> 24;
//        fwrite(buf, 1, 4,state.logfiles[i]);
//        fclose(state.logfiles[i]);
//    }

    freenect_shutdown(f_ctx);
    return;
}
