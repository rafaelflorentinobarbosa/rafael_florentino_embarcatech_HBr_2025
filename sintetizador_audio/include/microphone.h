#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <stdint.h>
#include <stdbool.h>

#define SAMPLE_RATE 8000
#define NUM_SAMPLES (SAMPLE_RATE * 3)

extern uint16_t audio_buffer[NUM_SAMPLES];

void microphone_init();
void microphone_start_recording(uint16_t *buffer);
void microphone_process_recording();
bool is_recording();

#endif