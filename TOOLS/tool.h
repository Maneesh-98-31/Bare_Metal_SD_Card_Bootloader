#ifndef _TOOL_H
#define _TOOL_H

#include "stdint.h"

#define ONE         1
#define SET         ONE

#define ZERO        0
#define CLEAR       ZERO

#define INVALID_VALUE               (0xffffaaaa)


#define SET_BIT(value,bit)          (value |= (SET << bit))
#define CLEAR_BIT(value,bit)        (value &= ~(SET << bit))
#define VALUE_AT(value,bit)         ((value & (SET << bit)) >> bit)




void delay(uint32_t);

#endif