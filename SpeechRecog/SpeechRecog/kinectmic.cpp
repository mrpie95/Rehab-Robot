#include "kinectmic.h"

freenect_context* KinectMic::f_ctx;
freenect_device* KinectMic::f_dev;

pthread_mutex_t KinectMic::audiobuf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t KinectMic::audiobuf_cond = PTHREAD_COND_INITIALIZER;

volatile int KinectMic::die = 0;

void in_callback(freenect_device* dev, int num_samples,
                 int32_t* mic1, int32_t* mic2,
                 int32_t* mic3, int32_t* mic4,
                 int16_t* cancelled, void *unknown);

KinectMic::KinectMic() {
    printf("Running\n");
}

void* KinectMic::freenect_threadfunc(void* arg) {
    while(!die && freenect_process_events(f_ctx) >= 0) {
        // If we did anything else in the freenect thread, it might go here.
    }
    freenect_stop_audio(f_dev);
    freenect_close_device(f_dev);
    freenect_shutdown(f_ctx);
    return NULL;
}

void KinectMic::in_callback(freenect_device* dev, int num_samples,
                            int32_t* mic1, int32_t* mic2,
                            int32_t* mic3, int32_t* mic4,
                            int16_t* cancelled, void *unknown) {
    pthread_mutex_lock(&audiobuf_mutex);
    capture* c = (capture*)freenect_get_user(dev);
    if(num_samples < c->max_samples - c->current_idx) {
        memcpy(&(c->buffers[0][c->current_idx]), mic1, num_samples*sizeof(int32_t));
        memcpy(&(c->buffers[1][c->current_idx]), mic2, num_samples*sizeof(int32_t));
        memcpy(&(c->buffers[2][c->current_idx]), mic3, num_samples*sizeof(int32_t));
        memcpy(&(c->buffers[3][c->current_idx]), mic4, num_samples*sizeof(int32_t));
    } else {
        int first = c->max_samples - c->current_idx;
        int left = num_samples - first;
        memcpy(&(c->buffers[0][c->current_idx]), mic1, first*sizeof(int32_t));
        memcpy(&(c->buffers[1][c->current_idx]), mic2, first*sizeof(int32_t));
        memcpy(&(c->buffers[2][c->current_idx]), mic3, first*sizeof(int32_t));
        memcpy(&(c->buffers[3][c->current_idx]), mic4, first*sizeof(int32_t));
        memcpy(c->buffers[0], &mic1[first], left*sizeof(int32_t));
        memcpy(c->buffers[1], &mic2[first], left*sizeof(int32_t));
        memcpy(c->buffers[2], &mic3[first], left*sizeof(int32_t));
        memcpy(c->buffers[3], &mic4[first], left*sizeof(int32_t));
    }
    c->current_idx = (c->current_idx + num_samples) % c->max_samples;
    c->new_data = 1;
    pthread_cond_signal(&audiobuf_cond);
    pthread_mutex_unlock(&audiobuf_mutex);
}

void KinectMic::printToConsole() {
    pthread_mutex_lock(&audiobuf_mutex);
    for (int i = 0; i < 4; i++) {
        printf("Mic %i: %d", i, state.buffers[i][0]);
    }
    pthread_mutex_unlock(&audiobuf_mutex);
}

int KinectMic::init() {
    if (freenect_init(&f_ctx, NULL) < 0) {
        printf("freenect_init() failed\n");
        return 1;
    }
    freenect_set_log_level(f_ctx, FREENECT_LOG_INFO);
    freenect_select_subdevices(f_ctx, FREENECT_DEVICE_AUDIO);

    int nr_devices = freenect_num_devices (f_ctx);
    printf ("Number of devices found: %d\n", nr_devices);
    if (nr_devices < 1) {
        freenect_shutdown(f_ctx);
        return 1;
    }

    int user_device_number = 0;
    if (freenect_open_device(f_ctx, &f_dev, user_device_number) < 0) {
        printf("Could not open device\n");
        freenect_shutdown(f_ctx);
        return 1;
    }

    state.max_samples = 256 * 60;
    state.current_idx = 0;
    state.buffers[0] = (int32_t*)malloc(state.max_samples * sizeof(int32_t));
    state.buffers[1] = (int32_t*)malloc(state.max_samples * sizeof(int32_t));
    state.buffers[2] = (int32_t*)malloc(state.max_samples * sizeof(int32_t));
    state.buffers[3] = (int32_t*)malloc(state.max_samples * sizeof(int32_t));
    memset(state.buffers[0], 0, state.max_samples * sizeof(int32_t));
    memset(state.buffers[1], 0, state.max_samples * sizeof(int32_t));
    memset(state.buffers[2], 0, state.max_samples * sizeof(int32_t));
    memset(state.buffers[3], 0, state.max_samples * sizeof(int32_t));
    freenect_set_user(f_dev, &state);

    freenect_set_audio_in_callback(f_dev, in_callback);
    freenect_start_audio(f_dev);

    int res = pthread_create(&freenect_thread, NULL, freenect_threadfunc, NULL);
    if (res) {
        printf("pthread_create failed\n");
        freenect_shutdown(f_ctx);
        return 1;
    }
    printf("This is the libfreenect microphone waveform viewer.  Press 'q' to quit or spacebar to pause/unpause the view.\n");
    return 0;
}
