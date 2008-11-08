#ifndef INTS_H_
#define INTS_H_
#include "defs.h"
int int_09_LAT(unsigned char code);
int int_09_US(unsigned char code);
void int_80w(FileDesc fd, const void * buff, int size);
void int_80r(FileDesc fd, char * buff, int size);

#endif /*INTS_H_*/
