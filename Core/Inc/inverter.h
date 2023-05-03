#pragma once
#include "stdint.h"
#include "stm32l4xx_hal.h"

#define INV_PRESCALER 0
#define INV_MAX_PWM_PULSE_VAL 1000

typedef struct POLE
{
    TIM_HandleTypeDef * timer_handler;
    uint32_t channel;
    uint16_t width;
} pole_t;

typedef struct INVERTER
{
    TIM_OC_InitTypeDef oc_config;


    pole_t poles_high[3];
    pole_t poles_low[3];






} inverter_t;


void inv_init(inverter_t * inverter);

void set_pulses(inverter_t *  inverter);