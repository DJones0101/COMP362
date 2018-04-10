
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

typedef enum {DIRECTORY_ND = 0, FILE_ND, INDEX_ND, DATA_ND} NODE_TYPE;

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

   int byte_index;
   int bit_position;

} NODE;

// storage blocks
// owener id = pid

NODE *memory[MAX_MEMORY]; // allocate 2^16 blocks (in init)
char *bitvector; // allocate space for managing 2^16 blocks (in init) for managing 2^16 blocks (in init)
//
void file_system_create();
void file_create(NODE *directory_node);
void directory_create(NODE *directory_node);
void file_delete(NODE *file_node);
void directory_delete(NODE *directory_node);
//
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

int find_memory_index(char name[]) {
   int index;
   int found = 0;
   for (index = 0; index < MAX_MEMORY; index++) {
      if (strcmp(name, memory[index]->content.file_desc.name) == found) {
         return index;
      }
   }

   return ERROR;
}



void place_in_memory(NODE *node) {

   int index = find_empty_memory_index();
   if (index != ERROR) {
      node->content.file_desc.block_ref = index;
      memory[index] = node;
      mark_empty_bit(bitvector, node);
   } else {
      printf("ERROR: in place_in_memory\n");
   }
}

void place_in_indexND(NODE *file_node, NODE *index_node) {

   int index = find_empty_indexND_index(index_node);
   if (index != ERROR) {
      index_node->content.index[index] = file_node->content.file_desc.block_ref;
   } else {
      printf("ERROR: in place_in_indexND\n");
   }
}

int find_empty_indexND_index(NODE *index_node) {

   int index;
   for (index = 0; index < INDEX_SIZE; index++) {
      if (index_node->content.index[index] != 0) {
         return index;
      }
   }

   return ERROR;

}

int find_empty_memory_index() {
   int index;

   for (index = 0; index < 65536; index++) {
      if (memory[index] != NULL) {
         return index;
      }
   }

   return ERROR;
}

void mark_empty_bit(char *bitvector, NODE *node) {

   int bv_index;
   int bit_position;
   int char_size = 8;

   for (bv_index = 0; bv_index < BLOCK_SIZE; bv_index++) {

      for (bit_position = 0; bit_position < char_size; bit_position++) {

         if (is_bit_set(bitvector[bv_index], bit_position) == false) {

            bitvector[bv_index] = set(bitvector[bv_index], bit_position);
            node->bit_position = bit_position;
            node->byte_index = bv_index;
            return;

         }
      }
   }
}

void remove_from_bitvector( NODE *node) {
  // int mem_index = find_memory_index(node->content.file_desc.name);
  // int bv_index =

}

void display_bitvector() {

   int index, bit_position;
   int char_size = 8;

   for (index = 0; index < BLOCK_SIZE; index++) {

      printf("%d : ", index);

      for (bit_position = 0; bit_position < char_size; bit_position++) {

         printf("%u ", is_bit_set(bitvector[index], bit_position ));
      }

      printf("\n");
   }
}



bool is_bit_set(char byte, int bit_position) {
   return ((byte & (1 << bit_position)) != 0);
}

char set(char byte, int bit_position) {
   return (byte | (1 << bit_position));
}

char clear(char byte, int bit_position) {
   return (byte & (~(1 << bit_position)));
}

#endif
