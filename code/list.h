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
    struct list_node *next;
}list_node;

typedef struct HashTable
{
    struct list_node *head;
    struct list_node *tail;
}HashTable;

unsigned int get_key(char *name, char *surname, char *group);

void create_list(HashTable *hashtable, int key);

bool add_to_hash_table(Student *student, int key, HashTable *hashtable);

bool delete_from_hash_table(Student *student, int key, HashTable *hashtable);

list_node_load *create_list_for_load();

HashTable *init_hash_table();

bool add_student_info(list_node *list, Student *student);

bool delete_student_info(list_node *list, char *s_name, char *s_surname, char *s_group);

bool distlay_structure(HashTable *hashtable);

bool free_list_node(list_node *list);

bool write_data(HashTable *hashtable, const char *filename);

list_node_load *read_data(const char *filename);

bool free_hash_table(HashTable *hashtable);

#endif