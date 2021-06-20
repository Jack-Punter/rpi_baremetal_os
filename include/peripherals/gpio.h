#pragma once

#include "common.h"
#include "peripherals/base.h"

typedef struct GPIOPinData {
    reg32 reserved;
    reg32 data[2];
} GPIOPinData;

typedef struct GPIORegs {
    reg32 func_select[6];
    GPIOPinData output_set;
    GPIOPinData output_clear;
    GPIOPinData level;
    GPIOPinData ev_detect_status;
    GPIOPinData re_detect_enable;
    GPIOPinData fe_detect_enable;
    GPIOPinData hi_detect_enable;
    GPIOPinData lo_detect_enable;
    GPIOPinData async_re_detect;
    GPIOPinData async_fe_detect;
    reg32 reserved;
    reg32 pupd_enable;
    reg32 pupd_enable_clocks[2];
} GPIORegs;

#define GPIO ((GPIORegs *)(PBASE + 0x0020000))