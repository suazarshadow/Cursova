#ifndef CONVERT_C
#define CONVERT_C
#include "convert.h" 


bool try_convert_to_int(const char *string, int *result)
{
    bool negative = false;
    size_t i = 0;

    if (string[0] == '-')
    {
        negative = true;
        i++;
    }

    for (; i < strlen(string); i++)
    {
        if (!isdigit(string[i]))
        {
            *result = 0;
            return 0;
        }

    long long pre_result = atoll(string);

    if (pre_result > INT_MAX || pre_result < INT_MIN)
    {   
        *result = 0;
        return false;
    } 

   
    *result = (int)pre_result;

    return true;
    }
}

#endif