#include "stm32l0xx_hal.h"
#include "reduced_hal.h"

static void TIM_CCxChannelCmd(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ChannelState)
{
    uint32_t tmp;

    /* Check the parameters */
    assert_param(IS_TIM_CC1_INSTANCE(TIMx));
    assert_param(IS_TIM_CHANNELS(Channel));

    tmp = TIM_CCER_CC1E << (Channel & 0x1FU); /* 0x1FU = 31 bits max shift */

    /* Reset the CCxE Bit */
    TIMx->CCER &= ~tmp;

    /* Set or reset the CCxE Bit */
    TIMx->CCER |= (uint32_t)(ChannelState << (Channel & 0x1FU)); /* 0x1FU = 31 bits max shift */
}

void tim_base_start(TIM_HandleTypeDef *htim)
{
    htim->State = HAL_TIM_STATE_BUSY;
    __HAL_TIM_ENABLE(htim);
}

void tim_pwm_start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);
    __HAL_TIM_ENABLE(htim);
}