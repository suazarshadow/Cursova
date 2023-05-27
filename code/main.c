#include <stdio.h>
#include <stdbool.h>
#include "list.h"

int main()
{
    
    YESNO yesno = YES;

 
    list_node *list = read_data("data.txt");
    printf("Database is load\n");

    if (list  == NULL) 
    {
        printf("Database is empty\n");
        list = create_list();
    }
  
    else distlay_structure(list);
    printf("aviable comands: \n");
    printf("Add info about student(a)\n");
    printf("Delete info about student(d)\n");
    printf("Show all info(s)");
    printf("(help) show all comands; (end) - end the program\n");

    while (1)
    {
       
        

        char *input = ask_string_for_int("[a/d/s/l]\n", "Error: invalid input");

        if (!strcmp(input, "end"))
        {
            printf("If you didn`t write data base to file it won`t save:");
            yesno = ask_yes_no("Wanna write [y/n]\n", "Error: invalid input");
            if (yesno == YES)
            {
                if (!strcmp(input, "w")||!strcmp(input, "W"))
                {
                    printf("Chose type of database\n");
                    input = ask_string_for_int("json/txt/bin\n", "Error: invalid input");
                    if (!strcmp(input, "json"))
                    {
                        write_data_json(list);
                    }
                    if (!strcmp(input, "txt"))
                    {
                        write_data(list ,"data.txt");
                    }
                    if (!strcmp(input, "bin"))
                    {
                        write_data(list ,"data.bin");
                    }
                    else printf("Unknow command\n!");
                }

            }

            write_data(list, "data.txt")
            free_list_node(list);

            return 0;
        }
        if (!strcmp(input, "help"))
        {
            printf("Add info about student(a)\n");
            printf("Delete info about student(d)\n");
            printf("Show all info(s)\n");
            printf("(end) - end the program\n");
            printf("w - write to chosed type of file\n");
        }

        if (!strcmp(input, "a")||!strcmp(input, "A"))
        {
            
            while (yesno != NO)
            {
                add_student_info(list);
                yesno = ask_yes_no("Wanna continue [y/n]?\n","Error: input error");

            }
        }

        if (!strcmp(input, "d")||!strcmp(input, "D"))
        {
            while (yesno != NO)
            {
                add_student_info(list);
                yesno = ask_yes_no("Wanna continue [y/n]?\n","Error: input error");

            }
        }
        if (!strcmp(input, "s")||!strcmp(input, "S"))
        {
            distlay_structure(list);
        }
            else printf("Unknow command\n!");

        if (!strcmp(input, "w")||!strcmp(input, "W"))
        {
            printf("Chose type of database\n");
            input = ask_string_for_int("json/txt/bin\n", "Error: invalid input");
            if (!strcmp(input, "json"))
            {
                write_data_json(list);
            }
            if (!strcmp(input, "txt"))
            {
                write_data(list ,"data.txt");
            }
            if (!strcmp(input, "bin"))
            {
                write_data(list ,"data.bin");
            }
            else printf("Unknow command\n!");
        }

        else printf("Unknow command\n!");
    }
    
       
    return 0;   
}