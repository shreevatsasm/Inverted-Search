#include "inverted_index.h"

void display_database(main_node *hashtable[])
{
    main_node *m_temp;
    sub_node *s_temp;

    for (int i = 0; i < HASH_SIZE; i++)
    {
        /* check if index empty */
        if (hashtable[i] == NULL)
        {
            continue;
        }

        m_temp = hashtable[i];

        /* loop main nodes */
        while (m_temp != NULL)
        {
            printf("\nIndex : %d\n", i);
            printf("Word : %s  File Count : %d\n",
                   m_temp->word,
                   m_temp->file_count);

            s_temp = m_temp->sub_link;

            /* loop sub nodes */
            while (s_temp != NULL)
            {
                printf("File : %s  Word Count : %d\n",
                       s_temp->file_name,
                       s_temp->word_count);

                s_temp = s_temp->sub_link;
            }

            m_temp = m_temp->main_link;
        }
    }
}