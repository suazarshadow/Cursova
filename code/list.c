#ifndef LIST_C
#define LIST_C
#define TABLE_SIZE 10
#include "list.h"

bool add_student(list_node *hashtable[])
{
    char name[64];
    char surname[64];
    char group[64];

    ask_string("Enter name to add:", "Input Error", name);
    ask_string("Enter surname to add:", "Input Error", surname);
    ask_string("Enter group to add:", "Input Error", group);
    
    Student *s = malloc(sizeof(Student));

    strcpy(s -> name, name);
    strcpy(s -> surname, surname);
    strcpy(s -> group, group);

    add_student_info(hashtable[get_key(name, surname, group)], s);

}
void transfer_data_to_hashtable(list_node_load *list, list_node *hashtable[])
{
    int key = 0;

    for (Student *c = list -> head; c != NULL; c = c -> next)
        {
            key = get_key(c -> name, c -> surname, c -> group);

            add_student_info(hashtable[key], c);
            
        }
}
unsigned int get_key(char *name, char *surname, char *group)
{
    unsigned int key;

    int name_length = strnlen(name, 64);
    int surname_length = strnlen(surname, 64);
    int group_length = strnlen(group, 64);

    for (int i = 0; i < name_length; i++)
    {
        tolower(name[i]);
        key += name[i];
    }
    for (int j = 0; j < surname_length; j++)
    {
        tolower(surname[j]);
        key += surname[j];
    }
    for (int k = 0; k < group_length; k++)
    {
        tolower(group[k]);
        key += group[k];
    }
    key = key%TABLE_SIZE;
    return key;
}

list_node *create_list(int key)
{
    list_node *list = malloc(sizeof(Student));

    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;
    list -> key = key;
    
    return list;
}

bool add_student_info(list_node *list, Student *student)
{

    student -> next = NULL;

    if (list -> size == 0)
    {
        list -> head = student;
        list -> tail = student;
    }
    else
    {
        list -> tail -> next = student;
        list -> tail = student;
    }

    list -> size ++;
    return true;
}
bool delete_student_info(list_node *hashtable[])
{
    char s_name[64];
    char s_surname[64];
    char s_group[64];
    int key = 0;

    printf("================ Deleting info ================\n");  

  
    ask_string("Enter name to find:", "Input Error", s_name);
    ask_string("Enter surname to find:", "Input Error", s_surname);
    ask_string("Enter group to find:", "Input Error", s_group);
    //c - current structure
    key = get_key(s_name, s_surname, s_group);
    if(hashtable[key]->size == 0) 
    {
        printf("List Error: Empty list!");
        return false;

    }
    Student *c = hashtable[key] -> head;  
    //p - previos structure: if we find correct student info that we want to delete we will swith pointer(pointer to next node) in previos node -
    // -to  pointer(pointer to next node) from node with info to delete so we won`t damage structure;
    Student *p = hashtable[key] -> head;   // In current moment *p == *c  when *c pointer will do two moves we will make one move on *p pointer
    for(size_t i = 0; i < hashtable[key] -> size; i++)
    {
        // First we will separete by group, then by surname , then by name;
        // That will help our program to run  a litle bit faster; 
        if (!strcmp(s_group, c -> group))
        {
            if(!strcmp(s_surname, c -> surname))
            {
                if(!strcmp(s_name, c -> name))
                {
                    if (c == p) hashtable[key] -> head = c -> next; // in case head is info that we want to delete
                    p -> next = c -> next; // pointer switching;
                    free(c);
                    hashtable[key] -> size--; 
                    return true;
                }
            }
        }

        c = c -> next;

    }
    printf("Error : no such student in database!");
    return false;
}   
list_node_load *create_list_for_load()
{
    list_node_load *list = malloc(sizeof(Student));

    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;

    return list;
}

bool distlay_structure(list_node *hashtable[])
{         
    printf("=============== Displaying info ===============\n"); 
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Hash Key: %d\n", i);
        if (hashtable[i] -> size == 0)
        { 
            printf("EMPTY\n"); 
        }
        else
        { 
            Student *c = hashtable[i] -> head;

            for (int j = 1; j <= hashtable[i] -> size; j ++)
            {
                printf("===========\n");
                printf("NAME    : %s\n", c -> name);
                printf("SURNAME : %s\n", c -> surname);
                printf("CROUP   : %s\n", c -> group);

                c = c -> next;
            }
        }
    }
    return true;
}


bool free_list_node_load(list_node_load *list)
{
    Student *c = list -> head;


    while (c != NULL)
    {
        //using temporary pointers to delete because *c will be equal NULL that will stop the cycle; 
        Student *delete_temp = c;
        c = c -> next;

        free(delete_temp);
        
    }
    free(list);
    return true;
}

bool free_list_node(list_node *list)
{
    Student *c = list -> head;


    while (c != NULL)
    {
        //using temporary pointers to delete because *c will be equal NULL that will stop the cycle; 
        Student *delete_temp = c;
        c = c -> next;

        free(delete_temp);
        
    }
    free(list);
    return true;
}


bool write_data(list_node *hashtable[] , const char *filename)
{
    FILE *file = fopen(filename, "w");

    if(file == NULL)
    {
        return false;
    }

    int size = 0;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        size += hashtable[i] -> size;
    }

    fprintf(file, "%d\n", size);

    for(int i = 0; i < TABLE_SIZE; i++)
    {

        for (Student *c = hashtable[i] -> head; c != NULL; c = c -> next)
        {
            fprintf(file, "%s\n", c -> name);
            fprintf(file, "%s\n", c -> surname); 
            fprintf(file, "%s\n", c -> group);
        }
    }

    fclose(file);

    return true;
}


list_node_load *read_data(const char *filename)
{
    FILE *file = fopen(filename, "r");
    list_node_load *list = create_list_for_load();
    Student *p = NULL;
    Student *c = NULL;
    if (file == NULL)
    {
        return NULL;
    }

    fscanf(file, "%d\n", &list ->size);

    if (list -> size == 0)
    {
        return NULL;
    }

    

    for (int i =0; i < list -> size; i++)
    {
        c = (Student *)malloc(sizeof(Student));

        if (i == 0 ) list -> head = c;
        else p -> next = c;   

        p = c;
        
        fgets(c->name, 64, file);
        fgets(c->surname, 64, file);
        fgets(c -> group, 64, file);
        c->name[strlen(c->name)-1] = '\0';
        c->surname[strlen(c->surname)-1] = '\0';
        c->group[strlen(c->group)-1] = '\0';
    }

    list -> tail = c;
    c -> next = NULL;
    fclose(file);

    return list;
}
#endif