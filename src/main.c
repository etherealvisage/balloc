#include <stdio.h>
#include <stdlib.h>

#include "balloc.h"

void print_error() {
    int error = balloc_get_last_error();
    switch(error) {
    case BALLOC_NO_ERROR:
        printf("No error!\n");
        break;
    case BALLOC_INVALID_SIZE:
        printf("Invalid size!\n");
        break;
    case BALLOC_NO_FREE_MEMORY:
        printf("No free memory!\n");
        break;
    case BALLOC_POINTER_NOT_IN_REGION:
        printf("Pointer not in region!\n");
        break;
    default:
        printf("Unknown error.\n");
        break;
    }
}

int main() {
    size_t size = balloc_calculate_size(4);
    balloc_allocator_t *allocator = malloc(size);
    balloc_setup_allocator(allocator, size);
    balloc_set_default_allocator(allocator);

    balloc_add_region(allocator, malloc(1<<30), 1<<30, 32);
    balloc_add_region(allocator, malloc(1<<30), 1<<30, 64);
    balloc_add_region(allocator, malloc(1<<30), 1<<30, 128);
    balloc_add_region(allocator, malloc(1<<30), 1<<30, 16);

    void **ptrs = malloc(sizeof(void *) * (1<<24));
    int i;
    for(i = 0; i < 1<<24; i ++) {
        ptrs[i] = (void *)1;
    }
    for(i = 0; i < 1<<24; i ++) {
        ptrs[i] = balloc_allocate(16);
        /*ptrs[i] = malloc(16);*/
    }

    for(i = 0; i < 1<<24; i ++) {
        balloc_free(ptrs[i]);
        /*free(ptrs[i]);*/
    }

    return 0;
}

