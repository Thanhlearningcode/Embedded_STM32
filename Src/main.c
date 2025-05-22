#include "Gpio.h"
#include "stm32f4xx.h"

void delay(volatile uint32_t count) {
    while(count--) {
        __NOP();
    }
}

int main(void) {
    GPIOA_Pin5_Output_Init();

    while(1) {
     //   GPIOA_Pin5_Toggle();
        delay(1000000);
    }
}
