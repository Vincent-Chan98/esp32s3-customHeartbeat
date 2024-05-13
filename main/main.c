#include <stdio.h>
#include "esp_timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <sdkconfig.h>
#include "esp_system.h"
#include "freertos/task.h"
#include "hal/twai_hal.h"
#include "hal/twai_types.h"
#include "driver/twai.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_vfs_fat.h"

static const twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)12,(gpio_num_t)14,TWAI_MODE_NORMAL);
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_25KBITS();
static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

#define BEAT GPIO_NUM_15
bool can_flag = false;
unsigned char msg[8] = {0xAA, 0xBB, 0xFF, 0xC6, 0x12, 0x88, 0xDE, 0xB0};

twai_message_t tx_message;
esp_err_t err, ren, errn;

// void heartbeat_timer(void)
// {
//     static int64_t heartbeat_last_1ms_time = 0;
//     static int heartbeat_10ms_time = 0;
//     static int heartbeat_100ms_time = 0;
//     static int heartbeat_1s_time = 0;
//     while ((esp_timer_get_time()-heartbeat_last_1ms_time)>=1000)
//     {
//         heartbeat_last_1ms_time += 1000;
//         static int heartbeat = 0;
//         heartbeat ^= 1;
//         gpio_set_level(BEAT, heartbeat);
//         heartbeat_10ms_time ++;        if (heartbeat_10ms_time >= 10){heartbeat_10ms_time = 0;}
//         heartbeat_100ms_time ++;        if (heartbeat_100ms_time >= 100){heartbeat_100ms_time = 0;}
//         heartbeat_1s_time ++;        if (heartbeat_1s_time >= 1000){heartbeat_1s_time = 0;}
//     }
// }

void light()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BEAT),
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&io_conf);
    gpio_set_direction(BEAT, GPIO_MODE_OUTPUT);
    while (1)
    {
        if (can_flag == true){gpio_set_level(BEAT, 1);vTaskDelay(50/portTICK_RATE_MS);gpio_set_level(BEAT, 0);vTaskDelay(50/portTICK_RATE_MS);}
        else{gpio_set_level(BEAT, 1);vTaskDelay(500/portTICK_RATE_MS);gpio_set_level(BEAT, 0);vTaskDelay(500/portTICK_RATE_MS);}
    }
}

void can_send(void *pvParameter)
{
    twai_driver_install(&g_config, &t_config, &f_config);
    twai_start();
    tx_message.extd = 0; tx_message.identifier = 0x8; tx_message.data_length_code = 8;
    while (1)
    {
        for (int i = 0; i < 8; i++){tx_message.data[i] = msg[i];}  
        err = twai_transmit(&tx_message, pdMS_TO_TICKS(100));
        if (err == ESP_OK){can_flag = true;}else{can_flag = false;}
        vTaskDelay(100/portTICK_RATE_MS);
    }
}

void app_main(void)
{
    ren = nvs_flash_init();
    if (ren == ESP_ERR_NVS_NO_FREE_PAGES || ren == ESP_ERR_NVS_NEW_VERSION_FOUND) {errn = nvs_flash_init();}
    ESP_ERROR_CHECK(errn); 
    xTaskCreatePinnedToCore(&can_send, "csend", 2048, NULL, 1, NULL, 1);
    light();
}
