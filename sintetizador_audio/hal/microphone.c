#include "include/microphone.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "pico/stdlib.h"

#define MICROPHONE 28
#define MIC_CHANNEL 2 
#define ADC_CLK_DIV 6000

uint16_t audio_buffer[NUM_SAMPLES];

static int dma_chan;
static dma_channel_config dma_cfg;
static volatile bool recording = false;

void microphone_init() {
    adc_init();
    adc_gpio_init(MICROPHONE);
    adc_select_input(MIC_CHANNEL);
    adc_fifo_setup(true, true, 1, false, false); 
    adc_set_clkdiv(ADC_CLK_DIV);               

    dma_chan = dma_claim_unused_channel(true);
    dma_cfg = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&dma_cfg, DMA_SIZE_16);
    channel_config_set_read_increment(&dma_cfg, false);
    channel_config_set_write_increment(&dma_cfg, true);
    channel_config_set_dreq(&dma_cfg, DREQ_ADC);
}

void microphone_start_recording(uint16_t *buffer) {
    adc_run(false);
    adc_fifo_drain();

    dma_channel_configure(
        dma_chan,
        &dma_cfg,
        buffer,                  
        &adc_hw->fifo,           
        NUM_SAMPLES,
        true                     
    );

    recording = true;
    adc_run(true);
}

void microphone_process_recording() {
    if (recording && dma_channel_is_busy(dma_chan) == false) {
        adc_run(false);
        dma_channel_abort(dma_chan);
        recording = false;
    }
}

bool is_recording() {
    return recording;
}
