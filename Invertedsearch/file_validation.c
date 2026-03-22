#include "inverted_index.h"

/* Check file extension */
int is_txt_file(char *filename)
{
    char *ext = strrchr(filename, '.');

    if (ext != NULL && strcmp(ext, ".txt") == 0)
        return SUCCESS;

    return FAILURE;
}


/* Check if file is empty */
int is_file_empty(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("ERROR: File %s does not exist\n", filename);
        return FAILURE;
    }

    fseek(fp, 0, SEEK_END);

    if (ftell(fp) == 0)
    {
        fclose(fp);
        return SUCCESS;   // file empty
    }

    fclose(fp);
    return FAILURE;       // file not empty
}


/* Validate input files */
int validate_files(char *argv[], int argc, char valid_files[][50], int *file_count)
{
    for (int i = 1; i < argc; i++)
    {
        /* Check extension */
        if (is_txt_file(argv[i]) == FAILURE)
        {
            printf("ERROR: %s is not a .txt file\n", argv[i]);
            continue;
        }

        /* Check empty file */
        if (is_file_empty(argv[i]) == SUCCESS)
        {
            printf("ERROR: %s is empty\n", argv[i]);
            continue;
        }

        /* Check duplicate filenames */
        int duplicate = 0;

        for (int j = 0; j < *file_count; j++)
        {
            if (strcmp(valid_files[j], argv[i]) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        if (duplicate)
        {
            printf("ERROR: %s already provided\n", argv[i]);
            continue;
        }

        /* Store valid filename */
        strcpy(valid_files[*file_count], argv[i]);
        (*file_count)++;
    }

    if (*file_count == 0)
    {
        printf("ERROR: No valid files found\n");
        return FAILURE;
    }

    return SUCCESS;
}