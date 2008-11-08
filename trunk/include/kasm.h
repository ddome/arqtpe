/*********************************************
kasm.h

************************************************/

#include "defs.h"


unsigned int    _read_msw();

void            _lidt (IDTR *idtr);

void		_mascaraPIC1 (byte mascara);  /* Escribe mascara de PIC1 */
void		_mascaraPIC2 (byte mascara);  /* Escribe mascara de PIC2 */

void		_Cli(void);        /* Deshabilita interrupciones  */
void		_Sti(void);	 /* Habilita interrupciones  */

void		_int_08_hand();      /* Timer tick */
void		_int_80_hand();      /* write */
void		write();
void		read(int fd, char *buff, int size);

void		mywrite();
void		myread();

void		_debug (void);

void        _int_09_hand_US(void);
void        _int_09_hand_LAT(void);
void 		_MoveCursor(int pos); /* charxchar y */

void		_DelCursor(void);
void		_RestoreCursor(void);
