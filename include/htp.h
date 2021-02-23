#ifndef _NTH_HTP
#define _NTH_HTP

#include "ht.h"

/* Structure used by compiled hash table */
typedef struct _ht_compile_info {
  int comment_len;  char *comment;
  unsigned __int64 key_len,  data_len;
  char *key_ptr, *data_ptr;
} HT_COMPILE_INFO;

typedef struct _ht_new_compile_info {
  unsigned __int64 byte_order;
  unsigned __int64 version;
  char pointer_size, int_size, long_size, short_size;
  unsigned __int64 comment_len;  char *comment;
  unsigned __int64   key_len,  data_len;
  char *key_ptr, *data_ptr;
} HT_NEW_COMPILE_INFO;


#endif /*_NTH_HTP */
