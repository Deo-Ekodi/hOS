#include "io/io.h"
#include "disk.h"

int disk_read_sector(int lba, int total, void* buf)
{
    outb(0x1f6, (lba >> 24) | 0xE0);
    outb(0x1f2, total);
    outb(0x1f3, (unsigned char)(lba & 0xff));
    outb(0x1f4, (unsigned char)(lba >> 8));
    outb(0x1f5, (unsigned char)(lba >> 16));
    outb(0x1f7, 0x20);

    unsigned short* ptr = (unsigned short*) buf;
    for(int b = 0; b < total; b++)
    {
        char c = insb(0x1f7);
        while(!(c & 0x08))
        {
            c = insb(0x1f7);
        }

        // copy from hard disk to memory

        for(int i = 0; i < 256; i++)
        {
            *ptr = insw(0x1f0);
            ptr++;
        }
    }

    return 0;
}