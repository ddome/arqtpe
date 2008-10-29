#ifndef PCI_H_
#define PCI_H_

#include "defs.h"
#define PCI_HEADER_TYPE         0x0e    /* 8 bits */
#define PCI_VENDOR_ID           0x00    /* 16 bits */

struct pci_device {
	unsigned short	vendor, dev_id;
	const char	*name;
	/* ioaddr is silly and deprecated */
	unsigned int	ioaddr;
	unsigned int	addr1;
	unsigned char	devfn;
	unsigned char	bus;
	struct pci_id *	probe_id;
	unsigned int	romaddr;
};

#define PCI_FUNC(devfn)           ((devfn) & 0x07)



unsigned short pciConfigReadWord (unsigned short bus, unsigned short slot,
                                  unsigned short func, unsigned short offset);

unsigned short pciCheckVendor(unsigned short bus, unsigned short slot);

unsigned short lspci (unsigned short bus, unsigned short slot,
                                 unsigned short func, unsigned short offset);
unsigned short lspcib(struct pci_id *id, int ids, struct pci_device *dev);

int pcibios_read_config_byte(unsigned int bus, unsigned int device_fn,
			       unsigned int where, unsigned char *value);

int pcibios_read_config_word (unsigned int bus,
    unsigned int device_fn, unsigned int where, unsigned short *value);

int pcibios_read_config_dword (unsigned int bus, unsigned int device_fn,
				 unsigned int where, unsigned int *value);

#endif /*PCI_H_*/
