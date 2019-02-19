#ifndef G711_H
#define G711_H
#include "WinRDefs.h"
unsigned char linear2alaw(short);
short         alaw2linear(unsigned char);
unsigned char linear2ulaw(short);
short         ulaw2linear(unsigned char);
int           alaw2ulaw(int);
int           ulaw2alaw(int);
#endif
//------------------------------------------------------------------------------