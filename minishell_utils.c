
#include "executor.h"

void    *safe_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        print_error(errno, NULL, PRINT);
        return (NULL);
    }
    return (ptr);
}

// add duplicate double_pointers
