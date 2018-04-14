/*
* Darius Jones
* Project 1 task 1
* 4/5/2018
*/

#include "filesystem.h"

/*

   Redo the the bitvector. the size should be number of block / 8, which is
   65536/8 = 8192. Indexes of the bitvector are from 0 to 8191 {not 0...7, 0...7}.
   This will make it easy to delete things later.

   The permissions of everything create should be read and write 0777.

   bitvector operations :
       set
       clear
       display

*/

void file_system_create() {
   allocate();
   create_superblock();
   
   file_create(memory[0], "file.txt");
   directory_create(memory[0], "/sub_folder");
   display_bitvector();
}

void file_delete(NODE *file_node) {



}


void file_create(NODE *directory_node, char *name) {

   NODE *file_node = malloc(sizeof(NODE));
   time_t start = time(NULL);
   int memory_index = get_free_index();
   add_to_bitvector(memory_index);
   file_node->type = FILE_ND;
   strcpy(file_node->content.file_desc.name, name);
   file_node->content.file_desc.creation_time = start;
   file_node->content.file_desc.last_modification = start;
   file_node->content.file_desc.last_access = start;
   file_node->content.file_desc.owner_id = getpid();
   file_node->content.file_desc.access_rights = 0777;
   add_to_bitvector(memory_index);
}

void directory_create(NODE *directory_node, char *name) {

   time_t start = time(NULL);
   int dir_index = get_free_index();
   add_to_bitvector(dir_index);
   int memory_index = get_free_index();
   add_to_bitvector(memory_index);

   NODE *home_index = memory[directory_node->content.file_desc.block_ref];
   assign_to_index_node(home_index, dir_index);

   NODE *new_directory = malloc(sizeof(NODE));
   NODE *index_node = malloc(sizeof(NODE));

   new_directory->type = DIR_ND;
   index_node->type = INDEX_ND;

   memory[dir_index] = new_directory;
   memory[memory_index] = index_node;

   strcpy(new_directory->content.file_desc.name, name);
   new_directory->content.file_desc.creation_time = start;
   new_directory->content.file_desc.last_modification = start;
   new_directory->content.file_desc.last_access = start;
   new_directory->content.file_desc.owner_id = getpid();
   new_directory->content.file_desc.access_rights = 0777;
   new_directory->content.file_desc.block_ref = memory_index;

}

void assign_to_index_node(NODE *index_node, int memory_index) {

   int count;
   for (count = 0; count < INDEX_SIZE; count++) {
      if (index_node->content.index[count] != 0) {
         index_node->content.index[count] = memory_index;
         return;
      }
   }

}

void allocate() {
   bitvector = calloc(BITVECTOR_SIZE, sizeof(char));
   int count;
   for (count = 0; count < MAX_MEMORY; count++) {
      memory[count] = malloc(sizeof(NODE));
   }
}

void create_superblock() {
   time_t start = time(NULL);
   NODE *SUPERBLOCK = malloc(sizeof(NODE));
   NODE *SB_INDEX_ND = malloc(sizeof(NODE));
   memory[0] = SUPERBLOCK;
   memory[1] = SB_INDEX_ND;
   SUPERBLOCK->type = DIR_ND;
   SB_INDEX_ND->type = INDEX_ND;
   strcpy(SUPERBLOCK->content.file_desc.name, "/");
   SUPERBLOCK->content.file_desc.creation_time = start;
   SUPERBLOCK->content.file_desc.last_modification = start;
   SUPERBLOCK->content.file_desc.last_access = start;
   SUPERBLOCK->content.file_desc.owner_id = getpid();
   SUPERBLOCK->content.file_desc.access_rights = 0000;
   SUPERBLOCK->content.file_desc.block_ref = 1;
   add_to_bitvector(0); // SUPERBLOCk location in memory
   add_to_bitvector(1); // SUPERBLOCK's index node's location in memory
}

void add_to_bitvector(int memory_index) {
   set_bit(memory_index);
}

void remove_from_bitvector(int memory_index) {
   clear_bit(memory_index);
}

void set_bit(int memory_index) {
   int byte = (memory_index / 8);
   int bit =  (memory_index % 8);
   bitvector[byte] = (bitvector[byte] | (1 << bit));
}

void clear_bit(int memory_index) {
   int byte = (memory_index / 8);
   int bit =  (memory_index % 8);
   bitvector[byte] = (bitvector[byte] & (~(1 << bit)));
}

int get_free_index() {
   int index;
   for (index = 0; index < MAX_MEMORY; index++) {
      if (test_bit(index) == false) {
         return index;
      }
   }
   return ERROR;
}

bool test_bit(int memory_index) {
   int byte = (memory_index / 8);
   int bit =  (memory_index % 8);
   return ((bitvector[byte] & (1 << bit)) != 0);

}

void display_bitvector() {
   int index;
   int bit_counter = 0;
   for (index = 0;  index < 256; index++) { // we don't need to print them all, there's to many.

      if (bit_counter == 0) {
         printf("byte # %d: ", index / 8);
      }

      printf("%u ", test_bit(index));
      bit_counter++;

      if (bit_counter == 8) {
         printf("\n");
         bit_counter = 0;
      }
   }
}






