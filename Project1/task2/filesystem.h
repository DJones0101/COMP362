/*
* Darius Jones
* Project 1 task 2
* 4/15/2018
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
#define EMPTY -2
#define READ_PERMISSION 0444
#define WRITE_PERMISSION 0222
#define NO_PERMISSION 0000
#define ALL_PERMISSION 0777

int numOfEntries_global;
int numOfEntries_local;



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
int find_node(char *name);
void directory_delete(NODE *directory_node, NODE *home_dir);
void delete_by_name(char *name);
void create_superblock();
void allocate();
int get_free_index();
void assign_to_index_node(NODE *index_node, int memory_index);
void directoryIndex_add(NODE *home_dir, int index);
void free_system();
int find_index_slot(NODE *index_nd, int memory_location);



// bitvector operations
void display_bitvector();
void set_bit(int memory_index);
void clear_bit(int memory_index);
bool test_bit(int memory_index);
void add_to_bitvector(int memory_index);
void remove_from_bitvector(int memory_index);


//--------------------------------Task 2--------------------------------------------------------------------



#define MAX_OPEN_PER_PROCESS 16
#define GLOBAL_TABLE_SIZE  65521 


struct global_node { // elements of the hash table (in-memory "directory")

  unsigned short fd; // reference to the file descriptor node
  unsigned short data_index; // reference to the data or index node (depending on the size)
  unsigned short reference_count;
  mode_t access_rights;
  unsigned short size;
  struct global_node *next; // chaining for collison detection

};

struct local_item { // a node for a local list of open files (per process)

  mode_t access_rights; // access rights for this process
  unsigned short global_ref; // reference to the entry for the file in the global table

};

struct global_item {

  struct global_node *head;
  struct global_node *tail;

};

struct local_item local_table[MAX_OPEN_PER_PROCESS];
struct global_item global_table[GLOBAL_TABLE_SIZE];


//hash functions
void create_tables();
unsigned short hash_code(char *key);
struct global_node* get_item_global(char *key);
void delete_item_global(char *key);
void insert_global(char *key);
void display_table_global();
int find_item(struct global_node *list, char *key);
void global_toPrint(struct global_node *temp);


struct local_item* get_item_local(char *key);
void delete_item_local(char *key);
void insert_local(char *key);
void display_table_local();
int find_emptyLocal();

void open_file(NODE *path, char *file_name, mode_t access_rights);
char* read_file(char *file_name);
void write_file(char *what_to_write,  char *file_name);
void close_file(char *file_name);
int num_of_dataNDs(int num_of_bytes);
void print_data(int dataNodeIndex, int num_of_content);
void append_data(char *des, char src[]);
NODE* data_node_create(bool need_indexNd, NODE* index_node);


#endif