#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"

uint16_t *video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char color)
{
    return (color << 8) | c;
}

void terminal_putchar(int x, int y, char c, char color)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, color);
    terminal_col += 1;

    if(terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void terminal_writechar(char c, char color)
{
    terminal_putchar(terminal_col, terminal_row, c, color);
    terminal_col += 1;

    if(c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void terminal_initialize()
{
    video_mem = (uint16_t *)(0xB8000);
    terminal_col = 0;
    terminal_row = 0;

    for(int y = 0; y < VGA_HEIGHT; y++)
    {
        for(int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while(str[len])
    {
        len++;
    }
    return len;
}

void print(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 5);
    }
    
}

// extern void problem(); // for testing interrupt

void kernel_main()
{
    terminal_initialize();

    const char* name = "Deogratius\nEKodi";
    print(name);

    kheap_init(); // initialize heap

    idt_init();
    // problem(); // for testing interrupt

    void* ptr = kmalloc(50);
    void* ptr2 = kmalloc(5000);
    void* ptr3 = kmalloc(5600);

    kfree(ptr);
    void* ptr4 = kmalloc(50);

    if(ptr || ptr2 || ptr3 || ptr4)
    {
        ;
    }

}