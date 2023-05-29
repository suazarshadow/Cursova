#ifndef LIST_C
#define LIST_C
#define TABLE_SIZE 10
#include "list.h"

HashTable *init_hash_table()
{
    HashTable *hashtable = malloc(sizeof(list_node));
    

    hashtable -> head = NULL;
    hashtable -> tail = NULL;
    return hashtable;
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
bool add_to_hash_table(Student *student,  int key, HashTable *hashtable)
{
    list_node *curr = hashtable -> head;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        printf("%d %d\n", curr -> key);
        if(key == curr -> key)
        {
            
            break;
        } 
        curr = curr -> next;
    }
    if (add_student_info(curr, student))
    {
        return true;
    }
    else return false;
}

bool delete_from_hash_table(Student *student, int key, HashTable *hashtable)
{
    list_node *curr = hashtable -> head;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(i == curr -> key)
        {
            break;
        } 
        curr = curr -> next;
    }
    if (delete_student_info(curr, student -> name, student -> surname, student -> group))
    {
        return true;
    }
    else return false;
}

void create_list(HashTable *hashtable, int key)
{
    list_node *list = malloc(sizeof(Student));

    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;
    list -> key = key;
    
    
    if (list -> key == 0)
    {
        hashtable -> head = list;
        hashtable -> tail = list;
    }
    else
    {
        hashtable -> tail -> next = list;
        hashtable -> tail = list;
    }
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
bool delete_student_info(list_node *list, char *s_name, char *s_surname, char *s_group)
{
    if(list->size == 0) 
    {
        printf("List Error: Empty list!");
        return false;
    }
    //c - current structure
    Student *c = list -> head;  
    //p - previos structure: if we find correct student info that we want to delete we will swith pointer(pointer to next node) in previos node -
    // -to  pointer(pointer to next node) from node with info to delete so we won`t damage structure;
    Student *p = list -> head;   // In current moment *p == *c  when *c pointer will do two moves we will make one move on *p pointer;

    for(size_t i = 0; i < list -> size; i++)
    {
        // First we will separete by group, then by surname , then by name;
        // That will help our program to run  a litle bit faster; 
        if (!strcmp(s_group, c -> group))
        {
            if(!strcmp(s_surname, c -> surname))
            {
                if(!strcmp(s_name, c -> name))
                {
                    if (c == p) list -> head = c -> next; // in case head is info that we want to delete
                    p -> next = c -> next; // pointer switching;
                    free(c);
                    list -> size--; 
                    free(s_group);
                    free(s_name);
                    free(s_surname);
                    return true;
                }
            }
        }

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

bool distlay_structure(HashTable *hashtable)
{         
    printf("=============== Displaying info ===============\n"); 
    list_node *curr = hashtable -> head;
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Hash Key: %d\n", i);
        if (curr -> size == 0)
        { 
            printf("EMPTY\n"); 
        }
        else
        { 
            Student *c = curr -> head;

            for (int i = 1; i <= curr -> size; i ++)
            {
                printf("%d.\n", i);
                printf("NAME    : %s\n", c -> name);
                printf("SURNAME : %s\n", c -> surname);
                printf("CROUP   : %s\n", c -> group);

                c = c -> next;
            }
        }
        curr = curr -> next;
    }
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

bool free_hash_table(HashTable *hashtable)
{
    list_node *c = hashtable -> head;


    while (c != NULL)
    {
        //using temporary pointers to delete because *c will be equal NULL that will stop the cycle; 
        list_node *delete_temp = c;

        c = c -> next;

        free_list_node(delete_temp);
        
    }
    free(hashtable);
    return true;
}

bool write_data(HashTable *hashtable, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if(file == NULL)
    {
        return false;
    }

    list_node *curr = hashtable -> head;
    int size = 0;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        size += curr -> size;
    }

    curr  = hashtable -> head;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        fprintf(file, "%d\n", size);//writing total number for better reading;

        for (Student *c = curr -> head; c != NULL; c = c -> next)
        {
            fprintf(file, "%s\n", c -> name);
            fprintf(file, "%s\n", c -> surname); 
            fprintf(file, "%s\n", c -> group);
        }
        curr = curr -> next;
    
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
    if (ftell(file) == 0)
    {
        printf("File has no content");
        return list;
    }
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
    }

    list -> tail = c;
    c -> next = NULL;

    fclose(file);

    return list;
}
#endif