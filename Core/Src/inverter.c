//
// Created by michal on 03.05.23.
//

#include "inverter.h"

void inv_init(inverter_t * inverter)
{
    inverter->oc_config.OCMode       = TIM_OCMODE_PWM1;
    inverter->oc_config.OCPolarity   = TIM_OCPOLARITY_HIGH;
    inverter->oc_config.OCFastMode   = TIM_OCFAST_DISABLE;
    inverter->oc_config.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
    inverter->oc_config.OCNIdleState = TIM_OCNIDLESTATE_RESET;

    inverter->oc_config.OCIdleState  = TIM_OCIDLESTATE_RESET;

    /* Set the pulse value for channel 1 */

    for(int i = 0 ; i< 3; i++)
    {
        HAL_TIM_PWM_ConfigChannel(inverter->poles_high[i].timer_handler,&inverter->oc_config,inverter->poles_low[i].channel);
        HAL_TIM_PWM_Start(inverter->poles_high[i].timer_handler,inverter->poles_low[i].channel);
    }

    for(int i = 0 ; i< 3; i++)
    {
        HAL_TIM_PWM_ConfigChannel(inverter->poles_low[i].timer_handler,&inverter->oc_config,inverter->poles_low[i].channel);
    }

//   HAL_TIM_PWM_Start(inverter->high_side_timer,TIM_CHANNEL_1);
//    HAL_TIM_PWM_Start(inverter->high_side_timer,TIM_CHANNEL_2);
//    HAL_TIM_PWM_Start(inverter->high_side_timer,TIM_CHANNEL_3);


}

void set_pulses(inverter_t *  inverter)
{
    for(int i = 0 ; i< 3; i++)
    {
        __HAL_TIM_SET_COMPARE(inverter->poles_high[i].timer_handler,inverter->poles_high[i].channel,inverter->poles_high[i].width);

    }

    for(int i = 0 ; i< 3; i++)
    {
        __HAL_TIM_SET_COMPARE(inverter->poles_low[i].timer_handler,inverter->poles_low[i].channel,inverter->poles_low[i].width);

    }
//   inverter->high_side_timer->Instance->CCR1 = inverter->high_side_pulse[0];
//    inverter->high_side_timer->Instance->CCR2 = inverter->high_side_pulse[1];
//    inverter->high_side_timer->Instance->CCR3 = inverter->high_side_pulse[2];

//    inverter->oc_config.Pulse = inverter->high_side_pulse[1];
//   // HAL_TIM_PWM_ConfigChannel(&inverter->high_side_timer, &inverter->oc_config, TIM_CHANNEL_2); //Change those tim channels!
//
//    inverter->oc_config.Pulse = inverter->high_side_pulse[2];
//    //HAL_TIM_PWM_ConfigChannel(&inverter->high_side_timer, &inverter->oc_config, TIM_CHANNEL_3); //Change those tim channels!


}