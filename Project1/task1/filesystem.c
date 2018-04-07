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
#define MAX_NAME_LENGTH 128
#define DATA_SIZE 254
#define INDEX_SIZE 127
#define ERROR -1

typedef char data_t;
typedef unsigned short index_t;

typedef enum {DIR_ND, FILE_ND, INDEX_ND, DATA_ND} NODE_TYPE;

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

// storage blocks

NODE *memory; // allocate 2^16 blocks (in init)

char *bitvector; // allocate space for managing 2^16 blocks (in init) for managing 2^16 blocks (in init)

void file_system_create();
void file_create();
void directory_create();
void file_delete();
void directory_delete();
void create_superblock();
int find_memory_index();
void mark_in_memory(NODE *node);
// bitvector operations
void display_bitvector();
void mark_in_bitvector(char *bitvector);
char set_bit(char byte, int bit_position);
char clear_bit(char byte, int bit_position);
bool get_bit(char byte, int bit_position);
int find_empty_bit(char *bitvector);

int main(int argc, char *argv[]) {
   file_system_create();
   display_bitvector();
   return 0;
}


void file_system_create() {

   bitvector = calloc(BLOCK_SIZE, sizeof(char));
   memory = malloc( sizeof(NODE) * 65536);

   create_superblock();
}

void create_superblock(){

   time_t start = time(NULL);

   NODE *SUPERBLOCK = malloc( sizeof(NODE));
   NODE *SB_INDEX_ND = malloc(sizeof(NODE));

   SUPERBLOCK->type = DIR_ND;
   strcpy(SUPERBLOCK->content.file_desc.name, "/");
   SUPERBLOCK->content.file_desc.creation_time = start;
   SUPERBLOCK->content.file_desc.last_modification = start;
   SUPERBLOCK->content.file_desc.last_access = start;
   SUPERBLOCK->content.file_desc.access_rights = 0000;
   SUPERBLOCK->content.file_desc.size = 0;
   SUPERBLOCK->content.file_desc.block_ref = 0;

   SB_INDEX_ND->type =  INDEX_ND;
   //SB_INDEX_ND->content.

   //put_in_memory(SUPERBLOCK);
   //put_in_memory(SB_INDEX_ND);

   set_bit(bitvector[0],1);

}

void mark_in_bitvector(char *bitvector){

   int bit_position = find_empty_bit(bitvector);
}

void mark_in_memory(NODE *node){

   int mem_index = find_memory_index();
  
   if(mem_index != ERROR){
      memory[mem_index] = *node;

   }else{
      printf("ERROR: could not place a node in memory\n");
   }
}


int find_memory_index(){
   int index;

   for(index = 0; index < 65536; index++){
      if(memory[index] == NULL){
         return index;
      }
   }

   return ERROR;
}



void display_bitvector() {

   int index, bit_position;
   int char_size = 8;

   for (index = 0; index < BLOCK_SIZE; index++) {

      printf("%d : ", index);

      for (bit_position = 0; bit_position < char_size; bit_position++) {

         if(get_bit(bitvector[index], bit_position ) == true){
            printf("TRUE\n");
         }else if(get_bit(bitvector[index], bit_position ) == false){
            printf("FALSE\n");
         }

         printf("%u ", get_bit(bitvector[index], bit_position ));
      }

      printf("\n");
   }
}



bool get_bit(char byte, int bit_position) {
   return ((byte & ( 1 << bit_position)) != 0);
}

char set_bit(char byte, int bit_position) {
    return (byte | (1 << bit_position));
}

char clear_bit(char byte, int bit_position) {
   int mask = ~(1 << bit_position);
   return (byte & mask);
}

void mark_empty_bit(char *bitvector){
   int bv_index, bit_position;
   int char_size = 8;

   for(bv_index = 0; bv_index < BLOCK_SIZE; bv_index++){
      
      for(bit_position = 0; bit_position < char_size; bit_position++){
         
         if(get_bit(bitvector[bv_index], bit_position) == true){
            set_bit(bitvector[bv_index], bit_position);
            return;

         }
      }
   }


}





