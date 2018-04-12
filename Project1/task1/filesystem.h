#ifndef  _filesystem_h_
#define  _filesystem_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "filesystem.h"

#define BLOCK_SIZE 256
#define MAX_MEMORY 65536
#define MAX_NAME_LENGTH 128
#define DATA_SIZE 254
#define INDEX_SIZE 127
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

   //int byte_index; not needed
   //int bit_position; not needed

} NODE;

// storage blocks
// owener id = pid

NODE *memory[MAX_MEMORY]; // allocate 2^16 blocks (in init)
char *bitvector; 
//
void file_system_create();
void file_create(NODE *directory_node);
void directory_create(NODE *directory_node);
void file_delete(NODE *file_node);
void directory_delete(NODE *directory_node);
void create_superblock();
int find_empty_memory_index();
void place_in_memory(NODE *node);
void allocate_blocks();
int find_empty_indexND_index(NODE *index_node);
void place_in_indexND(NODE *file_node, NODE *index_node);
void free_nodes();
void free_blocks();

// bitvector operations
void display_bitvector();
void mark_in_bitvector(char *bitvector);
char set(char byte, int bit_position);
char clear(char byte, int bit_position);
bool is_bit_set(char byte, int bit_position);
void mark_empty_bit(char *bitvector, NODE *node);
void mark_remove_bit(char *bitvector, NODE *node); 

#endif