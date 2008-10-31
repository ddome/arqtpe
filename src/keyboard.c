#include"../include/keyboard.h"
#include"../include/buffer.h"


#define IsLetter(c) ( ( (c)>='a' && (c)<='z' ) || ((c)>='A' && (c)<='Z') )?1:0

extern int numlock,caps,scrolllock,shift;


/*
static unsigned char tecladoLAT[][CANT_KEYS]
{
	{0,'º','1','2','3','4','5','6','7','8','9','0',0,'¡',0,},
 	{0,'ª','!','"','·','$','%','&','/','(',')','=','?','¿',0}
};*/

static unsigned char tecladoUS [][CANT_KEYS] =
{
	{0, ESC, '1', '2', '3', '4', '5', '6',
 '7', '8', '9', '0', '-', '=', '\b',	'\t',
 'q', 'w', 'e', 'r',	't', 'y', 'u', 'i',
 'o', 'p', '[', ']',	'\n', 0, 'a', 's',
 'd', 'f', 'g', 'h',	'j', 'k', 'l', ';',
 '\'', '`', 0,	'\\', 'z', 'x',	'c', 'v',
 'b', 'n', 'm', ',', '.', '/', 0, '*',
 0, ' ', 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 UPKEY, 0, 0, 0, 0, 0, 0, 0,
 DOWNKEY, 0, 0,0
	}, /* Shifteados */

 {0, 0, '!', '@', '#', '$', '%', '^',
 '&', '*', '(', ')',	'_', '+', '\b', '\t',
 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
 'O', 'P', '{', '}', '\n', 0, 'A', 'S',
 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
 '"', '~', 0, '|', 'Z', 'X', 'C', 'V',
 'B', 'N', 'M', '<', '>', '?', 0, 0,
 0, ' ', 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 UPKEY, 0, 0, 0, 0, 0, 0, 0,
 DOWNKEY, 0, 0, 0
 }
};

char
ToUpper(char c)
{
	return ( (c)>='a' && (c)<='z' )?(c - 'a' + 'A'):(c);
}

char
ToLower(char c)
{
	return ( (c)>='A' && (c)<='Z' )?(c - 'A' + 'a'):(c);
}

unsigned char
PutInBuffer(unsigned char code)
{
	unsigned char ascii;

	ascii=tecladoUS[shift][code];

	if( caps && !shift && IsLetter(ascii) )
		ascii=ToUpper(ascii);
	else if( caps && shift && IsLetter(ascii) )
		ascii=ToLower(ascii);

	AddToBuffer(ascii);

	return ascii;
}

void
SetKBLights(void)
{
	char keys= 0;

	if( scrolllock )			/* seteo el char de luces de teclado */
		keys |= 1;
	if( numlock )
		keys |= 2;
	if( caps )
		keys |= 4;

	/*_Lights(keys);*/
	return;
}





