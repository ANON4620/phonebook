#include <ncurses.h>
#include <stdlib.h>
#define DATAFILE "file.dat"

struct NewContact
{
	char name[21];
	unsigned long phone;
};

int main()
{
	void list();
	void add();
	void edit();
	void delete();

	int n;

	initscr();

	while(TRUE)
	{
		erase();

		addch('\n');
		addstr("[1] List\n");
		addstr("[2] Add\n");
		addstr("[3] Edit\n");
		addstr("[4] Delete\n");
		addstr("[5] Search\n");
		addstr("[6] Exit\n");
		addch('\n');

		addstr(">> ");
		scanw("%d", &n);
		addch('\n');

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
				edit();
				break;
			case 4:
				list();
				delete();
				break;
			case 5:
				addstr("This feature is under development.");
				break;
			case 6:
				endwin();
				exit(EXIT_SUCCESS);
			default:
				addstr("Invalid input!\n");
		}
		addstr("\n[Press any key to continue]");
		getch();
	}

	return 0;
}

void list()
{
	struct NewContact contact;
	FILE *file;
	int err;

	file = fopen(DATAFILE, "r");

	addstr("RECORD, NAME, PHONE\n\n");
	for(int i = 1; ; i++)
	{
		err = fscanf(file, "%s %lu", contact.name, &(contact.phone));
                if(err == EOF)
			break;
		printw("[%d], %s, %lu\n", i, contact.name, contact.phone);
	}

	fclose(file);
	addch('\n');
}

void add()
{
	struct NewContact contact;
	FILE *file;

	addstr("Name: ");
	getnstr(contact.name, 20);
	addstr("Phone no: ");
	scanw("%lu", &(contact.phone));

	file = fopen(DATAFILE, "a");
	fprintf(file, "%s %lu\n", contact.name, contact.phone);
	fclose(file);
}

void delete()
{
        struct NewContact contact;
	FILE *file, *new;
	int n, err;

        addstr("Record no: ");
        scanw("%d", &n);

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

        addstr("Record no: ");
        scanw("%d", &n);
	addstr("Name: ");
        getnstr(edit.name, 20);
        addstr("Phone no: ");
	scanw("%lu", &(edit.phone));

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
