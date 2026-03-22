#include "inverted_index.h"

void update_database(main_node *hashtable[])
{
    char filename[50];

    printf("Enter the file name to update database: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("ERROR: Unable to open file\n");
        return;
    }

    char ch;

    /* check file starts with '#' */
    fscanf(fp, " %c", &ch);

    if (ch != '#')
    {
        printf("ERROR: Invalid file format\n");
        fclose(fp);
        return;
    }

    rewind(fp);

    int index, file_count;
    char word[50];

    while (fscanf(fp, "# %d %s %d", &index, word, &file_count) != EOF)
    {
        /* create main node */
        main_node *new_main = malloc(sizeof(main_node));

        strcpy(new_main->word, word);
        new_main->file_count = file_count;
        new_main->main_link = NULL;
        new_main->sub_link = NULL;

        sub_node *prev_sub = NULL;

        /* read sub nodes */
        for (int i = 0; i < file_count; i++)
        {
            char fname[50];
            int w_count;

            fscanf(fp, "%s %d", fname, &w_count);

            sub_node *new_sub = malloc(sizeof(sub_node));

            strcpy(new_sub->file_name, fname);
            new_sub->word_count = w_count;
            new_sub->sub_link = NULL;

            if (prev_sub == NULL)
            {
                new_main->sub_link = new_sub;
            }
            else
            {
                prev_sub->sub_link = new_sub;
            }

            prev_sub = new_sub;
        }

        /* insert into hashtable */
        if (hashtable[index] == NULL)
        {
            hashtable[index] = new_main;
        }
        else
        {
            main_node *temp = hashtable[index];

            while (temp->main_link != NULL)
            {
                temp = temp->main_link;
            }

            temp->main_link = new_main;
        }
    }

    fclose(fp);

    printf("Database updated successfully from file\n");
}