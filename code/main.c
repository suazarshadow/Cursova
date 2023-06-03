#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "input.h"
#define TABLE_SIZE 10

int main()
{
    YESNO q;
    int choise = 0;
    list_node *hashtable[TABLE_SIZE];
    list_node_load *list = NULL;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        hashtable[i] = create_list(i); 
    }


    printf("================================================");
    printf("Author : Chernaik Sviatoslav KM-24\n");
    printf("Hash Table\n");
    printf("================================================");
    while(1)
    {
        printf("Commands:\n1 - load database\n2 - add student\n3 - delete student\n4 - display all\n5 - save work\n6 - find info about someone\n7 - end work\n");
        printf("================================================\n");

        choise = ask_int("Enter int to chose one option from list\n>", "Error: expected int value!\n"); 
        printf("================================================\n");

        switch(choise)
        {
            case 1:
                list = read_data("data.txt", hashtable);
                if (transfer_data_to_hashtable(list, hashtable))
                {
                    printf("DataBase loaded succsesfully\n");
                    free_list_node_load(list);
                }
                printf("================================================\n");
                break;
            case 2:
                add_student(hashtable);
                printf("Student added sucsesfuly\n");
                printf("================================================\n");
                break;
            case 3:
                if (delete_student_info(hashtable))printf("Student deleted sucsesfuly\n");
                printf("================================================\n");
                break;
            case 4:
                distlay_structure(hashtable);
                printf("================================================\n");
                break;
            case 5:
                printf("WARNING: your old data can be deleted FOREVER\n");
                q = ask_yes_no("Wanna save data[y/n]\n","Error: wrond input\n");
                if(q) write_data(hashtable, "data.txt");
                printf("================================================\n");
                break;
            case 6:
                if(find_info(hashtable)) printf("some info\n"); 
                else printf("There is no such student in database\n");
                break;
            case 7:
                printf("WARNING: your non saved data will be deleted FOREVER\n");
                q = ask_yes_no("Wanna save data[y/n]","Error: wrond input");
                if(q) 
                {
                    write_data(hashtable, "data.txt");
                    for(int i = 0; i< TABLE_SIZE; i++)
                    {
                        free_list_node(hashtable[i]);
                    }
                    return 0;
                }
                else
                {
                    for(int i = 0; i < TABLE_SIZE; i++)
                    {
                        free_list_node(hashtable[i]);
                    }
                    return 0;
                }
            default:
                printf("Unknown command!\n");
        }
        printf("================================================\n");
    }
    return 0;  
}