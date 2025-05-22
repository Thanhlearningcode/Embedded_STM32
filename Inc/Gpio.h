#ifndef GPIO_H
#define GPIO_H

#include "stm32f4xx.h"

void GPIOA_CLK_ENABLE(void);
void GPIOA_Pin5_Output_Init(void);
void GPIOA_Pin5_Toggle(void);

#endif // GPIO_H
