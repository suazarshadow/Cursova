#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "input.h"
#include "cJSON.h"

typedef enum GENDER
{
    MALE,
    FEMALE,
}GENDER;

typedef struct Date
{
    int year;
    int month;
    int day;
}Date;



typedef struct Student
{
    char name[64];
    char surname[64];
    char lastname[64];
    Date *date;
    GENDER gender;
    char group[64];
    struct Student *next;
}Student;



typedef struct list_node
{
    Student *head;
    Student *tail;
    int size;
}list_node;

GENDER ask_gender(const char *msg, const char *error_msg); 

list_node *create_list();


bool add_student_info(list_node *student);

bool delete_student_info(list_node *list);

bool distlay_structure(list_node *list);

bool free_list_node(list_node *list);

bool write_data(list_node *list, const char *filename);

bool write_data_json(list_node *list);

list_node *read_data(const char *filename);

list_node *read_from_json();


#endif