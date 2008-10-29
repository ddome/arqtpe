#include "../include/pci.h"

#define  PCIBIOS_SUCCESSFUL                0x00

/*
 * Functions for accessing PCI configuration space with type 1 accesses
 */

#define CONFIG_CMD(bus, device_fn, where)   (0x80000000 | (bus << 16) | (device_fn << 8) | (where & ~3))



unsigned short pciConfigReadWord (unsigned short bus, unsigned short slot,
                                  unsigned short func, unsigned short offset)
{
   unsigned long address;
   unsigned long lbus = (unsigned long)bus;
   unsigned long lslot = (unsigned long)slot;
   unsigned long lfunc = (unsigned long)func;
   unsigned short tmp = 0;
 
   /* create configuration address as per Figure 1 */
   address = (unsigned long)((lbus << 16) | (lslot << 11) |
             (lfunc << 8) | (offset & 0xfc) | ((UINT32)0x80000000));
 
   /* write out the address */
   myout (0xCF8, address);
   /* read in the data */
   tmp = (unsigned short)((myin (0xCFC) >> ((offset & 2) * 8)) & 0xffff);
   return (tmp);
}


unsigned short pciCheckVendor(unsigned short bus, unsigned short slot)
{
   unsigned short vendor,device;
   /* try and read the first configuration register. Since there are no */
   /* vendors that == 0xFFFF, it must be a non-existent device. */
   if ((vendor = pciConfigReadWord(bus,slot,0,0)) != 0xFFFF) {
      device = pciConfigReadWord(bus,slot,0,2);
      //. . .
   } return (vendor);
}

unsigned short lspci (unsigned short bus, unsigned short slot,
                                  unsigned short func, unsigned short offset)
{
   unsigned long address;
   unsigned long lbus = (unsigned long)bus;
   unsigned long lslot = (unsigned long)slot;
   unsigned long lfunc = (unsigned long)func;
   unsigned short tmp = 0;
   char aux[7] = {'0'};
   
   int i = 0;
   
   while (i++ < 6)
	   aux[i] = '0';
   aux[6] = 0;
   address = 0;
   /* write out the address */
   
   /* read in the data */
   //tmp = (unsigned short)((myin (0xCFC) >> ((offset & 2) * 8)) & 0xffff);
   int j = 0;
   while(j++ <= 256)
   {
	   myoutl (0xCF8, j);
   
	   myinl (0xCFC,&tmp);
	   //tmp = (unsigned short)((myinl (0xCFC) >> ((0 & 2) * 8)) & 0xffff);
	   
	   if (tmp == 0xffff)
	   {
		   printf("0xffff\n");
	   }
	   else
	   {
		   i = 5;
		   while (tmp > 0 && i >= 0)
		   {
			   aux[i] = (tmp % 10) + '0';
			   tmp /= 10;
			   i--;
		   }
		   printf(aux);
		   printf("\n");
	   }
	   
   }
   return (tmp);
}

/*Funciones basadas en codigo de http://www.koders.com/c/fidE6BECF1628861AC7945D0C553470A28758EDA501.aspx?s=md5 */
int pcibios_read_config_byte(unsigned int bus, unsigned int device_fn,
			       unsigned int where, unsigned char *value)
{
	_Cli();
    myoutl(0xCF8, CONFIG_CMD(bus,device_fn,where));
    _Sti();
    _Cli();
    myin(0xCFC + (where&3), value);
    _Sti();
    return PCIBIOS_SUCCESSFUL;
}

int pcibios_read_config_word (unsigned int bus,
    unsigned int device_fn, unsigned int where, unsigned short *value)
{
	_Cli();
    myoutl(0xCF8,CONFIG_CMD(bus,device_fn,where));
    _Sti();
    _Cli();
    myinw(0xCFC + (where&2), value);
    _Sti();
    return PCIBIOS_SUCCESSFUL;
}

int pcibios_read_config_dword (unsigned int bus, unsigned int device_fn,
				 unsigned int where, unsigned int *value)
{
	_Cli();
    myoutl(0xCF8, CONFIG_CMD(bus,device_fn,where));
    _Sti();
    _Cli();
    myinl(0xCFC, value);
    _Sti();
    return PCIBIOS_SUCCESSFUL;
}


unsigned short lspcib(struct pci_id *id, int ids, struct pci_device *dev)
{
	unsigned int devfn, l, bus, buses;
	unsigned int first_bus, first_devfn, first_i;
	unsigned char hdr_type = 0;
	unsigned short vendor, device;
		
	unsigned short tmp = 0;
	
	char aux[7] = {'0'};
	char aux2[7] = {'0'};
	   
	int i = 0;
	  
	while (i++ < 6)
		aux[i] = '0';
	aux[6] = 0;
	
	i = 0;
		  
		while (i++ < 6)
			aux2[i] = '0';
		aux2[6] = 0;

	first_bus = 0;
		first_devfn = 0;
		first_i = 0;



	buses=256;
		for (bus = first_bus; bus < buses; bus++) {
			for (devfn = first_devfn; devfn < 0xff; ++devfn) {
				if (PCI_FUNC (devfn) == 0)
					pcibios_read_config_byte(bus, devfn, PCI_HEADER_TYPE, &hdr_type);
				else if (!(hdr_type & 0x80))	/* not a multi-function device */
					continue;
				
				pcibios_read_config_dword(bus, devfn, PCI_VENDOR_ID, &l);
				/* some broken boards return 0 if a slot is empty: */
				if (l == 0xffffffff || l == 0x00000000) {
					hdr_type = 0;
					//printf("SI\n");
					continue;
				}
				vendor = l & 0xffff;
				
				device = (l >> 16) & 0xffff;
				
				i = 5;
				tmp = vendor;
				   while (tmp > 0 && i >= 0)
					{
					   aux[i] = (tmp % 10) + '0';
					   tmp /= 10;
					   i--;
					}
					printf(aux);
					printf("--");
					
					i = 5;
					tmp = device;
					while (tmp > 0 && i >= 0)
					{
					   aux2[i] = (tmp % 10) + '0';
					   tmp /= 10;
					   i--;
					}
					printf(aux2);
					printf("\n");
					

			}
		}
	
}

