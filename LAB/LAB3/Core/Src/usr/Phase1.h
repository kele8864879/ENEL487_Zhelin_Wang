#ifndef Phase1_h
#define Phase1_h

#include <stdbool.h>
#include "main.h"
uint8_t cliRXChar;
uint8_t cliBufferTX[20];
uint8_t cliBufferRX[20];
bool isCompleteLine;



bool returnLineOrPartialLine(uint8_t cliRXChar, uint8_t cliBufferRX[]);
#endif Phase1_h
