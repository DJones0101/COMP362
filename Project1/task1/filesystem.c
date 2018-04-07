/*
* Darius Jones
* Project 1 task 1
* 4/5/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

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

typedef enum {DIRECTORY_ND=0, FILE_ND, INDEX_ND, DATA_ND} NODE_TYPE;

typedef struct fd_node {c

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

// storage blocks

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
void mark_empty_bit(char *bitvector);


int main(int argc, char *argv[]) {
   file_system_create();
   display_bitvector();
   return 0;
}


void file_system_create() {

   allocate_blocks();
   create_superblock();
}

void directory_create(NODE *directory_node){
   
   time_t start = time(NULL);
  

   NODE *directory = malloc(sizeof(NODE));
   NODE *index_node = malloc(sizeof(NODE));

   directory->type = INDEX_ND;
   directory->content.file_desc.creation_time = start;
   directory->content.file_desc.last_modification = start;
   directory->content.file_desc.last_access = start;
   directory->content.file_desc.access_rights = 0777;
   index_node->type =  INDEX_ND;
   place_in_memory(directory);
   place_in_memory(index_node);


}

void file_create(NODE *directory_node) {

   NODE *file = malloc(sizeof(NODE));
   NODE *data = malloc(sizeof(NODE));
   data->type = DATA_ND;
   file->type = FILE_ND;

   place_in_memory(file);
   place_in_memory(data);
   file->content.file_desc.size = 0;

}


void allocate_blocks() {

   bitvector = calloc(BLOCK_SIZE, sizeof(char));
   int count;
   for (count = 0; count < MAX_MEMORY; count++) {
      memory[count] = malloc(sizeof(NODE));
   }
}

void create_superblock() {

   time_t start = time(NULL);

   NODE *SUPERBLOCK = malloc(sizeof(NODE));
   NODE *SB_INDEX_ND = malloc(sizeof(NODE));

   SUPERBLOCK->type = DIR_ND;
   strcpy(SUPERBLOCK->content.file_desc.name, "/");
   SUPERBLOCK->content.file_desc.creation_time = start;
   SUPERBLOCK->content.file_desc.last_modification = start;
   SUPERBLOCK->content.file_desc.last_access = start;
   SUPERBLOCK->content.file_desc.access_rights = 0000;
   SB_INDEX_ND->type =  INDEX_ND;
   place_in_memory(SUPERBLOCK);
   place_in_memory(SB_INDEX_ND);

}

void place_in_memory(NODE *node) {

   int index = find_empty_memory_index();
   if (index != ERROR) {
      node->content.file_desc.block_ref = index;
      memory[index] = node;
      mark_empty_bit(bitvector);
   } else {
      printf("ERROR: in place_in_memory\n");
   }
}

void place_in_indexND(NODE *file_node, NODE *index_node) {

   int index = find_empty_indexND_index(INDEX_NODE);
   if (index != ERROR) {
      INDEX_NODE->content.index[index] = FILE_ND->content.file_desc.block_ref;
   } else {
      printf("ERROR: in place_in_indexND\n");
   }
}

int find_empty_indexND_index(NODE *index_node) {

   int index;
   for (index = 0; index < INDEX_SIZE; index++) {
      if (INDEX_NODE->content.index[index] != 0) {
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

void mark_empty_bit(char *bitvector) {

   int bv_index;
   int bit_position;
   int char_size = 8;

   for (bv_index = 0; bv_index < BLOCK_SIZE; bv_index++) {

      for (bit_position = 0; bit_position < char_size; bit_position++) {

         if (is_bit_set(bitvector[bv_index], bit_position) == false) {

            bitvector[bv_index] = set(bitvector[bv_index], bit_position);
            return;

         }
      }
   }


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




