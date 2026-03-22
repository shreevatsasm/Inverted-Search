#include "inverted_index.h"

int main(int argc, char *argv[])
{
    char valid_files[MAX_FILES][50];
    int file_count = 0;
    int choice;
    int db_created = 0;


    main_node *hashtable[HASH_SIZE] = {NULL};

    /* Validate number of arguments */
    if (argc <= 1)
    {
        printf("ERROR: Number of arguments must be greater than 1\n");
        printf("Usage: ./a.out file1.txt file2.txt ...\n");
        return FAILURE;
    }

    /* Validate files */
    if (validate_files(argv, argc, valid_files, &file_count) == FAILURE)
    {
        printf("ERROR: File validation failed\n");
        return FAILURE;
    }

    while (1)
    {
        printf("\n----- INVERTED INDEX MENU -----\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (db_created)
                {
                    printf("Database already created\n");
                    break;
                }

                for (int i = 0; i < file_count; i++)
                {
                    create_database(hashtable, valid_files[i]);
                }

                db_created = 1;
                printf("Database created successfully\n");
                break;

            case 2:
                display_database(hashtable);
                break;

            case 3:
                search_database(hashtable);
                break;

            case 4:
                save_database(hashtable);
                break;

            case 5:
                update_database(hashtable);
                break;

            case 6:
                printf("Exiting...\n");
                return SUCCESS;

            default:
                printf("Invalid choice\n");
        }
    }

    return SUCCESS;
}