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
#define GLOBAL_TABLE_SIZE  1000 //65521 

typedef struct global_item GLOBAL_ITEM;
typedef struct local_item LOCAL_ITEM;

struct global_item{ // elements of the hash table (in-memory "directory")

   unsigned short fd; // reference to the file descriptor node
   unsigned short data_index; // reference to the data or index node (depending on the size)
   unsigned short reference_count; 
   mode_t access_rights;
   unsigned short size; 
   GLOBAL_ITEM *next; // chaining for collison detection

};

struct local_item{ // a node for a local list of open files (per process)

   mode_t access_rights; // access rights for this process
   unsigned short global_ref; // reference to the entry for the file in the global table

};

LOCAL_ITEM local_table[MAX_OPEN_PER_PROCESS];
GLOBAL_ITEM global_table[GLOBAL_TABLE_SIZE];


/*

   Comments / Questions / Things to keep in mind:

    1. SO, I have two data items and i need to make two tables for each.
       (a). Use function pointers for the the fuctions to make them usable
       in both tables.
       (b). Use a switching function to handle the diffrent types.
       (c). Combination of both.
       (d). return void pointers. This involves checking the data type inside the
        the functions.


   
   2. How will I intergrate this into opening, closing, reading, writing? 

   3. File size using a data node or index node is now  important. Figure out a way to 
      fit this in.


   4. What role does the loca_item play (unsigned short global_ref) overall? 

   You should distribute the information between the two tables; for example, 
   the main table can keep the information about the location of the file, 
   and the tables local to processes can keep specifics such as the access rights. 

   5. It's posiable that we can't use the the same functions for both table beacause the 
      global table use chaining while the local does not.

      Different insert funtions for global and local? And maybe a switching funtion on the types?



*/

/*

   key = file name (string)

   value = ITEM (global or local)

*/

// http://www.partow.net/programming/hashfunctions/#SDBMHashFunction 


//hash functions   
void create_tables();
unsigned short hash_code(char *key);
GLOBAL_ITEM* get_item_global(char *key);
void delete_item_global(char *key);
void insert_global(char *key);
void display_table_global();

bool contains(char *name);

LOCAL_ITEM* get_item_local(char *key);
void delete_item_local(char *key);
void insert_local(char *key);
void display_table_local();
int find_emptyLocal();

void open(char *file);
void read_file(char *file);
void write(char *file);
void close_file(char *file);

// bool is_type( void* item);


 /*
   
   open(file, (open type read or write) )

   When you open a file, you can use a system default for 
   allocating some predefined space; or, you can just allocate 
   the file descriptor node and postpone allocating more when a 
   write is requested.When file grows, you can have another configuration 
   option that states by how much the file should grow. 

   directories are just special files, so they can be opened in the same way.
   You do not have to implement caching.


 */

/*

    close( file )

   Be careful with processes calling close() function. 
   If another process has the same file opened, you cannot 
   remove the FCB from the global open file table; hence you
   need a reference count. 

*/

/*

   read( file )

   check the access rights.

   Recall that when a file is read, then frequently used elements 
   of it's file control block are loaded into the main memory 
   to improve efficiency. 

   Usually there is a table of all open files, and a table of 
   files opened by a specifc process

*/

/*

   write( file )

   check the access rights.

   The write() function has to check the mode of the opened file, 
   so read-only files are not overwritten.


*/




#endif   