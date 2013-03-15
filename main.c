#include "stdio.h"
#include "stdlib.h"
#ifndef _WIN32 || ifndef _WIN64
	#include "std_ext.h"
    #define  fflush __fpurge
#endif

typedef struct employees
{
	char names[3][30];
	int salary[12];
} employ_t;

int input(employ_t*);
int sort_up(employ_t*,int);
int get_num(int*);
int output_table(employ_t*);
char* month_name(int);

int main(int argc,char **argv)
{
	employ_t *company;
	int workers_n,i,j;
	char name[35];
	company=(employ_t*)calloc(25,sizeof(employ_t));
	workers_n=(input (company));
	company=(employ_t*)realloc(company,workers_n*sizeof(employ_t));
	sort_up(company,workers_n);
	output_table(company);
	free(company);
	return (0);                    /* I like it */
}

int input(employ_t* company)
{
	int i=0,j=0,k=0;
	for (i=0;i<25;i++)
	{
		printf ("Provide First Name. To end input press enter.\n");
		fflush(stdin);
		fgets (company[i].names[0],29,stdin);
		if (*company[i].names[0]=='\n')
			break;
		printf ("Last Name\n");
		fflush(stdin);
		fgets (company[i].names[1],29,stdin);
		printf ("Patronymic\n");
		fflush(stdin);
		fgets (company[i].names[2],29,stdin);
		for (j=0;j<12;j++)
		{
			printf ("Provide salary for %s\n",month_name(j));
			fflush(stdin);
			while (!get_num(&company[i].salary[j]))
				printf ("Please print numbers. NUMBERS.\n");
		}
		for (j=0;j<3;j++)
		{
			while (*(company[i].names[j]+k)!='\n')
			k++;
			*(company[i].names[j]+k)='\0';
			k=0;
		}
	}
	return i;
}

int get_num(int* target)
{
	char tmp='a';
	char buff[10];
	int i=0,output=0;
	fgets (buff,8,stdin);
	if ((tmp=buff[i])=='\n')
		return 0;
	do
	{
		if (tmp>'9')
			return 0;
		output=output*10+(tmp-'0');
		i++;
		tmp=buff[i];
	} while (tmp && tmp!='\n');
	*target=output;
	return 1;
}

char* month_name(int i)
{
	char* month[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	return month[i];
}

int sort_up(employ_t* company,int workers_n)
{
	int i=0,j=0,k=0,min;
	employ_t temp;
	for (i=0;i<workers_n;i++)
	{
		min=i;
		for (j=i+1;j<workers_n;j++)
			if (*(company[j].names[1])<*(company[min].names[1]))
				min=j;
			else if (*(company[j].names[1])==*(company[i].names[1]))
			{
				while (*(company[j].names[1]+k)==*(company[i].names[1]+k))
					k++;
				if (*(company[j].names[1]+k)<*(company[i].names[1]+k))
					min=j;
			}
		temp=company[min];
		company[min]=company[i];
		company[i]=temp;
	}
	return 1;
}

int output_table(employ_t* comapany)
{
	printf ("Name%16c",' ');
	for (i=0;i<12;i++)
		printf ("%9s",month_name(i));
	printf ("\n");
	for (i=0;i<workers_n;i++)
	{
		sprintf (name,"%s %c. %c.",company[i].names[1],*(company[i].names[0]),*(company[i].names[2]));
		printf ("%-20s",name);
		for (j=0;j<12;j++)
			printf ("%9d",company[i].salary[j]);
	}
	return 1;
}