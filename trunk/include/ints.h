#ifndef INTS_H_
#define INTS_H_
#include "defs.h"

void int_80w(FileDesc fd, const void * buff, int size);
int int_80r(FileDesc fd, char * buff, int size);

#endif /*INTS_H_*/
