#ifndef HEAP_H
#define HEAP_H

// #include "/home/eigen/dev/c++/projects/hOS/files/src/config.h"
#include "config.h"
#include <stdint.h>
#include <stddef.h>

#define HEAP_BLOCK_TABLE_ENTRY_TAKEN    0x01
#define HEAP_BLOCK_TABLE_ENTRY_FREE     0x00
#define HEAP_BLOCK_HAS_NEXT             0b10000000
#define HEAP_BLOCK_IS_FIRST             0b10000000

typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;

struct heap_table
{
    HEAP_BLOCK_TABLE_ENTRY* entries;
    size_t total;
};
struct heap
{
    struct heap_table* table;
    void* saddr;
};

int heap_create(struct heap *heap, void *ptr, void *end, struct heap_table *table);
void *heap_maloc(struct heap*, size_t);
void heap_free(struct heap*, void *);

#endif