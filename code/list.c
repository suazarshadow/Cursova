#ifndef LIST_C
#define LIST_C
#include "list.h"


GENDER ask_gender(const char *msg, const char *error_msg)
{
    GENDER gender;
    char *string;
    while(1)
    {
        printf("%s([M/W]): ", msg);
        string = ask_string_for_int("", error_msg);

        if (!strcmp(string, "m")||!strcmp(string, "M"))
        {
            return MALE;
        }
        if(!strcmp(string, "w")||!strcmp(string, "W"))
        {
            return FEMALE;
        }

        puts(error_msg);
    }
}



list_node *create_list()
{
    list_node *list = malloc(sizeof(Student));

    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;

    return list;
}

bool add_student_info(list_node *list)
{
    printf("================= Adding info =================\n");

    Student *new = malloc(sizeof(Student));
    //BTW function are modefied;
    ask_string("Enter name of student: ", "Input error: invalid input", new -> name);
    ask_string("Enter surname of student: ", "Input error: invalid input", new -> surname);
    ask_string("Enter lastname of student: ", "Input error: invalid input", new -> lastname);

    new -> date = (Date *)malloc(sizeof(Date)); 

    new -> date -> year = ask_int("Enter year of birth: ", "Input Error: invalid input");
    new -> date -> month = ask_int("Enter month of birth: ", "Input Error: invalid input");
    new -> date -> day = ask_int("Enter day of birth: ", "Input Error: invalid input");

    new -> gender = ask_gender("Enter student`s gender ", "Input error");
    ask_string("Enter group of student: ", "Input error: invalid input", new -> group);

    new -> next = NULL;

    if (list -> size == 0)
    {
        list -> head = new;
        list -> tail = new;
    }
    else
    {
        list -> tail -> next = new;
        list -> tail = new;
    }

    list -> size ++;
    return true;
}

bool delete_student_info(list_node *list)
{
    char s_name[64];
    char s_surname[64];
    char s_group[64];

    printf("================ Deleting info ================\n");  

    if(list->size == 0) printf("List Error: Empty list!");
    

    ask_string("Enter name to find:", "Input Error", s_name);
    ask_string("Enter name to find:", "Input Error", s_surname);
    ask_string("Enter name to find:", "Input Error", s_group);

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

                    Date *delete_date = c -> date; // we need get pointer to dinamicly allocated space to delete memory reservation

                    free(delete_date);
                    free(c);
                    list -> size--; 

                    return true;
                }
            }
        }

    }
    printf("Error : no such student in database!");
    return false;
}   

bool distlay_structure(list_node *list)
{         
    printf("=============== Displaying info ===============\n"); 

    if (list -> size == 0)
    {
        printf("Nothing to display");
        return true;
    }

    Student *c = list -> head;

    for (int i = 1; i <= list -> size; i ++)
    {
        printf("%d.\n", i);
        printf("NAME    : %s\n", c -> name);
        printf("SURNAME : %s\n", c -> surname);
        printf("CROUP   : %s\n", c -> group);
        printf("-----------------------------------------------\n");

        c = c -> next;
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
        Date *delete_date = c -> date;

        c = c -> next;

        free(delete_temp);
        free(delete_date);
        
    }
    free(list);
    return true;
}


bool write_data(list_node *list, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if(file == NULL)
    {
        return false;
    }

    fprintf(file, "%d\n", list -> size);//writing total number for better reading;

    for (Student *c = list -> head; c != NULL; c = c -> next)
    {
        fprintf(file, "%s\n", c -> name);
        fprintf(file, "%s\n", c -> surname);
        fprintf(file, "%s\n", c -> lastname);

        fprintf(file, "%d\n", c -> date -> year);
        fprintf(file, "%d\n", c -> date -> month);
        fprintf(file, "%d\n", c -> date -> day);

        if (c -> gender == MALE) fprintf(file, "%s\n", "MALE");
        else fprintf(file, "%s\n", "FEMALE");
        
        fprintf(file, "%s\n", c -> group);
    }
    fclose(file);
    return true;
}


list_node *read_data(const char *filename)
{
    FILE *file = fopen(filename, "r");
    list_node *list = create_list();
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
        fgets(c->lastname, 64, file);

        char temp_gen[64];

        
         
        c->date = (Date*)malloc(sizeof(Date));
        fscanf(file, "%d\n", &c->date->year);
        fscanf(file, "%d\n", &c->date->month);
        fscanf(file, "%d\n", &c->date->day);

        fscanf(file, "%s\n", temp_gen);
        if (strcmp(temp_gen, "male") == 0) c->gender = MALE;
        else c->gender = FEMALE;

        fgets(c -> group, 64, file);
    }

    list -> tail = c;
    c -> next = NULL;

    fclose(file);

    return list;
}

bool write_data_json(list_node *list)
{
    cJSON *root = cJSON_CreateArray();

    for (Student *c = list -> head; c != NULL; c = c -> next)
    {
        cJSON *json_obj = cJSON_CreateObject();
        
        cJSON_AddItemToArray(root, json_obj);

        cJSON_AddStringToObject(json_obj, "name", c -> name);
        cJSON_AddStringToObject(json_obj, "surname", c -> surname);
        cJSON_AddStringToObject(json_obj, "lastname", c -> lastname);

        cJSON *date_obj = cJSON_CreateObject();

        cJSON_AddItemToObject(json_obj, "date_of_birth", date_obj);
        cJSON_AddNumberToObject(date_obj, "year", c -> date -> year);
        cJSON_AddNumberToObject(date_obj, "month", c -> date -> month);
        cJSON_AddNumberToObject(date_obj, "day", c -> date -> day);
        

        if (c -> gender == MALE) cJSON_AddStringToObject(json_obj, "gender", "MALE");
        else cJSON_AddStringToObject(json_obj, "gender", "FEMALE");
        
        cJSON_AddStringToObject(json_obj, "group", c -> group);
    }

    FILE *file = fopen("data.json", "w");

    if (file == NULL)
    {
        printf("Error : Somthing went wrong, cannot open the file");

        cJSON_Delete(root);
        fclose(file);
        
        return false;

    }

    char *json_str  = cJSON_Print(root);
    fputs(json_str, file);
    fclose(file);
    cJSON_Delete(root);
    cJSON_free(json_str);

    return true;
}

list_node *read_from_json()
{
    char temp_gen[64];
    int y; 
    int m;
    int d;  
    list_node *list = create_list();
    Student *p = NULL;
    Student *c = NULL;

    

    FILE *file = fopen("data.json", "r");
    
    if (ftell(file) == 0)
    {
        printf("File has no content");
        return NULL;
    }

    if (file == NULL)
    {
        return NULL;
    }
    
    fseek(file, 0 , SEEK_END);

    long fsize = ftell(file);

    fseek(file, 0, SEEK_SET);

    char *json_data = malloc(fsize + 1);

    fread(json_data, 1, fsize, file);

    if (json_data == NULL)
    {
        printf("Error!");
        return NULL;
    }

    cJSON *root = cJSON_Parse(json_data);
    cJSON *student = NULL;
    cJSON_free(json_data);

    cJSON_ArrayForEach(student, root)
    {  
        cJSON *name = cJSON_GetObjectItemCaseSensitive(student, "name");
        cJSON *surname = cJSON_GetObjectItemCaseSensitive(student, "surname");
        cJSON *lastname = cJSON_GetObjectItemCaseSensitive(student, "lastname");
        cJSON *date_obj = cJSON_GetObjectItemCaseSensitive(student, "date_of_birth");
        cJSON *gender = cJSON_GetObjectItemCaseSensitive(student, "gender");
        cJSON *group = cJSON_GetObjectItemCaseSensitive(student, "group");

        const cJSON *year = cJSON_GetObjectItemCaseSensitive(date_obj, "year");
        const cJSON *month = cJSON_GetObjectItemCaseSensitive(date_obj, "month");
        const cJSON *day = cJSON_GetObjectItemCaseSensitive(date_obj, "day");

        c = (Student *)malloc(sizeof(Student));
        c -> date = (Date*)malloc(sizeof(Date));

        if (list -> size == 0) list -> head = c;
        else p -> next = c;
        
        p = c;
        strncpy(c -> name, name -> valuestring, sizeof(c -> name));
        strncpy(c -> surname, surname -> valuestring, sizeof(c -> surname));
        strncpy(c -> lastname, lastname -> valuestring, sizeof(c -> lastname));

        c -> date -> year = year->valueint;
        c -> date -> month = month->valueint;
        c -> date -> day = day->valueint;

        strncpy(temp_gen, gender -> valuestring, sizeof(temp_gen));

        if (strcmp(temp_gen, "male") == 0) c->gender = MALE;
        else c->gender = FEMALE;
        strncpy(c -> group, group -> valuestring, sizeof(c -> group));

        list -> size ++;
    }

    list -> tail = c;
    c -> next = NULL;

    cJSON_Delete(root);

    return list;
}
#endif