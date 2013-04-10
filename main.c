#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 16
#define MAX_STUDENTS_NUMBER 25

typedef struct employees {
    char names[3][NAME_SIZE];
    int salary[12];
} employ_t;

int input(employ_t *);
int sort_up(employ_t *, int);
int get_posint(void);
void fgets_c(char *, int, FILE *);
int compare(const void *, const void *);
int output_table(employ_t *, int);
char *month_name(int);
int display_help(int argc, char**);

int main(int argc, char **argv)
{
    employ_t *company;
    int workers_n;
    if(display_help(argc,argv))
        return 0;
    company = (employ_t *) calloc(MAX_STUDENTS_NUMBER, sizeof(employ_t));
    workers_n = (input(company));
    company = (employ_t *) realloc(company, workers_n * sizeof(employ_t));
    sort_up(company, workers_n);
    output_table(company, workers_n);
    free(company);
    return (0);                 /* I like it */
}

int input(employ_t * company)
{
    int i = 0, j = 0;
    for (i = 0; i < MAX_STUDENTS_NUMBER; i++) {
        printf("Provide First Name. To end input press enter:\n");
        fgets_c(company[i].names[0], NAME_SIZE, stdin);
        if (*company[i].names[0] == '\n')
            break;
        printf("Last Name:\n");
        fgets_c(company[i].names[1], NAME_SIZE, stdin);
        printf("Patronymic:\n");
        fgets_c(company[i].names[2], NAME_SIZE, stdin);
        for (j = 0; j < 12; j++) {
            printf("Provide salary for %s\n", month_name(j));
            while (get_posint(&company[i].salary[j]) == -1)
                printf("Please print positive numbers.\n");
        }
    }
    return i;
}

void fgets_c(char *target, int length, FILE * source)
{
    int i = 0;
    char buf[1000];
    fgets(buf, 1000, source);
    strncpy(target,buf,length-1);
    target[length]='\0';
    if (strlen(buf)>length)
        printf("String you entered was too long, data is partially lost.\n");
    while (target[i] != '\n' && target[i])
        i++;
    if (target[i] == '\n' && i)
        target[i] = '\0';
    return;
}

int get_posint(int* target)
{
    char buff[1000];
    int output = 0;
    char* check;
    printf ("Maximum 9 digit number\n");
    fgets_c(buff, 1000, stdin);
    *target=strtol(buff,&check,10);
    if (*check!='\0' || strlen(buff)>9 || *target<0)
        output=-1;
    return output;
}

char *month_name(int i)
{
    char *month[] =
        { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
        "Oct", "Nov", "Dec"
    };
    return month[i];
}

int sort_up(employ_t * company, int workers_n)
{
    qsort(company, workers_n, sizeof(employ_t), compare);
    return 1;
}

int compare(const void *a, const void *b)
{
    return strcmp(((employ_t *) a)->names[1], ((employ_t *) b)->names[1]);
}

int output_table(employ_t * company, int workers_n)
{
    int i, j;
    char name[35];
    printf("Name%16c", ' ');
    for (i = 0; i < 12; i++)
        printf("%9s", month_name(i));
    printf("\n");
    for (i = 0; i < workers_n; i++) {
        sprintf(name, "%s %c. %c.", company[i].names[1],
                *(company[i].names[0]), *(company[i].names[2]));
        printf("%-20s", name);
        for (j = 0; j < 12; j++)
            printf("%9d", company[i].salary[j]);
    }
    return 1;
}

int display_help(int argc,char** argv)
{
    if (argc>1 && strcmp(argv[1],"-h")==0)
    {
        printf ("This program gets information about workers and their salary and prints it in alphabetic order.\n"
                "Name size(last name, patronymic) is limited to 15 characters.\n");
        return 1;
    }
    return 0;
}
