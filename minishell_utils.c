
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

// safe malloc allocates any type of variable by being of return type void pointer
// if allocation fails it calls print error immedieatly, saving 3 lines of code in the calling function
// then it returns NULL
// else it returns the pointer

void    *safe_ft_calloc(size_t count, size_t size)
{
    void    *ptr;

    ptr = ft_calloc(count, size);
    if (!ptr)
    {
        print_error(errno, NULL, PRINT);
        return (NULL);
    }
    return (ptr);
}

char    *safe_ft_substr(const char *s, unsigned int start, size_t len)
{
    char *substr = ft_substr(s, start, len);
    if (!substr)
    {
        print_error(errno, NULL, PRINT);
        return (NULL);
    }
    return (substr);
}

char    *safe_ft_strdup(const char *s)
{
    char *str;

    str = ft_strdup(s);
    if (!str)
    {
        print_error(errno, NULL, PRINT);
        return (NULL);
    }
    return (str);
}

char    *safe_ft_strtrim(char *s, const char *set)
{
    char *res;

    res = ft_strtrim(s, set);
    if (!res)
    {
        print_error(errno, NULL, PRINT);
        return (NULL);
    }
    return (res);
}



// add duplicate double_pointers
