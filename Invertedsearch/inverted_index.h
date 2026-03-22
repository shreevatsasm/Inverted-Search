#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1

#define MAX_FILES 20
#define HASH_SIZE 27


/* Sub Node */
typedef struct sub_node
{
    int word_count;
    char file_name[50];
    struct sub_node *sub_link;

} sub_node;


/* Main Node */
typedef struct main_node
{
    int file_count;
    char word[50];

    sub_node *sub_link;
    struct main_node *main_link;

} main_node;


/* File validation functions */

int validate_files(char *argv[], int argc, char valid_files[][50], int *file_count);
int is_txt_file(char *filename);
int is_file_empty(char *filename);


/* Database operations */

int create_database(main_node *hashtable[], char *filename);
void display_database(main_node *hashtable[]);
void search_database(main_node *hashtable[]);
void save_database(main_node *hashtable[]);
void update_database(main_node *hashtable[]);


#endif