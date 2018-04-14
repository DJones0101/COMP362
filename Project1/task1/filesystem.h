/*
* Darius Jones
* Project 1 task 1
* 4/5/2018
*/

#ifndef  _filesystem_h_
#define  _filesystem_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "filesystem.h"

#define BLOCK_SIZE 256
#define MAX_MEMORY 65536
#define MAX_NAME_LENGTH 128
#define DATA_SIZE 254
#define INDEX_SIZE 127
#define BITVECTOR_SIZE (MAX_MEMORY/8)
#define ERROR -1

/*

                     Access Rights

Number   Octal Permission Representation                                Ref
0        No permission                                                  ---
1        Execute permission                                             --x
2        Write permission                                               -w-
3        Execute and write permission: 1 (execute) + 2 (write) = 3      -wx
4        Read permission                                                r--
5        Read and execute permission: 4 (read) + 1 (execute) = 5        r-x
6        Read and write permission: 4 (read) + 2 (write) = 6            rw-
7        All permissions: 4 (read) + 2 (write) + 1 (execute) = 7        rwx

*/

typedef char data_t;
typedef unsigned short index_t;

typedef enum {DIR_ND = 0, FILE_ND, INDEX_ND, DATA_ND} NODE_TYPE;

typedef struct fd_node {

   char name[MAX_NAME_LENGTH];
   time_t creation_time;
   time_t last_access;
   time_t last_modification;
   mode_t access_rights;
   unsigned short owner_id;
   unsigned short size;
   index_t block_ref;

} FD_NODE;

typedef struct node {
   NODE_TYPE type;

   union {
      FD_NODE file_desc;
      data_t data[DATA_SIZE];
      index_t index[INDEX_SIZE];
   } content;
} NODE;

NODE *memory[MAX_MEMORY]; // allocate 2^16 blocks (in init)
char *bitvector;

void file_system_create();
void file_create(NODE *home_dir, char *name);
void directory_create(NODE *directory_node, char *name);
void file_delete(NODE *home_dir, char *name);
void directory_delete(NODE *directory_node);
void create_superblock();
void allocate();
int get_free_index();
void assign_to_index_node(NODE *index_node, int memory_index);
void directoryIndex_add(NODE *home_dir, int index);
void directoryIndex_remove(NODE *home_dir);
void free();

// bitvector operations
void display_bitvector();
void set_bit(int memory_index);
void clear_bit(int memory_index);
bool test_bit(int memory_index);
void add_to_bitvector(int memory_index);
void remove_from_bitvector(int memory_index);

#endif