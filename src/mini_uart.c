#include "gpio.h"
#include "utils.h"
#include "peripherals/aux.h"
#include "mini_uart.h"

#define TXD 14
#define RXD 15

void uart_init() {
    gpio_pin_set_function(TXD, GPIOFunc_Alt5);
    gpio_pin_set_function(RXD, GPIOFunc_Alt5);

    gpio_pin_enable(TXD);
    gpio_pin_enable(RXD);

    AUX->enables = 1;
    AUX->mu_control = 0;
    AUX->mu_ier = 0;
    AUX->mu_lcr = 3;
    AUX->mu_mcr = 0;

    // See 2.2.1 of BCM2835 Reference Manual for
    // baud rate register value calculation
    // baud = sysclk / (8 * (baud_reg + 1))
#if RPI_VERSION == 3
    //AUX->mu_baud_reg = 270; //115200 baud @ 250MHz
    AUX->mu_baud_reg = 433; //115200 baud @ 400MHz
#elif RPI_VERSION == 4
    AUX->mu_baud_reg = 541; // 115200 baud @ 500MHz
#endif

    AUX->mu_control = 3;
    uart_send_str("\r\n\n");
}

void uart_send(char c)
{
    // See Section 2.2.2 AUX_MU_LSR_REG Register table
    // wait until the uart transmission fifo can accept
    // a byte
    while(BIT_CLR(AUX->mu_lsr, 0x20));

    AUX->mu_io = c;
}

char uart_recv() 
{
    // Wait untill the data ready byte is set
    while(BIT_CLR(AUX->mu_lsr, 1));

    return AUX->mu_io & 0xFF;
}

void uart_send_str(char *str)
{
    while (*str) {
        if (*str == '\n') {
            uart_send('\r');
        }
        uart_send(*str++);
    }
}
