#include "inverted_index.h"

void save_database(main_node *hashtable[])
{
    char filename[50];

    printf("Enter the file name to save database: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("ERROR: Unable to create file\n");
        return;
    }

    main_node *m_temp;
    sub_node *s_temp;

    for (int i = 0; i < HASH_SIZE; i++)
    {
        if (hashtable[i] == NULL)
            continue;

        m_temp = hashtable[i];

        while (m_temp != NULL)
        {
            /* write index + word + file_count */
            fprintf(fp, "# %d %s %d ",
                    i,
                    m_temp->word,
                    m_temp->file_count);

            s_temp = m_temp->sub_link;

            /* write sub nodes */
            while (s_temp != NULL)
            {
                fprintf(fp, "%s %d ",
                        s_temp->file_name,
                        s_temp->word_count);

                s_temp = s_temp->sub_link;
            }

            fprintf(fp, "\n");

            m_temp = m_temp->main_link;
        }
    }

    fclose(fp);

    printf("Database saved successfully in %s\n", filename);
}