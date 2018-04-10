/*
* Darius Jones
* Project 1 task 1
* 4/5/2018
*/
#include "filesystem.h"

int main(int argc, char *argv[]) {
   file_system_create();
   display_bitvector();
   return 0;
}


void file_system_create() {

   allocate_blocks();
   create_superblock();
}

void directory_create(NODE *directory_node) {

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

   NODE *file_node = malloc(sizeof(NODE));
   file_node->type = FILE_ND;
   place_in_memory(file_node);

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

   SUPERBLOCK->type = DIRECTORY_ND;
   strcpy(SUPERBLOCK->content.file_desc.name, "/");
   SUPERBLOCK->content.file_desc.creation_time = start;
   SUPERBLOCK->content.file_desc.last_modification = start;
   SUPERBLOCK->content.file_desc.last_access = start;
   SUPERBLOCK->content.file_desc.access_rights = 0000;
   SB_INDEX_ND->type =  INDEX_ND;
   place_in_memory(SUPERBLOCK);
   place_in_memory(SB_INDEX_ND);

}


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




