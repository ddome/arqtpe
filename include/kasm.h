/*********************************************
kasm.h

Funciones de bajo nivel

************************************************/

#ifndef KASM_H
#define KASM_H

#include "defs.h"


unsigned int    _read_msw();

void            _lidt (IDTR *idtr);

void		_mascaraPIC1 (byte mascara);  /* Escribe mascara de PIC1 */
void		_mascaraPIC2 (byte mascara);  /* Escribe mascara de PIC2 */

void		_Cli(void);        /* Deshabilita interrupciones  */
void		_Sti(void);	 	   /* Habilita interrupciones  */

/* Timer Tick */
void		_int_08_hand();

/* Drivers del teclado */
void        _int_09_hand_US(void);
void        _int_09_hand_LAT(void);

/* Primitivas Write() and Read() */
void		_int_80_hand();

/* Entrada y salida */
void		write();
void		read(int fd, char *buff, int size);
void		mywrite();
void		myread();

void 		myout(int port, byte dato);

/* Funciones de control del cursor */
void 		_MoveCursor(int pos);


void		_Fault();

#endif
