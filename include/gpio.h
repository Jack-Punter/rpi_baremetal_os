#pragma once

#include "peripherals/gpio.h"

typedef enum GPIOFunc {
    GPIOFunc_Input = 0,
    GPIOFunc_Output = 1,
    GPIOFunc_Alt0 = 4,
    GPIOFunc_Alt1 = 5,
    GPIOFunc_Alt2 = 6,
    GPIOFunc_Alt3 = 7,
    GPIOFunc_Alt4 = 3,
    GPIOFunc_Alt5 = 2
} GPIOFunc;

void gpio_pin_set_function(u8 pin, GPIOFunc func);
void gpio_pin_enable(u8 pin);
