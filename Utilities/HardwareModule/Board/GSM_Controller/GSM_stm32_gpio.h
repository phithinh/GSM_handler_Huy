/*
 * GSM_stm32_gpio.h
 *
 *  Created on: Mar 28, 2015
 *      Author: phi thinh
 */

#ifndef GSM_STM32_GPIO_H_
#define GSM_STM32_GPIO_H_

#ifndef BOOL
#define BOOL unsigned char
#endif

BOOL GSM_GetStatusPort_b(void);
void GSM_SetResetPort_v(BOOL p_state_b);
void GSM_SetOnOffPort_v(BOOL p_state_b);


//#ifndef Bit_RESET
//#define Bit_RESET	0
//#endif
//
//#ifndef Bit_SET
//#define Bit_SET		1
//#endif

#endif /* GSM_STM32_GPIO_H_ */
