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

bool try_convert_to_long(const char *string, long *result)
{
    bool negative = false;

    for (int i = 0; i < strlen(string); i++)
    {
        if (i == 0 && string[i] == '-')
        {
            negative = true; 
            continue;
        }
        if (!isdigit(string[i]))
        {   
            printf("f");
            return 0;
        }
    }

    long long pre_result = atoll(string);

    if (pre_result > LONG_MAX)
    {
        return 0;
    } 

    if (negative)
    {
        pre_result = -pre_result;
    }
    *result = (long)pre_result;

    return 1;
}
bool try_convert_to_double(const char *string, double *result)
{
    bool negative = false;
    int dot_counter = 0; 

    for (int i = 0; i < strlen(string); i++)
    {
        if (i == 0 && string[i] == '-')
        {
            negative = true; 
            continue;
        }

        if (string[i] == '.')
        {
            dot_counter++;
            continue;
        } 

        if (!isdigit(string[i]))
        {
            return 0;
        }
    }

    if (dot_counter > 1)
    {
        return 0;
    }

    long long pre_result = strtod(string, 0);

    if (pre_result > DBL_MAX)
    {
        return 0;
    } 

    if (negative)
    {
        pre_result = -pre_result;
    }

    *result = (double)pre_result;
    return 1;
}

#endif