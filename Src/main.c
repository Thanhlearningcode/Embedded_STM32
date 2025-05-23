#include "Gpio.h"
#include "stm32f4xx.h"
#include "Uart_Builder.h"
#include <stdio.h>

void delay(volatile uint32_t count) {
    while(count--) {
        __NOP();
    }
}

   

int main(void) {
    GPIOA_Pin5_Output_Init();
    Uart_Builder builder = UART_Builder_Init();
   
          // Configure UART using the Builder
      Uart_Config_t uartConfig = builder
    .setBaudrate(&builder, 115200)
    ->setParity(&builder, 0)
    ->setStopBits(&builder, 1)
    ->setDataBits(&builder, 8)
    ->build(&builder);

         // Print the configured UART parameters
          while(1) {
 
     //   GPIOA_Pin5_Toggle();
        delay(1000000);
    }
}
