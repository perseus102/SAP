/*  

(c) COPYRIGHT Institute of Systems Science (ISS), Singapore, 1988,1992,1993

Date: September 1993.
Author: Ngair Teow Hin.

Date: May 2012
Modified by: Hendy Chandra
*/
#pragma once
#pragma pack(push, 1)

#ifndef _NTH_HT
#define _NTH_HT

#ifndef _WDMDDK_
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#else
#include <fltKernel.h>
#include <ntstrsafe.h>
#endif
#ifndef NULL
#define NULL    ((void *) 0)
#endif

#ifndef EOF
#define EOF     (-1)
#endif

#ifndef YES
#define YES	1
#endif

#ifndef NO
#define NO	0
#endif

#ifdef DEC			/* equivalent interger size for pointer */
#define pINT   long
#else
#define pINT   unsigned __int64
#endif

#ifdef HALLOC_OPTIMIZE		/* Make halloc functions same as system */
#define htable_insert_alloc_info(p,q) (p)
#define print_alloc_ht()              {}
#define hmalloc       malloc
#define hcalloc       calloc
#define hrealloc(a,b) (a ?  realloc(a, b): malloc(b))
#define hfree         free
#endif

/* Use to specify if the hash value has collided,	*/
/*   and if an entry is already occupied                */
#define COLLIDED         01	/* Collision flag for hash table 	*/
#define OCCUPIED         02	/* Occupied flag for hash table 	*/
#define IN_DISK          04 /* The data is in the disk */
#define MANUAL_FREE_KEY	  8 /* The key need to be manually freed */
#define MANUAL_FREE_DATA 16 /* The data need to be manually freed */
#define IS_WRITING       32 /* In the progress of writing */

#define MANUAL_FREE_KEY_AND_DATA (MANUAL_FREE_KEY | MANUAL_FREE_DATA)
#define SAVED_STATUS_MASK (COLLIDED | OCCUPIED)

/* HT_FLAG? are flags for external use                                  */
/* This feature is likely to go away in the future due to its overhead  */
#define HT_FLAG1       04	/* external flag for hash table 	*/
#define HT_FLAG2       08	/* external flag for hash table 	*/
#define HT_FLAG3       16	/* external flag for hash table 	*/
#define HT_FLAG4       32	/* external flag for hash table 	*/


/* Value for null key and data field*/
#define NULL_KEY_DATA	((unsigned __int64) 0)
#define MAXLENGTH 300		/* the maximun string length allowed when */
				/* reading hash table entries from file   */

//hashtable will be flushed when it meets either MAX_UNFLUSH_WRITE or  MAX_FLUSH_INTERVAL
#ifdef _WDMDDK_
#define MAX_UNFLUSH_WRITE 1000 //Maximum number of unflushed write operation.
#define MAX_FLUSH_INTERVAL 10000000 //1 second
#else
#define MAX_UNFLUSH_WRITE 100000 //Maximum number of unflushed write operation.
#define MAX_FLUSH_INTERVAL 30000000 //3 seconds
#endif

/***************************************************/
/* Data structures used in this hash table library */
/***************************************************/

/* This is the arg type for htable_set_para function. 
   An array of HT_ARGS should be terminated with NULL key */
//key and data is prepared for 64 bit
typedef struct _ht_args {  unsigned __int64 key; unsigned __int64 data; } HT_ARGS;

/* The structure of an entry in the hash table */
typedef struct _entry { unsigned __int64 key, data; char status; } ENTRY;

#define HTABLE_STATE_MERGING  1
#define HTABLE_STATE_MERGED   2
#define HTABLE_STATE_RESIZING 4
#define HTABLE_STATE_FREED    8
#define HTABLE_STATE_WRITING  16
#define HTABLE_STATE_UNLINK   32
#define HTABLE_STATE_FLUSHING 64
#define HTABLE_STATE_CONTENT_FREED 128

#define htable_is_merging(id) (id->info.state & HTABLE_STATE_MERGING)
#define htable_is_merged(id) (id->info.state & HTABLE_STATE_MERGED)
#define htable_is_resizing(id) (id->info.state & HTABLE_STATE_RESIZING)
#define htable_is_freed(id) (id->info.state & HTABLE_STATE_FREED)
#define htable_is_writing(id) (id->info.state & HTABLE_STATE_WRITING)
#define htable_is_unlink(id) (id->info.state & HTABLE_STATE_UNLINK)
#define htable_is_flushing(id) (id->info.state & HTABLE_STATE_FLUSHING)
#define htable_is_content_freed(id) (id->info.state & HTABLE_STATE_CONTENT_FREED)

#ifndef _WDMDDK_
#define PFLT_INSTANCE HINSTANCE
#define PFILE_OBJECT PVOID
#define FAST_MUTEX CRITICAL_SECTION
#define ExInitializeFastMutex InitializeCriticalSection
#define ExAcquireFastMutex EnterCriticalSection
#define ExReleaseFastMutex LeaveCriticalSection
#endif


/* The strucutre of a hash table */
/* =====================================================================
   KEYCPY_FN(key) & DATACPY_FN(data) is the copying functions for 
   key & data fileds respectively. NULL value for these two fields is 
   defaulted to just store the pointer instead of copying.		
		
   HASH_FN (size, key) is the user defined hash function. 
			
	 The function should return a value between 1 and size -1 
	  -- [0 is not allowed !!]  
	 NULL value specified a default (string) hash function is to be used 

   CMP_FN(key1, key2) is the user defined comparison function. 	
	 NULL valuse specified a default comparison function is to be used
======================================================================= */
typedef struct _htable_disk {
  unsigned __int64 SIZE, ENTRIES;
  unsigned short next_id; //if it linked to another hash table. The name of the other hash table has to be filename.ext_next_id, for example: if the next_id is 1, the base filename: data.dat, the next filename will be: data.dat_1
  ENTRY		ht[1];
  //data
} HASH_TABLE_DISK, *PHASH_TABLE_DISK;

typedef struct _ht_info {
  unsigned __int64 SIZE, ENTRIES;
  unsigned short next_id;
  unsigned __int64 entry_start_offset; //entry offset in the file
  unsigned __int64 data_start_offset;  //data offset in the file. In the file, the key and data value are relative to data_start_offset. The absolute offset int the file is something like : key + data_start_offset, or data + data_start_offset
  unsigned __int64 total_data_size;  
  unsigned __int32 number_of_rw; //number of reading and writing
  unsigned __int32 number_of_unflushed_write; //We will start flushing when it reaches MAX_UNFLUSH_WRITE
  unsigned __int64 last_flush_timestamp; //system time tick in nano seconds
  unsigned char state;
  void *data_ptr;
  FAST_MUTEX mutex;
  HANDLE hFile;
  //PFILE_OBJECT  fileObject;
  PFLT_INSTANCE instance;
  const wchar_t *filename;
#ifdef NO_PROTO
  void *(*KEYCPY_FN)(), *(*DATACPY_FN)(); 
  unsigned __int64 (*HASH_FN)(); int (*CMP_FN)();
#else
  void *(*KEYCPY_FN)(void *), *(*DATACPY_FN)(void *); 
  unsigned __int64 (*HASH_FN)(unsigned __int64 size, void *); int (*CMP_FN)(void *, void *);
  //you can decide what to do when the user is inserting the data which the key is already in the hash table
  unsigned __int64 (*ON_INSERT_SAME_KEY)(void *new_item_data, void *old_item_data, BOOLEAN *pbNewEntry, BOOLEAN *pbUpdate); 

  //you can decide whether to delete the entire entry, or just update the entry
  //return the data size. 0 data size means that it requests to delete the entry.
  //To update or delete, *modified has to be set to TRUE by the callback function.
  unsigned __int32 (*ON_DELETE_ITEM)(void *data, void *context, OUT BOOLEAN *modified);
#endif

  //lookup table to check which entry is occupied.
  //if the bit is set to 1, that means the entry is occupied
} HT_INFO;

/* changed on Oct 30, 1992 */
/*
typedef struct _htable {
  HT_INFO	info;		
  ENTRY		*ht;
} *HTABLE, HASH_TABLE;
*/

/* changed on May 28, 2012 (HC)*/
typedef struct _htable {
  HT_INFO	info;		
  ENTRY		*ht;
  BOOLEAN bWriteAccess;
  struct _htable *prev_htable; //To support resize
  struct _htable *next_htable; //To support resize
  struct _htable *active_htable; //where all the write operations should go to. This is usually the last htable in the linked list.
} *HTABLE, HASH_TABLE;

typedef struct {
	unsigned __int32 size; //must be always started with the size of the entry
	unsigned __int32 checksum; //to verify the validity of the entry
} HTABLE_DATA_AND_KEY_HEADER, *PHTABLE_DATA_AND_KEY_HEADER;

/* Actions that the hash_access() function is capable of performing  */
typedef enum _htable_action { FIND, ENTER, REMOVE, UPDATE_ONLY_IF_EXISTS } HTABLE_ACTION;

//#define MAX_PRIME 4294967291 //currently this is the maximum number that we supported (32 bit)
#define MAX_PRIME 18446744073709551557 //this is the maximum prime number for 64 bit

#include "ht_win_io.h"

#ifdef __cplusplus
extern "C" {
#endif

/* API calls that are available in the hash table library */
#ifdef NO_PROTO
extern HTABLE	htable_create();
extern HTABLE	htable_create_o();
extern HTABLE   htable_clone();

extern void 	htable_destroy();
extern void 	htable_set_para();
extern unsigned __int64 	htable_change_size();
extern ENTRY 	*htable_access ();

extern ENTRY 	*htable_intacc ();
extern ENTRY	*htable_find();
extern ENTRY	*htable_remove();
extern ENTRY	*htable_enter();
extern unsigned __int64 	htable_entries();
extern unsigned __int64 	htable_size();
extern char 	**htable_list_array();       
extern unsigned __int64 	htable_list_file ();
extern void 	htable_integer_print_fn();
extern void     htable_str_int_print_fn ();
extern unsigned __int64 	htable_read_file();
extern unsigned __int64 	htable_read_integers();
extern unsigned __int64 	htable_read_phrase();
extern unsigned __int64      htable_read_str_int ();
extern unsigned __int64	htable_map ();
extern unsigned __int64      htable_map_internal ();
extern void 	htable_reset(HTABLE id);
extern void 	htable_free_storage();
extern void 	htable_free_item();
extern int      htable_strcmp();

extern unsigned __int64 htable_compile_write();
extern unsigned __int64 htable_compile_cwrite();
extern HTABLE htable_compile_read ();
extern unsigned __int64 htable_cwrite();
extern HTABLE htable_cread ();
extern unsigned __int64 htable_add_func_index ();

extern unsigned __int64 hfn_int();
extern int cmp_int();
extern char *cpy_str();
extern void *htable_strcpy();
extern unsigned __int64 htable_find_count ();
extern void htable_print_info();
extern HTABLE htable_ratio_clone();

extern void sort_pointer_array();

/* Hash table memory management functions */
#ifndef HALLOC_OPTIMIZE
extern void *htable_insert_alloc_info ();
extern void *hmalloc();
extern void *hcalloc();
extern void *hrealloc();
extern void hfree();
#endif

#else  /* NO_PROTO */
extern HTABLE	htable_create(unsigned __int64 size);
extern HTABLE	htable_create_o(unsigned __int64 size, void *(*keycpy)(void *),
				void *(*datacpy)(void *),
				unsigned __int64 (*hfn) (unsigned __int64 size, void *),
				int (*cfn) (void *, void *));

extern HTABLE   htable_clone(HTABLE id);

extern unsigned __int64	next_prime(unsigned __int64 size);

unsigned __int32 ht_crc32(unsigned __int32 crc, const void *pkey_or_pdata, size_t size);
#define htable_crc32(pkey_or_pdata) ht_crc32(pkey_or_pdata->size, (BYTE*)pkey_or_pdata + sizeof(HTABLE_DATA_AND_KEY_HEADER), pkey_or_pdata->size - sizeof(HTABLE_DATA_AND_KEY_HEADER))

BOOLEAN htable_is_valid_entry(HTABLE table_id, PHTABLE_DATA_AND_KEY_HEADER pHeaderKey, PHTABLE_DATA_AND_KEY_HEADER pHeaderData);

extern void 	htable_destroy(HTABLE table_id);
extern void 	htable_set_para(HTABLE table_id, HT_ARGS *args);
extern unsigned __int64	htable_change_size(register HTABLE id, unsigned __int64 new_size);

void htable_merge_wait_until_thread_done(HTABLE table_id);
BOOLEAN htable_retrieve_from_disk(HTABLE id, unsigned __int64 index);
//Only for single table
//HTABLE htable_win_change_size(register HTABLE id, unsigned __int64 new_size);

//Can handle multiple hashtable chain.
HTABLE htable_win_resize(register HTABLE root_table, BOOLEAN bAutoMerge);

HTABLE htable_win_create_file (BOOLEAN bOverwrite, BOOLEAN bWriteAccess, const wchar_t *filename, unsigned __int64 size, PFLT_INSTANCE instance);
HTABLE htable_win_create (BOOLEAN bOverwrite, BOOLEAN bWriteAccess, const wchar_t *filename, unsigned __int64 size, PFLT_INSTANCE instance);
HTABLE htable_create_memory(unsigned __int64 size);
void htable_set_callback(HTABLE table_id, void *(*keycpy)(void *),
			void *(*datacpy) (void *),
			unsigned __int64 (*hfn) (unsigned __int64 size, void *),
			int (*cfn) (void *, void *),
			unsigned __int64 (*on_insert_same_key)(void *new_item_data, void *old_item_data, BOOLEAN *, BOOLEAN *),
			unsigned __int32 (*on_delete_item)(void *data, void *context, OUT BOOLEAN *modified)
			);
void htable_copy_callback(OUT HTABLE newHT, IN HTABLE id);

extern ENTRY 	*htable_access (HTABLE id, ENTRY *item, HTABLE_ACTION action);

extern ENTRY 	*htable_intacc (HTABLE id, ENTRY *item, HTABLE_ACTION action);
extern ENTRY	*htable_find(HTABLE id, void *key);
extern ENTRY	*htable_remove(HTABLE id, void *key);
extern ENTRY	*htable_enter(HTABLE id, void *key, void *data);
extern unsigned __int64 	htable_entries(HTABLE table_id);
extern unsigned __int64 htable_size(HTABLE table_id);
extern void 	**htable_list_array(HTABLE table_id, unsigned __int64 *size);       
extern unsigned __int64 	htable_list_file (HTABLE id, FILE *fd,
		      void (*print_fn) (FILE *fd, void *key, void *data));
extern void 	htable_integer_print_fn(FILE *fd, void *key, void *data);
extern void     htable_str_int_print_fn (FILE *fd, void *key, void *data);
extern unsigned __int64 	htable_read_file(HTABLE id, FILE *fd,
				 unsigned __int64 (*fn) (char *str, ENTRY *item));
extern int 	htable_read_integers(char *str, ENTRY *item);
extern int 	htable_read_phrase(char *str, ENTRY *item);
extern int      htable_read_str_int (char *str, ENTRY *item);
extern unsigned __int64	htable_map (HTABLE table_id, void (*fn) (void *, void*));
unsigned __int64 htable_safe_map_internal(HTABLE table_id, void (*fn) (ENTRY *e, char *key_ptr, char *data_ptr), char *key_ptr, char *data_ptr, unsigned __int64 filesize);
#define htable_map_internal(table_id, fn, key_ptr, data_ptr) htable_safe_map_internal(table_id, fn, key_ptr, data_ptr, 0xffffffffffffffff)

//unsigned __int64 htable_map_internal (HTABLE table_id, void (*fn) (ENTRY *e, char *key_ptr, char *data_ptr), char *key_ptr, char *data_ptr, unsigned __int64 filesize);
extern unsigned __int64 htable_map_to_disk (HTABLE table_id);
extern void 	htable_reset(HTABLE id);
extern void 	htable_free_storage(HTABLE id, unsigned __int64 free_keyp, unsigned __int64 free_datap);
extern void 	htable_free_item(ENTRY *item, int free_keyp, int free_datap);

extern unsigned __int64 htable_compile_write(HTABLE oid, FILE *fd, int (*key_len)(void *s),
				int (*data_len)(void *s),
				void (*key_cpy)(void *dest, void *src), 
				void (*data_cpy)(void *dest, void *src),
				char *comment);
extern unsigned __int64 htable_compile_cwrite(HTABLE oid, FILE *fd, int (*key_len)(void *s),
				 int (*data_len)(void *s),
				 void (*key_cpy)(void *dest, void *src), 
				 void (*data_cpy)(void *dest, void *src),
				 char *comment);

void htable_merge_all(HTABLE table_id);

#ifdef WIN32
//(HC)
extern unsigned __int64 htable_compile_win_cwrite(HTABLE oid, HANDLE hFile, 
					unsigned __int32 (*key_len)(void *s), 
				   unsigned __int32 (*data_len)(void *s),
				   void (*key_cpy)(void *dest, void *src), 
				   void (*data_cpy)(void *dest, void *src),
				   char *comment);
#endif

extern HTABLE htable_compile_read (FILE *fd, char **comment);

#ifdef WIN32
//(HC)
extern HTABLE htable_compile_win_read (HANDLE hFile, OPTIONAL char **comment);
#endif

unsigned __int32 htable_datalen(void *data);
unsigned __int32 htable_keylen(void *key);
void htable_datacpy(void *dest, void *src);
void htable_keycpy(void *dest, void *src);

extern unsigned __int64 htable_cwrite(HTABLE oid, FILE *fd, unsigned __int64 (*key_len)(void *s),
			 unsigned __int64 (*data_len)(void *s),
			 void (*key_cpy)(void *dest, void *src), 
			 void (*data_cpy)(void *dest, void *src),
			 char *comment);

extern HTABLE htable_cread (FILE *fd, char **comment);

extern unsigned __int64 htable_add_func_index (unsigned __int64 index, void (*func)());

extern unsigned __int64 hfn_int(unsigned __int64 size, void *n);
extern int cmp_int(void *ptr1, void *ptr2);
extern void *htable_strcpy(void *str);
extern unsigned __int64 htable_find_count (HTABLE id, void *key);
extern void htable_print_info(HTABLE id);
extern HTABLE htable_ratio_clone(HTABLE id, float ratio);

extern void sort_pointer_array();

/* Hash table memory management functions */
#ifndef HALLOC_OPTIMIZE
extern void *htable_insert_alloc_info (void *m, size_t size);
extern void *hmalloc(size_t size);
extern void *hcalloc(size_t nobj, size_t size);
extern void *hrealloc(void *p, size_t size);
extern void hfree(void *p);

//close single handle
void _htable_win_close_handle(HTABLE table_id);
//close multiple handles
void htable_win_close_handle(HTABLE table_id);

BOOLEAN delete_and_close_htable_file(HTABLE table_id);

void htable_free_key_and_data(HTABLE id, BOOLEAN free_keyp, BOOLEAN free_datap);

void _htable_free_content(HTABLE table_id);
HANDLE _htable_delay_free(HTABLE table_id, unsigned long dealy_in_ms);

//free single table
void _htable_free(HTABLE table_id);
//Free multiple hashtables
void htable_free(HTABLE table_id);
void htable_free_key(ENTRY *e);
void htable_free_data(ENTRY *e);
void htable_free_in_thread(HTABLE table_id);
void htable_free_wait_until_thread_done();

#endif
#endif /* NO_PROTO */

//Comapct hashtable
HTABLE htable_win_compact(register HTABLE *in_out_root_table, BOOLEAN bAutoMerge);

#ifdef __cplusplus
}  /* end of the 'extern "C"' block */
#endif

/* Second hash function (changed to a macro on Oct 30, 1992) */
#define nextindex(size, first_index, index) \
  (first_index + index) % size


/*********************************************************************/
/* Externally modifiable variables to control the global behavior    */
/* of the hash tables                                                */
/*********************************************************************/

/* Make sure that htable_resize_ratio is >= htable_min_resize_ratio  */
/* Automatic resize SIZE : ENTRIES ratio                             */
//extern float	htable_resize_ratio;
extern unsigned __int64	htable_resize_ratio_x10;

/* Minimum resize NEW-SIZE : ENTRIES ratio */
//extern float	htable_min_resize_ratio;
extern unsigned __int64	htable_min_resize_ratio_x10;

#endif	/* _NTH_HT */

#pragma pack(pop)