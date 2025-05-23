#ifndef _UART_BUILDER_H_
#define _UART_BUILDER_H_

#include <stdint.h>
/* UART Configuration Structure */ 
typedef struct 
{
    uint32_t baudRate; // Baud rate (e.g., 9600, 115200)
    uint8_t parity;  // 0: None, 1: Odd, 2: Even
    uint8_t stopBits;   // 1: 1 Stop Bit, 2: 2 Stop Bits
    uint8_t dataBits;   // 8: 8 Data Bits, 9: 9 Data Bits
} Uart_Config_t;

// UART Builder Structure
typedef struct Uart_Builder
{
    Uart_Config_t config;

    struct Uart_Builder*  (*setBaudrate)(struct Uart_Builder*, uint32_t);
    struct Uart_Builder*  (*setParity)  (struct Uart_Builder*, uint8_t);
    struct Uart_Builder*  (*setStopBits) (struct Uart_Builder*, uint8_t);
    struct Uart_Builder*  (*setDataBits) (struct Uart_Builder*, uint8_t);

    Uart_Config_t (*build)(struct Uart_Builder *);

} Uart_Builder;

Uart_Builder UART_Builder_Init();


#endif /* _UART_BUILDER_H_ */