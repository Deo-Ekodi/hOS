#include "kheap.h"
#include "heap.h"
#include "/home/eigen/dev/c++/projects/hOS/files/src/config.h"
#include "/home/eigen/dev/c++/projects/hOS/files/src/kernel.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;

void kheap_init()
{
    int total_table_entries = HOS_HEAP_SIZE_BYTES / HOS_HEAP_BLOCK_SIZE; // 25600 bytes
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY*)(HOS_HEAP_TABLE_ADDRESS);
    kernel_heap_table.total = total_table_entries;

    void* end = (void*)(HOS_HEAP_ADDRESS + HOS_HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void*)(HOS_HEAP_ADDRESS), end, &kernel_heap_table);

    if(res < 0)
    {
        print("Failed to create heap\n");
    }
}