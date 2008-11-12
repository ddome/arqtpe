#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/ints.h"
#include "../include/kc.h"
#include "../include/pci.h"
#include "../include/video.h"
#include "../include/shell.h"

DESCR_INT idt[0x81];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

/**********************************************
kmain()
Punto de entrada de cóo C.
*************************************************/

kmain()
{

        int i,num;
        int flag = 0;
        int vendor = 0xffff;


/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0 y IRQ1   */

       // setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
        setup_IDT_entry (&idt[0x80], 0x08, (dword)&_int_80_hand, ACS_INT, 0);

        /* Por default el teclado esta en ingles */
        setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand_US,ACS_INT, 0);

        /* Carga de IDTR    */

        idtr.base = 0;
        idtr.base +=(dword) &idt;
        idtr.limit = sizeof(idt)-1;

        _lidt (&idtr);

        _Cli();

        /* Habilito interrupcion del teclado */

        _mascaraPIC1(0xFD);
        _mascaraPIC2(0xFF);

        _Sti();

        /* Se inicia el shell */
        shell();


}

void
loadkeysla(void)
{
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand_LAT,ACS_INT, 0);
}

void
loadkeysus(void)
{
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand_US,ACS_INT, 0);
}

void
reboot(void)
{
	int i;
	/* Blanqueo el idt */
	for (i=0; i<10; i++)
	        setup_IDT_entry (&idt[i], 0x08, 0, ACS_INT, 0);

	_Fault();
}
