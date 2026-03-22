#include "inverted_index.h"

void search_database(main_node *hashtable[])
{
    char word[50];

    printf("Enter the word to search: ");
    scanf("%s", word);

    int index;

    /* find index */
    if (isalpha(word[0]))
        index = tolower(word[0]) - 'a';
    else
        index = 26;

    /* check hashtable[index] */
    if (hashtable[index] == NULL)
    {
        printf("Word not found in database\n");
        return;
    }

    main_node *m_temp = hashtable[index];

    /* loop main nodes */
    while (m_temp != NULL)
    {
        if (strcmp(m_temp->word, word) == 0)
        {
            printf("Word : %s\n", m_temp->word);
            printf("File count : %d\n", m_temp->file_count);

            sub_node *s_temp = m_temp->sub_link;

            /* loop sub nodes */
            while (s_temp != NULL)
            {
                printf("File : %s  Word Count : %d\n",
                       s_temp->file_name,
                       s_temp->word_count);

                s_temp = s_temp->sub_link;
            }

            return;
        }

        m_temp = m_temp->main_link;
    }

    printf("Word not found in database\n");
}