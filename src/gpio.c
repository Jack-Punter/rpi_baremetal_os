#include "common.h"

#include "gpio.h"

#include "utils.h"


void gpio_pin_set_function(u8 pin, GPIOFunc func)
{
    u8 bit_start = (pin * 3) % 30;
    u8 reg = pin / 10;

    u32 selector = GPIO->func_select[reg];
    selector &= ~(7 << bit_start);
    selector |= func << bit_start;
    GPIO->func_select[reg] = selector;
}


/*
 * See the "GPIO Pull-up/down Clock Registers (GPPUDCLKn)" Section 
 * of the BCM2835 Reference Manual. For enable sequence.
 */
void gpio_pin_enable(u8 pin)
{
    GPIO->pupd_enable = 0;
    delay(150);
    GPIO->pupd_enable_clocks[pin / 32] = 1 << (pin % 32);
    delay(150);
    GPIO->pupd_enable = 0;
    GPIO->pupd_enable_clocks[pin / 32] = 0;
}
