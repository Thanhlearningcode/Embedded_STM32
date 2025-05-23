#include "Gpio.h"
#include "Uart_Builder.h"
#include <stdio.h>

void delay(volatile uint32_t count) {
    while(count--) {
        __NOP();
    }
}

 extern void UART1_Config(Uart_Config_t config);  

int main(void) 
{
    GPIOA_Pin5_Output_Init();
    Uart_Builder builder = UART_Builder_Init();
   

    Uart_Config_t config = builder
        .setBaudrate(&builder, 115200)
        ->setParity(&builder, 0)
        ->setStopBits(&builder, 1)
        ->setDataBits(&builder, 8)
        ->build(&builder);

    UART1_Config(config);
    UART1_SendString("UART Ready!\r\n");
         // Print the configured UART parameters
          while(1) {
    char c = UART1_ReceiveChar();  // Nhận ký tự từ terminal
    UART1_SendChar(c);             // Phản hồi lại
     //   GPIOA_Pin5_Toggle();
        delay(1000000);
    }
}
