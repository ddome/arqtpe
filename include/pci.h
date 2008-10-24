#ifndef PCI_H_
#define PCI_H_

#include "defs.h"

unsigned short pciConfigReadWord (unsigned short bus, unsigned short slot,
                                  unsigned short func, unsigned short offset);

unsigned short pciCheckVendor(unsigned short bus, unsigned short slot);

#endif /*PCI_H_*/
