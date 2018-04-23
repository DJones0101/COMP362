/*
* Darius Jones
* Project 1 task 1
* 4/15/2018
*/

#include "filesystem.h"

void file_system_create() {
   allocate();
   create_superblock();
}


void directory_delete(NODE *directory_node, NODE *home_dir) {
   
   int index;
   int dir_location = find_node(directory_node->content.file_desc.name);
   int directory_node_indexND = directory_node->content.file_desc.block_ref;
   NODE *dir_indexND = memory[directory_node_indexND];

   bool is_superblock = (strcmp(directory_node->content.file_desc.name, "/") == 0) ? true : false;

   if(is_superblock == true || (dir_location ==  0)){ return;} 


   int num_of_content = directory_node->content.file_desc.size;

   for(index = 0; index < num_of_content; index++){

      int memory_location = dir_indexND->content.index[index];
   

      if(memory[memory_location]->type == DIR_ND){

         int memory_location = home_dir->content.file_desc.block_ref;

         // home_dir's indexND
         // memory[memory_location];
         
         int location_in_indexND = find_index_slot(memory[memory_location],dir_location);
         memory[memory_location]->content.index[location_in_indexND] = ERROR;

         directory_delete(directory_node, memory[memory_location]);
      
      }else if(memory[memory_location]->type == FILE_ND){
         
         file_delete(directory_node, memory[memory_location]->content.file_desc.name);
      
      }
   }

   remove_from_bitvector(dir_location);
   remove_from_bitvector(directory_node_indexND);
   free(directory_node);
}


void file_delete(NODE *home_dir, char *name) {


   //bool is_superblock = (strcmp(home_dir->content.file_desc.name, "/") == 0) ? true : false;

   //if(is_superblock == )[]
   int index = find_node(name);
   NODE *file = memory[index];
   home_dir->content.file_desc.size--;
   memory[home_dir->content.file_desc.block_ref]->content.index[index] = -1;

  // int data_index = file->content.file_desc.block_ref;
  // NODE *data_holder = memory[data_index];
   int file_index = find_node(name);


   

   if (file->content.file_desc.size > 0 ) {

      //remove_from_bitvector(data_index);
      //free(data_holder);
   }


   if (file_index != ERROR) {
      remove_from_bitvector(file_index);
      free(file);

   }

}


void file_create(NODE *home_dir, char *name) {

   NODE *file_node = malloc(sizeof(NODE));
   //NODE *data_node = malloc(sizeof(NODE));

   int file_index = get_free_index();
   add_to_bitvector(file_index);

   //int data_index = get_free_index();
   //add_to_bitvector(data_index);

   directoryIndex_add(home_dir, file_index);
   //directoryIndex_add(home_dir,data_index);

   time_t start = time(NULL);
   file_node->type = FILE_ND;
   strcpy(file_node->content.file_desc.name, name);
   file_node->content.file_desc.creation_time = start;
   file_node->content.file_desc.last_modification = start;
   file_node->content.file_desc.last_access = start;
   file_node->content.file_desc.owner_id = getpid();
   file_node->content.file_desc.access_rights = 0777;
   file_node->content.file_desc.size = 0;
   //file_node->content.file_desc.block_ref = data_index;

   memory[file_index] = file_node;
   //memory[data_index] = data_node;

}

void directory_create(NODE *home_dir, char *name) {

   time_t start = time(NULL);

   int dir_index = get_free_index();
   add_to_bitvector(dir_index);

   int memory_index = get_free_index();
   add_to_bitvector(memory_index);

   directoryIndex_add(home_dir, dir_index);


   NODE *new_directory = malloc(sizeof(NODE));
   NODE *index_node = malloc(sizeof(NODE));

   new_directory->type = DIR_ND;
   index_node->type = INDEX_ND;



   strcpy(new_directory->content.file_desc.name, name);
   new_directory->content.file_desc.creation_time = start;
   new_directory->content.file_desc.last_modification = start;
   new_directory->content.file_desc.last_access = start;
   new_directory->content.file_desc.owner_id = getpid();
   new_directory->content.file_desc.access_rights = 0777;
   new_directory->content.file_desc.block_ref = memory_index;
   new_directory->content.file_desc.size = 0;

   memory[dir_index] = new_directory;
   memory[memory_index] = index_node;

}

void assign_to_index_node(NODE *index_node, int memory_index) {

   int count;
   for (count = 0; count < INDEX_SIZE; count++) {
      if (index_node->content.index[count] == 0) {
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


int find_node(char *name) {
   int count;

   for (count = 2; count < MAX_MEMORY; count++) {

      if(memory[count]->type == DIR_ND || memory[count]->type == FILE_ND){

      bool found = (strcmp(memory[count]->content.file_desc.name, name) == 0) ? true : false;
      if (found == true) {
         return count;
      }
   }

   }

   return ERROR;
}

int find_index_slot(NODE *index_nd, int memory_location){
   int count;
   for(count = 0; count < INDEX_SIZE; count++){
      if(memory_location == index_nd->content.index[count]){

         return count;
      }
   }

   return ERROR;
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
   for (index = 0;  index < 80; index++) { // we don't need to print them all, there's to many.

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


void directoryIndex_add(NODE *home_dir, int index) { // adding to contnent of a directory
   int homeDirIndexNode = home_dir->content.file_desc.block_ref;
   assign_to_index_node(memory[homeDirIndexNode], index);
   home_dir->content.file_desc.size++;
}

void free_system() {
   int count;
   for (count = 0; count < MAX_MEMORY; count++) {
      free(memory[count]);
   }

   free(bitvector);

}




