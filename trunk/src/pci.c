#include "../include/pci.h"
#include "../include/pcilist.h"

#define  PCIBIOS_SUCCESSFUL                0x00


extern PCI_VENTABLE	PciVenTable [];
extern PCI_DEVTABLE	PciDevTable [];

int pcibios_read (unsigned long dato, unsigned int *value)
{
	_Cli();
    myoutl(0xCF8, dato);
    _Sti();
    _Cli();
    myinl(0xCFC, value);
    _Sti();
    return PCIBIOS_SUCCESSFUL;
}

unsigned short lspci (void)
{
	unsigned int devfn, l, bus, buses, func;
	unsigned int first_bus, first_devfn, first_i;
	unsigned char hdr_type = 0;
	unsigned short vendor, device;
	unsigned long dato;
	int j, flag = 0;
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
			for (devfn = first_devfn; devfn < 32; ++devfn) {
				for (func = 0; func < 8; func++)
				{
					dato = armaDato (bus, devfn, func, 0);
					pcibios_read(dato, &l);
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
					
					j = 0;
					flag = 0;
					while (PciVenTable[j].VenId != 0 && flag == 0)
					{
						if (PciVenTable[j].VenId == vendor)
						{
							printf(PciVenTable[j].VenFull);
							printf("--");
							
							flag = 1;
							
						}
						j++;
					}
					
					//printf(PciVenTable[0].VenFull);
					
					i = 5;
					tmp = device;
					while (tmp > 0 && i >= 0)
					{
					   aux2[i] = (tmp % 10) + '0';
					   tmp /= 10;
					   i--;
					}
					printf(aux2);
					printf("--");
				
				
				
					j = 0;
					flag = 0;
					while (PciDevTable[j].VenId != 0 && flag == 0)
					{
						if (PciDevTable[j].VenId == vendor && PciDevTable[j].DevId == device)
						{
							printf(PciDevTable[j].ChipDesc);
							printf("\n");
							flag = 1;
						}
						j++;
					}
					while (i++ < 6)
						aux[i] = '0';
					aux[6] = 0;
						
					i = 0;
							  
					while (i++ < 6)
						aux2[i] = '0';
					aux2[6] = 0;
				}
					
				
					

			}
		}
	printf("\n");
}

unsigned long armaDato (unsigned int bus, unsigned int devfn, unsigned int func, unsigned int reg)
{
	unsigned long dato = 0;
	dato = ((unsigned long) 0x80000000 | (bus << 16) | (devfn << 11) | (func << 8) | reg);
	return dato;
	
	
}
