#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DATAFILE "file.dat"

struct NewContact
{
	char name[20];
	unsigned long phone;
};

int main()
{
	void list();
	void add();
	void edit();
	void delete();

	int n;

	while(true)
	{
		putchar('\n');
		puts("[1] List");
		puts("[2] Add");
		puts("[3] Edit");
		puts("[4] Delete");
		puts("[5] Exit");
		putchar('\n');

		printf(">> ");
		scanf("%d", &n);
		putchar('\n');

		switch(n)
		{
			case 1:
				list();
				break;
			case 2:
				add();
				break;
			case 3:
				list();
				putchar('\n');
				edit();
				break;
			case 4:
				list();
				putchar('\n');
				delete();
				break;
			case 5:
				exit(EXIT_SUCCESS);
			default:
				puts("Invalid input!");
		}

		putchar('\n');
		printf("[Press Enter to continue]");
		getchar();
		getchar();
	}

	return 0;
}

void list()
{
	struct NewContact contact;
	FILE *file;
	int err;

	file = fopen(DATAFILE, "r");

	for(int i = 1; ; i++)
	{
		err = fscanf(file, "%s %lu", contact.name, &(contact.phone));
                if(err == EOF)
			break;
		printf("[%d]\t%s\t%lu\n", i, contact.name, contact.phone);
	}

	fclose(file);
}

void add()
{
	struct NewContact contact;
	FILE *file;

	printf("Name: ");
	scanf("%s", contact.name);
	printf("Phone no: ");
	scanf("%lu", &(contact.phone));

	file = fopen(DATAFILE, "a");
	fprintf(file, "%s %lu\n", contact.name, contact.phone);
	fclose(file);
}

void delete()
{
        struct NewContact contact;
	FILE *file, *new;
	int n, err;

        printf("Record no: ");
        scanf("%d", &n);

	file = fopen(DATAFILE, "r");
	new = fopen("new.dat", "a");
	
	for(int i = 1; ; i++)
	{
		err = fscanf(file, "%s %lu", contact.name, &(contact.phone));
		if(err == EOF)
			break;
		if(i == n)
			continue;
		fprintf(new, "%s %lu\n", contact.name, contact.phone);
	}

	fclose(file);
	fclose(new);
	
	remove(DATAFILE);
	rename("new.dat", DATAFILE);
}

void edit()
{
	struct NewContact edit, contact;
	FILE *file, *new;
        int n, err;

        printf("Record no: ");
        scanf("%d", &n);
	printf("Name: ");
        scanf("%s", edit.name);
        printf("Phone no: ");
	scanf("%lu", &(edit.phone));

	file = fopen(DATAFILE, "r");
        new = fopen("new.dat", "a");

        for(int i = 1; ; i++)
        {
		err = fscanf(file, "%s %lu", contact.name, &(contact.phone));
                if(err == EOF)
                        break;
                if(i == n)
		{
			fprintf(new, "%s %lu\n", edit.name, edit.phone);
			continue;
		}
                fprintf(new, "%s %lu\n", contact.name, contact.phone);
	}
	
	fclose(file);
	fclose(new);

	remove(DATAFILE);
        rename("new.dat", DATAFILE);
}
