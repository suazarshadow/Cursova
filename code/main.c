#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#define TABLE_SIZE 10

int main()
{
    
   /* YESNO yesno = YES;

 
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
    
       */
    HashTable *hashtable = init_hash_table();
    int key = 0;
    while (key < TABLE_SIZE)
    {
        create_list(hashtable, key);
        key++;
    }
    list_node *curr = hashtable -> head;
    key = 0;
    while (key < TABLE_SIZE)
    {
        
        if(curr -> size  == 0)
        {
            printf("--------\n");
        }
        else
        {
            printf("Error");
        }
        key++;
        curr = curr -> next;
    }
    printf("----------\n");
    printf("Sviatoslav Cherniak KM-24 => %d\n", get_key("Sviatoslav", "Cherniak", "KM-24"));
    printf("Max Fedosenko KM-24 => %u\n", get_key("Max", "Fedosenko", "KM-24"));
    printf("max fedosenko km-24 => %u\n", get_key("max", "fedosenko", "km-24"));

    Student *s = malloc(sizeof(Student));

    strcpy(s->name, "Sviatoslav");
    strcpy(s->surname, "Cherniak");
    strcpy(s->group, "KM-24");
    add_to_hash_table(s, get_key("Sviatoslav", "Cherniak", "KM-24"), hashtable);
    distlay_structure(hashtable);

    if(write_data(hashtable, "data.txt")) printf("Wrote Sucuesful\n");

    if(free_hash_table(hashtable)) printf("Memory clear suscesful\n");

    list_node_load  *list = read_data("data.txt");


    if(free_hash_table(hashtable)) printf("Memory clear suscesful\n");

    return 0;  
}