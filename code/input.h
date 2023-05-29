#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef enum YESNO
{
    NO,
    YES
} YESNO;

char *ask_string_for_int(const char *msg, const char *error_msg);

YESNO ask_yes_no(const char *msg, const char *error_msg);

#endif
