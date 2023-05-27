#ifndef INPUT_C
#define INPUT_C
#include "input.h"
char *ask_string_for_int(const char *msg, const char *error_msg)
{
    printf("%s", msg);

    char *string = NULL;
    char buffer[1024];
    size_t len = 0;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[--len] = '\0';
        }
         
        string = (char *)malloc(len);

        if (string != NULL)
        { 
            strcpy(string, buffer);  
        }
        
    }
    else puts(error_msg);

    return string;
}
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


int ask_int(const char *msg, const char *error_msg)
{
    int result;

    while (1)
    {
        char *string = ask_string_for_int(msg , "Error: wrong input\n");

        if (try_convert_to_int(string, &result))
        {
            free(string);
            return result;
        }

        free(string);
        puts(error_msg);
        printf("\n");
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