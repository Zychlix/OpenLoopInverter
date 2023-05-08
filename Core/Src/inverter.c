//
// Created by michal on 03.05.23.
//

#include "inverter.h"
#include "resolver.h"

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

void inv_set_pulses(inverter_t *  inverter)
{
    for(int i = 0 ; i< 3; i++)
    {
        __HAL_TIM_SET_COMPARE(inverter->poles[i].timer_handler, inverter->poles[i].channel, inverter->poles[i].width);

    }

}

void inv_set_power(inverter_t* inverter, uint8_t phase_number, int32_t power)
{
    if(phase_number>2)
    {
        return;
    }

        inverter->poles[phase_number].width = (1000 + (uint16_t)power) / 2 * INV_MAX_PWM_PULSE_VAL / 1000;

    inv_set_pulses(inverter);

}


void inv_voltage_vector_apply(inverter_t * inverter, vector_t * vector)
{
    uint32_t power = 200*(uint32_t)vector->value;
    uint32_t pwm;

    pwm = (uint16_t)(power*sin(vector->argument));
    inv_set_power(inverter,0,pwm);

    pwm = ((uint16_t)(power*sin(vector->argument+3.1415*2/3)));
    inv_set_power(inverter,1,pwm);

    pwm = ((uint16_t)(power*sin(vector->argument+3.1415*4/3)));
    inv_set_power(inverter,2,pwm);
}


void res_read_position(resolver_t * res)
{
    HAL_GPIO_WritePin(RD_RES_PORT,RD_RES_PIN,0);
    HAL_GPIO_WritePin(SAMPLE_RES_PORT,SAMPLE_RES_PIN,0);

    //HAL_Delay(1);
    uint8_t data[2];
    HAL_SPI_Receive(res->spi_handler,&data,2,10);
    HAL_GPIO_WritePin(RD_RES_PORT,RD_RES_PIN,1);
    uint16_t pos = ((data[1]<<8)|(data[0]&0b11110000))>>4;
    res->position = pos;
//    HAL_GPIO_WritePin(RDVEL_GPIO_Port,RDVEL_RES_PIN,0);
//    HAL_GPIO_WritePin(RD_RES_PORT,RD_RES_PIN,0);
//    //HAL_SPI_Receive(res->spi_handler,&data,2,10);
//    uint16_t speed = ((data[1]<<8)|(data[0]&0b11110000))>>4&0b11111111111;
//
//    res->speed=speed;
//    HAL_GPIO_WritePin(RD_RES_PORT,RD_RES_PIN,1);

}