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

    balloc_add_region(allocator, malloc(1024), 1024, 64);
    balloc_add_region(allocator, malloc(1024), 1024, 16);
    balloc_add_region(allocator, malloc(1024), 1024, 128);

    balloc_set_default_allocator(allocator);

    void *p1 = balloc_allocate(32);
    print_error();
    printf("p1: %p\n", p1);
    void *p2 = balloc_allocate(14);
    print_error();
    printf("p2: %p\n", p2);
    void *p3 = balloc_allocate(129);
    print_error();
    printf("p3: %p\n", p3);

    balloc_free(p1);
    print_error();
    p1 = 0;
    p1 = balloc_allocate(32);
    print_error();
    printf("p1: %p\n", p1);

    balloc_free(p3);
    print_error();
    printf("p3: %p\n", p3);

    return 0;
}
