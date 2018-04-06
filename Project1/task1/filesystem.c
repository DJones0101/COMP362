/*
* Darius Jones
* Project 1 task 1
* 4/5/2018
*/

#define BLOCK_SIZE 256
#define MAX_NAME_LENGTH 128
#define DATA_SIZE 254
#define INDEX_SIZE 127

typedef char data_t;
typedef unsigned short index_t;

typedef enum
{
   DIR,
   FILE,
   INDEX,
   DATA
} NODE_TYPE;

typedef struct fs_node
{
   char name[MAX_NAME_LENGTH];
   time_t creation; 
   time_t last_access 
   time_t last_modification; 
   mode_t access_rights; 
   unsigned short owner_id; 
   unsigned short size;
   index_t block_ref;
} FS_NODE;

typedef struct node
{
   NODE_TYPE type;
   union
   {
      FS_NODE file_desc;
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

