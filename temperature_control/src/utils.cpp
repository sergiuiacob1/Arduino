#include "./../header/utils.h"

int freeMemory()
{
    int size = 100000; // Use 2048 with ATmega328
    byte *buf;

    while ((buf = (byte *)malloc(--size)) == NULL)
        ;
    free(buf);
    return size;
}
