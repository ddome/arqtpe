
#define MAX_CANT 40
#define BUFFER_ARRAY_SIZE (MAX_CANT+1)
#define EOF -1
#define BUFFER_FULL -2

int AddToBuffer(unsigned char c);

unsigned char GetFromBuffer(void);

int BufferIsFull(void);

int BufferIsEmpty(void);
