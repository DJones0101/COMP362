/*
* Darius Jones
* Project 1 task 1
* 4/5/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLOCK_SIZE 256
#define MAX_NAME_LENGTH 128
#define DATA_SIZE 254
#define INDEX_SIZE 127

typedef char data_t;
typedef unsigned short index_t;

typedef enum {DIR_ND, FILE_ND, INDEX_ND, DATA_ND} NODE_TYPE;

typedef struct fd_node {

   char name[MAX_NAME_LENGTH];
   time_t creation;
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
// bitvector operations
void display_bitvector();
int set_bit(char byte, int bit_position);
bool test_bit(char byte, int bit_position);
int clear_bit(char byte, int bit_position);
void find_empty_bit();
int get_bit(char byte, int bit_position);

int main(int argc, char *argv[]) {
   file_system_create();
   display_bitvector();
   return 0;
}


void file_system_create() {

   bitvector = calloc(BLOCK_SIZE, sizeof(char));
   memory = malloc( sizeof(NODE) * 65536);


}


void display_bitvector(){

   int index, bit_position; 
   int char_size = 8;

   for(index = 0; index < BLOCK_SIZE; index++){

      printf("%d : ", index);

      for(bit_position = 0; bit_position < char_size; bit_position++){

         printf("%d ",get_bit(bitvector[index],bit_position ));
      }

      printf("\n");
   }
}

int get_bit(char byte, int bit_position){
   int mask = 0x1;
   return (byte & (mask << (bit_position - 1)));
}

int set_bit(char byte, int bit_position){
   int mask = 0x1;
   return (byte | (mask << bit_position));
}

int clear_bit(char byte, int bit_position){
   int mask = ~(0x1 << bit_position);
   return (byte & mask);
}

bool test_bit(char byte, int bit_position){
   int mask = 0x1;
   return ((byte & (mask << bit_position)) == 1) ? true : false;
}