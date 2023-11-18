#include<stdio.h>
#include<sdkconfig.h>
#include<esp_system.h>
#include <freertos/FreeRTOS.h>
#include<freertos/task.h>
#include "driver/gpio.h"
#include"driver/adc.h"
#include "rom/gpio.h"
#include"driver/i2c.h"          
#define PIN 2
#define ADC_PIN ADC1_CHANNEL_7
#define SDA GPIO_NUM_21
#define SCL GPIO_NUM_22
#define Led GPIO_NUM_32
void app_main() {

gpio_set_direction(Led,GPIO_MODE_OUTPUT); 
adc1_config_width(ADC_WIDTH_BIT_12);
adc1_config_channel_atten(ADC_PIN,ADC_ATTEN_DB_11);
uint32_t value;
while(1){
value=adc1_get_raw(ADC_PIN);
float temperature=(value/4095.0)*3300.0;
temperature=temperature/10.0;
printf("Temperature: %.2f°C\n", temperature);
vTaskDelay(pdMS_TO_TICKS(1000));
if(temperature>19){
gpio_set_level(Led,1);
vTaskDelay(pdMS_TO_TICKS(100));
gpio_set_level(Led,0);

}
else
{
    gpio_set_level(Led,0);
}
}
}
