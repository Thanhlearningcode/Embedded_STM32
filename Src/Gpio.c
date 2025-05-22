#include "Gpio.h"

void GPIOA_CLK_ENABLE(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Bật clock GPIOA
}

void GPIOA_Pin5_Output_Init(void) {
    GPIOA_CLK_ENABLE();

    // Cấu hình PA5 thành output
    GPIOA->MODER &= ~(0x3 << (5 * 2));    // reset 2 bit mode của PA5
    GPIOA->MODER |=  (0x1 << (5 * 2));    // mode output (01)

    GPIOA->OTYPER &= ~(1 << 5);           // Output push-pull
    GPIOA->OSPEEDR |= (0x3 << (5 * 2));   // tốc độ cao
    GPIOA->PUPDR &= ~(0x3 << (5 * 2));    // không kéo lên kéo xuống (No pull-up/pull-down)
}

void GPIOA_Pin5_Toggle(void) {
    GPIOA->ODR ^= (1 << 5);  // Đảo trạng thái PA5
}
