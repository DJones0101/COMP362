/*
* Darius Jones
* Project 1 task 2
* 4/15/2018
*/

#include "filesystem.h"

int numOfEntries_global = 0;
int numOfEntries_local = 0;


void file_system_create() {
   allocate();
   create_superblock();
   create_tables();
}


void directory_delete(NODE *directory_node, NODE *home_dir) {

   int index;
   int dir_location = find_node(directory_node->content.file_desc.name);
   int directory_node_indexND = directory_node->content.file_desc.block_ref;
   NODE *dir_indexND = memory[directory_node_indexND];

   bool is_superblock = (strcmp(directory_node->content.file_desc.name, "/") == 0) ? true : false;

   if (is_superblock == true || (dir_location ==  0)) { return;}


   int num_of_content = directory_node->content.file_desc.size;

   for (index = 0; index < num_of_content; index++) {

      int memory_location = dir_indexND->content.index[index];


      if (memory[memory_location]->type == DIR_ND) {

         int memory_location = home_dir->content.file_desc.block_ref;

         // home_dir's indexND
         // memory[memory_location];

         int location_in_indexND = find_index_slot(memory[memory_location], dir_location);
         memory[memory_location]->content.index[location_in_indexND] = ERROR;

         directory_delete(directory_node, memory[memory_location]);

      } else if (memory[memory_location]->type == FILE_ND) {

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
   file_node->content.file_desc.access_rights = ALL_PERMISSION;
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
   new_directory->content.file_desc.access_rights = ALL_PERMISSION;
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
   SUPERBLOCK->content.file_desc.access_rights = NO_PERMISSION;
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

      bool found = (strcmp(memory[count]->content.file_desc.name, name) == 0) ? true : false;
      if (found == true) {
         return count;
      }

   }

   return ERROR;
}

int find_index_slot(NODE *index_nd, int memory_location) {
   int count;
   for (count = 0; count < INDEX_SIZE; count++) {
      if (memory_location == index_nd->content.index[count]) {

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

//--------------------------------Task 2--------------------------------------------------------------------

void create_tables() {
   int count;

   for (count = 0; count < MAX_OPEN_PER_PROCESS; count++) {
      local_table[count].global_ref = EMPTY;
   }

   global_table = (struct global_item*)malloc(GLOBAL_TABLE_SIZE * sizeof(struct global_item*));
}

unsigned short hash_code(char *key) {

   //sdbm hasing algorithm
   unsigned short hash = 0;
   unsigned short count;
   int length = strlen(key);

   for (count = 0; count < length; count++) {

      hash = key[count] + (hash << 6) + (hash << 16 ) - hash;
   }

   return hash;
}


void insert_global(char *key) {

   int hash_index = hash_code(key);
   int index = find_node(key);

   //printf("hash_index = %u", hash_index);

   struct global_node *item = (struct global_node*)malloc(sizeof(struct global_node));
   
   struct global_node *list = (struct global_node*) global_table[hash_index].head;
   

   item->fd = index;
   item->data_index = memory[index]->content.file_desc.block_ref;
   item->reference_count++;
   item->access_rights = memory[index]->content.file_desc.access_rights;
   item->size = memory[index]->content.file_desc.size;



   if (list == NULL) {

      global_table[hash_index].head = item;
      global_table[hash_index].tail = item;
      numOfEntries_global++;

   } else {
      int find = find_item(global_table[hash_index].head, key);

      if (find == ERROR) {

         global_table[hash_index].tail->next = item;
         global_table[hash_index].tail = item;
         numOfEntries_global++;

      }
   }


}



struct global_node* get_item_global(char *key) {

   int hash_index = hash_code(key);

   struct global_node *list = (struct global_node*) global_table[hash_index].head;



   while (list != NULL) {

      if (list->fd == find_node(key)) {
         return list;
      }

      list = list->next;
   }

   return NULL;

}

void delete_item_global(char *key) {

   int hash_index = hash_code(key);

   struct global_node *list = (struct global_node*) global_table[hash_index].head;

   if (list == NULL) {

      return;

   } else {

      int find = find_item(list, key);

      if (find == ERROR) {

         return;

      } else {

         struct global_node *temp = list;

         if (temp->fd == find_node(key)) {

            global_table[hash_index].head = temp->next;
            return;
         }

         while (temp->next->fd != find_node(key)) {

            temp = temp->next;
         }

         if (global_table[hash_index].tail == temp->next) {

            temp->next = NULL;
            global_table[hash_index].tail = temp;

         } else {

            temp->next = temp->next->next;
         }
      }
   }
}

void display_table_global() {

   int count;

   for (count = 0; count < MAX_OPEN_PER_PROCESS; count++ ) {

      struct global_node *temp = global_table[count].head;

      if (temp == NULL) {

         printf("global_table[%d] EMPTY\n", count);

      } else {

         while (temp != NULL) {

            global_toPrint(temp);

            temp = temp->next;
         }
         printf("\n");
      }
   }

}



void insert_local(char *key) {


   struct global_node *list = get_item_global(key);

   int index = find_emptyLocal();

   if (index != ERROR) {
      local_table[index].global_ref = list->access_rights;
      local_table[index].access_rights = list->fd;

   }

}

struct local_item* get_item_local(char *key) {

   int hash_index = hash_code(key);
   int count;
   struct local_item *to_find = NULL;
   for (count = 0; count < MAX_OPEN_PER_PROCESS; count++) {

      if (local_table[count].global_ref == hash_index) {

         to_find = &local_table[count];
         break;
      }
   }

   return to_find;

}

void delete_item_local(char *key) {

   int hash_index = hash_code(key);
   int count;

   for (count = 0; count < MAX_OPEN_PER_PROCESS; count++) {

      if (local_table[count].global_ref == hash_index) {

         local_table[count].global_ref = EMPTY;
         break;
      }
   }

}

int find_emptyLocal() {

   int count;
   for (count = 0; count < MAX_OPEN_PER_PROCESS; count++) {
      if (local_table[count].global_ref == EMPTY) {
         return count;
      }
   }

   return ERROR;
}


void open_file(NODE *path, char *file_name, mode_t access_rights) {


   file_create(path, file_name);
   int index = find_node(file_name);
   NODE *new_file =  memory[index];
   new_file->content.file_desc.access_rights = access_rights;

   insert_global(file_name);
   insert_local(file_name);
}


void read_file(char *file_name) {

   int in_mem = find_node(file_name);
   int file_size = memory[in_mem]->content.file_desc.size;

   if ( file_size < DATA_SIZE) {

      int num_of_content = memory[in_mem]->content.file_desc.size;
      int dataNodeIndex = memory[in_mem]->content.file_desc.block_ref;
      print_data(dataNodeIndex, num_of_content);

   } else {


      int num_of_content = memory[in_mem]->content.file_desc.size;
      int index_node = memory[in_mem]->content.file_desc.block_ref;
      int numOfnodes = num_of_dataNDs(file_size);


      int count;

      for (count = 0; count < numOfnodes; count++) {


         if (num_of_content > DATA_SIZE) {

            print_data(memory[index_node]->content.index[count], DATA_SIZE);
            num_of_content -= DATA_SIZE;

         } else if (num_of_content < DATA_SIZE) {

            print_data(memory[index_node]->content.index[count], num_of_content);

         }

      }

   }

}

void write_file(char *what_to_write,  char *file_name) {

   int file_location = find_node(file_name);

   if (memory[file_location]->content.file_desc.access_rights == READ_PERMISSION) {return;}

   int in_mem = find_node(file_name);
   int file_size = memory[in_mem]->content.file_desc.size;

   if ( file_size < DATA_SIZE) {


      NODE *data_node = data_node_create(false, NULL);


      if (file_size == 0) {

         strcpy(data_node->content.data, what_to_write);

      } else if ( file_size > 0) {

         append_data(data_node->content.data, what_to_write);
      }


   } else if (file_size > DATA_SIZE) {


      //int numOfnodes = num_of_dataNDs(file_size);
      int num_of_content = strlen(what_to_write);
      int tracker = 0;
      int count;

      NODE *index_node = malloc(sizeof(NODE));
      int index =  get_free_index();
      add_to_bitvector(index);
      memory[index] = index_node;
      NODE *data_node;
      data_node = data_node_create(true, index_node);




      for (count = 0; count < num_of_content; count++) {


         append_data(data_node->content.data, &what_to_write[count]);
         tracker++;
         if (tracker == DATA_SIZE) {
            tracker = 0;
            data_node = data_node_create(true, index_node);
         }


      }


   }




}

void close_file(char *file_name) {

   struct global_node *list = get_item_global(file_name);

   unsigned short reference_count = list->reference_count;

   if (reference_count > 0) {
      return;

   } else {

      delete_item_local(file_name);
      delete_item_global(file_name);
   }



}


int num_of_dataNDs( int num_of_bytes) {

   int retVal;

   if ( (num_of_bytes % DATA_SIZE) == 0 ) {

      retVal = num_of_bytes / DATA_SIZE;

   } else {

      retVal = (num_of_bytes / DATA_SIZE) + 1;
   }

   return retVal;
}

void print_data(int dataNodeIndex, int num_of_content) {
   int count;
   for (count = 0; count < num_of_content; count++ ) {
      printf("%c ", memory[dataNodeIndex]->content.data[count]);
   }
   printf("\n");
}

void append_data(char *des, char *src) {

   strcat(des, src);
}

NODE* data_node_create(bool need_indexNd, NODE* index_node) {

   int dataIndex = get_free_index();
   NODE *data_node = malloc(sizeof(NODE));
   data_node = memory[dataIndex];
   add_to_bitvector(dataIndex);

   if (need_indexNd == true) {
      assign_to_index_node(index_node, dataIndex);
   }

   return data_node;
}

int find_item(struct global_node *list, char *key) {
   int retVal = 0;

   struct global_node *temp = list;

   while (temp != NULL) {

      if (temp->fd == find_node(key)) {

         return retVal;
      }

      temp = temp->next;
      retVal++;

   }

   return ERROR;
}

void global_toPrint(struct global_node *node) {
   printf("fd %d\n", node->fd );
   printf("data_index %u\n", node->data_index);
   printf("reference_count %u\n", node->reference_count);
   printf("access_rights %u\n", node->access_rights);
   printf("size %u\n", node->size );
}