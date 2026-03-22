#include "inverted_index.h"

int create_database(main_node *hashtable[], char *filename)
{
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        printf("ERROR: Unable to open file %s\n", filename);
        return FAILURE;
    }

    char word[50];

    while (fscanf(fptr, "%s", word) != EOF)
    {
        int index;

        /* find index */
        if (isalpha(word[0]))
            index = tolower(word[0]) - 'a';
        else
            index = 26;

        /* CASE 1 : Hashtable empty */
        if (hashtable[index] == NULL)
        {
            main_node *new_main = malloc(sizeof(main_node));

            strcpy(new_main->word, word);
            new_main->file_count = 1;
            new_main->main_link = NULL;

            sub_node *new_sub = malloc(sizeof(sub_node));

            strcpy(new_sub->file_name, filename);
            new_sub->word_count = 1;
            new_sub->sub_link = NULL;

            new_main->sub_link = new_sub;

            hashtable[index] = new_main;
        }
        else
        {
            main_node *temp = hashtable[index];
            main_node *prev = NULL;

            /* traverse main nodes */
            while (temp != NULL)
            {
                if (strcmp(temp->word, word) == 0)
                {
                    /* word already exists */

                    sub_node *sub_temp = temp->sub_link;

                    while (sub_temp != NULL)
                    {
                        if (strcmp(sub_temp->file_name, filename) == 0)
                        {
                            sub_temp->word_count++;
                            break;
                        }

                        sub_temp = sub_temp->sub_link;
                    }

                    /* file not present */
                    if (sub_temp == NULL)
                    {
                        sub_node *new_sub = malloc(sizeof(sub_node));

                        strcpy(new_sub->file_name, filename);
                        new_sub->word_count = 1;
                        new_sub->sub_link = temp->sub_link;

                        temp->sub_link = new_sub;
                        temp->file_count++;
                    }

                    break;
                }

                prev = temp;
                temp = temp->main_link;
            }

            /* word not found */
            if (temp == NULL)
            {
                main_node *new_main = malloc(sizeof(main_node));

                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->main_link = NULL;

                sub_node *new_sub = malloc(sizeof(sub_node));

                strcpy(new_sub->file_name, filename);
                new_sub->word_count = 1;
                new_sub->sub_link = NULL;

                new_main->sub_link = new_sub;

                prev->main_link = new_main;
            }
        }
    }

    fclose(fptr);
    return SUCCESS;
}