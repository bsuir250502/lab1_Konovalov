#include "stdio.h"
#include "stdlib.h"
#ifndef _WIN32
#include "stdio_ext.h"
#define  fflush __fpurge
#endif
#define NAME_SIZE 16

typedef struct employees {
    char names[3][NAME_SIZE + 1];
    int salary[12];
} employ_t;

int input(employ_t *);
int sort_up(employ_t *, int);
int get_num(void);
void _fgets(char *, int, FILE *);
int compare(const void *, const void *);
int output_table(employ_t *, int);
char *month_name(int);

int main(int argc, char **argv)
{
    employ_t *company;
    int workers_n;
    company = (employ_t *) calloc(25, sizeof(employ_t));
    workers_n = (input(company));
    company = (employ_t *) realloc(company, workers_n * sizeof(employ_t));
    sort_up(company, workers_n);
    output_table(company, workers_n);
    free(company);
    return (0);                 /* I like it */
}

int input(employ_t * company)
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i < 25; i++) {
        printf("Provide First Name. To end input press enter.\n");
        _fgets(company[i].names[0], NAME_SIZE, stdin);
        if (*company[i].names[0] == '\n')
            break;
        printf("Last Name\n");
        _fgets(company[i].names[1], NAME_SIZE, stdin);
        printf("Patronymic\n");
        _fgets(company[i].names[2], NAME_SIZE, stdin);
        for (j = 0; j < 12; j++) {
            printf("Provide salary for %s\n", month_name(j));
            fflush(stdin);
            while ((company[i].salary[j] = get_num()) == -1)
                printf("Please print numbers. NUMBERS.\n");
        }
    }
    return i;
}

void _fgets(char *target, int length, FILE * source)
{
    int i = 0;
    fflush(stdin);
    fgets(target, length, source);
    while (*(target + i) != '\n' && *(target + i))
        i++;
    if (*(target + i) == '\n' && i)
        *(target + i) = '\0';
    return;
}

int get_num(void)
{
    char tmp = 'a';
    char buff[10];
    int i = 0, output = 0;
    fgets(buff, 8, stdin);
    if ((tmp = buff[i]) == '\n')
        return -1;
    do {
        if (tmp > '9' || tmp < '0')
            return -1;
        output = output * 10 + (tmp - '0');
        i++;
        tmp = buff[i];
    } while (tmp && tmp != '\n');
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
    qsort(company, workers_n, sizeof(employ_t), &compare);
    return 1;
}

int compare(const void *a, const void *b)
{
    int i = 0;
    employ_t *first = (employ_t *) a, *second = (employ_t *) b;
    while (!(*(first->names[1] + i) - *(second->names[1] + i)))
        i++;
    return *(first->names[1] + i) - *(second->names[1] + i);
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
