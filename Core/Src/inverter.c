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
        HAL_TIM_PWM_ConfigChannel(inverter->poles[i].timer_handler, &inverter->oc_config, inverter->poles[i].channel);
        HAL_TIM_PWM_Start(inverter->poles[i].timer_handler, inverter->poles[i].channel);
        HAL_TIMEx_PWMN_Start(inverter->poles[i].timer_handler, inverter->poles[i].channel);

    }


}

void set_pulses(inverter_t *  inverter)
{
    for(int i = 0 ; i< 3; i++)
    {
        __HAL_TIM_SET_COMPARE(inverter->poles[i].timer_handler, inverter->poles[i].channel, inverter->poles[i].width);

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

void inv_set_power(inverter_t* inverter, uint8_t phase_number, int32_t power)
{
    if(phase_number>2)
    {
        return;
    }

        inverter->poles[phase_number].width = (1000 + power) / 2 * INV_MAX_PWM_PULSE_VAL / 1000;

    set_pulses(inverter);

}