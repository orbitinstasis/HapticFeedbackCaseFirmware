#ifndef HELPER_H
#define HELPER_H

#include <avr/io.h>

void helperDigitalWrite(volatile uint8_t *, uint8_t, uint8_t );
void helperSetDir(volatile uint8_t *, uint8_t, uint8_t );

#endif