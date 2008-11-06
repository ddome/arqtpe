#ifndef PCI_H_
#define PCI_H_

#include "defs.h"


unsigned short lspci (void);

unsigned long armaDato (unsigned int bus, unsigned int devfn, unsigned int func, unsigned int reg);
int pcibios_read (unsigned long dato, unsigned int *value);

#endif /*PCI_H_*/
