#include "stdio.h"
#include "stdlib.h"

typedef struct company {
    char names[3][30];
    int salary[12];
    int sort_priority[3];
    char *adv_sorting[3];
} com_t;

typedef struct sorting {
    int sort_priority[3];
    int sort_order;
} sor_t;

int input(com_t *);
int sort_up(com_t *, int);
int matrix_reloaded(com_t *, char **, int);

int main(int argc, char **argv)
{
    com_t *company;
    int workers_n, i;
    char **table;
    company = (com_t *) calloc(25, sizeof(com_t));
    workers_n = (input(company));
    table = (char **) calloc(workers_n + 1, sizeof(char *));
    for (i = 0; i < workers_n + 1; i++)
        *(table + i) = (char *) malloc(sizeof(int) * 12 + 45);
    sort_up(company, workers_n);
    matrix_reloaded(company, table, workers_n);
    for (i = 0; i < workers_n + 1; i++)
        printf("%s\n", table[i]);
    return (0);                 /* I like it */
}

int input(com_t * company)
{
    char *month[12] =
        { "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December" };
    int i = 0, j = 0;
    for (i = 0; i < 25; i++) {
        printf("Provide First Name. To end input press enter.\n");
        fgets(company[i].names[0], 30, stdin);
        if (*company[i].names[0] == '\n')
            break;
        while (*(company[i].names[0] + j) != '\n')
            j++;
        *(company[i].names[0] + j) = '\0';
        printf("Last Name\n");
        fgets(company[i].names[1], 30, stdin);
        while (*(company[i].names[0] + j) != '\n')
            j++;
        *(company[i].names[0] + j) = '\0';
        printf("Patronymic\n");
        fgets(company[i].names[2], 30, stdin);
        while (*(company[i].names[0] + j) != '\n')
            j++;
        *(company[i].names[0] + j) = '\0';
        for (j = 0; j < 12; j++) {
            printf("Provide salary for %s\n", month[j]);
            scanf("%d", &company[i].salary[j]);
        }
        for (j = 0; j < 3; j++) {
            company[i].adv_sorting[j] = &company[i].names[j][1];
            if (*(company[i].names[j]) > 'a' - 1)
                company[i].sort_priority[j] =
                    *(company[i].names[j]) - 'a' + 'A';
            else
                company[i].sort_priority[j] = *(company[i].names[j]);
        }
    }
    return i;
}

int sort_up(com_t * company, const int workers_n)
{
    int i = 0, j = 0, k = 0, min, s_type;
    sor_t *sort;
    sor_t tmp;
    com_t *temp;
    sort = (sor_t *) calloc(workers_n, sizeof(sor_t));
    temp = (com_t *) calloc(workers_n, sizeof(com_t));
    printf
        ("You want to sort by:\n1)First Name\n2)Last Name\n3)Patronymic\n");
    scanf("%d", &s_type);
    s_type--;
    for (i = 0; i < workers_n; i++)
        for (j = 0; j < 3; j++) {
            sort[i].sort_priority[j] = company[i].sort_priority[j];
            sort[i].sort_order = i;
        }
    for (i = 0; i < workers_n; i++) {
        min = i;
        for (j = i + 1; j < workers_n; j++)
            if (sort[j].sort_priority[s_type] <=
                sort[min].sort_priority[s_type])
                if (sort[j].sort_priority[s_type] ==
                    sort[min].sort_priority[s_type]) {
                    while (*
                           (company[sort[j].sort_order].
                            adv_sorting[s_type] + k) ==
                           *(company[sort[min].sort_order].
                             adv_sorting[s_type] + k))
                        k++;
                    if (*
                        (company[sort[j].sort_order].adv_sorting[s_type] +
                         k) <
                        *(company[sort[min].sort_order].
                          adv_sorting[s_type] + k))
                        min = j;
                } else
                    min = j;
        tmp = sort[min];
        sort[min] = sort[i];
        sort[i] = tmp;
    }
    for (i = 0; i < workers_n; i++)
        temp[i] = company[sort[i].sort_order];
    for (i = 0; i < workers_n; i++)
        company[i] = temp[i];
    free(sort);
    free(temp);
    return 1;
}

int matrix_reloaded(com_t * company, char **table, int workers_n)
{
    int i = 0;
    char name[30] = { "Name" };
    sprintf(*table,
            "%-20s  Jan   Feb   Mar   Apr   May   Jun   Jul   Aug   Sep   Oct   Nov   Dec",
            name);
    for (i = 0; i < workers_n; i++) {
        sprintf(name, "%s %c. %c.", company[i].names[1],
                *(company[i].names[0]), *(company[i].names[2]));
        sprintf(*(table + i + 1),
                "%-20s%5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d\n",
                name, company[i].salary[0], company[i].salary[1],
                company[i].salary[2], company[i].salary[3],
                company[i].salary[4], company[i].salary[5],
                company[i].salary[6], company[i].salary[7],
                company[i].salary[8], company[i].salary[9],
                company[i].salary[10], company[i].salary[11]);
    }
    return 1;
}
