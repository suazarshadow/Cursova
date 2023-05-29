#ifndef INPUT_C
#define INPUT_C
#include "input.h"
void *ask_string(const char *msg, const char *error_msg, char *string)
{
    char buffer[1024];
    size_t len = 0;
    printf("%s", msg);
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[--len] = '\0';
        }

        if (string != NULL)
        { 
            strcpy(string, buffer);  
        }
    }
}

YESNO ask_yes_no(const char *msg, const char *error_msg)
{
    char *string ;

    while (1)
    {
        char *string=ask_string_for_int(msg , "Error: something went wrong!");

        for(size_t i = 0; i < strlen(string); i++)
        {
            string[i] = tolower(string[i]);
        }
        
        if (!strcmp(string, "y"))
        {
            free(string);
            return YES;
        }
        if (!strcmp(string,"n"))
        {
            free(string);
            return NO;
        }
        free(string);
        puts(error_msg);
    }
}

#endif