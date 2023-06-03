#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "input.h"


typedef struct Student
{
    char name[64];
    char surname[64];
    char group[64];
    struct Student *next;
}Student;

typedef struct list_node_load
{
    Student *head;
    Student *tail;
    int size;
}list_node_load;


typedef struct list_node
{
    Student *head;
    Student *tail;
    int size;
    int key;
}list_node;

unsigned int get_key(char *name, char *surname, char *group);

bool transfer_data_to_hashtable(list_node_load *list, list_node *hashtable[]);

bool find_info(list_node *hashtable[]);

list_node *create_list(int key);

list_node_load *create_list_for_load();

bool add_student_info(list_node *list, Student *student);

bool delete_student_info(list_node *hashtable[]);

bool distlay_structure(list_node *hashtable[]);

bool free_list_node(list_node *list);

bool write_data(list_node *hashtable[], const char *filename);

bool add_student(list_node *hashtable[]);

list_node_load *read_data(const char *filename, list_node *hashtable[]);

bool free_list_node_load(list_node_load *list);

#endif