#include "stdint.h"
#include "error.h"


uint32_t failed(module m){
    return (m << 16) | FAIL;
}

uint32_t pass(module m){
    return (m << 16) | PASS;
}