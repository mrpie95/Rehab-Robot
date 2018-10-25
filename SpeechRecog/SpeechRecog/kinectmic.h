#pragma once

#include "libfreenect.h"
#include "libfreenect_audio.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class KinectMic {

private:
  pthread_t freenect_thread;
  static volatile int die;

  static freenect_context* f_ctx;
  static freenect_device* f_dev;

  typedef struct {
    int32_t* buffers[4];
    int max_samples;
    int current_idx;  // index to the oldest data in the buffer (equivalently, where the next new data will be placed)
    int new_data;
  } capture;

  capture state;

  static pthread_mutex_t audiobuf_mutex;
  static pthread_cond_t audiobuf_cond;

  static void in_callback(freenect_device* dev, int num_samples,
                   int32_t* mic1, int32_t* mic2,
                   int32_t* mic3, int32_t* mic4,
                   int16_t* cancelled, void *unknown);

  static void* freenect_threadfunc(void* arg);

public:
  KinectMic();

  int init();
  void printToConsole();
};
