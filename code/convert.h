#ifndef CONVER_H
#define CONVER_H

#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool try_convert_to_int(const char *string, int *result);
bool try_convert_to_long(const char *str, long *res);
bool try_convert_to_double(const char *str, double *res);

#endif