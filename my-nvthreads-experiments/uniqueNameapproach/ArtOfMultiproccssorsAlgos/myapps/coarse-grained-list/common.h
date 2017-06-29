#ifndef __COMMON_H__
#define __COMMON_H__

typedef bool bool_t;
typedef int lkey_t;
typedef int  val_t;

#define DETAIL_DBG 1

#define elog(_message_)  do {fprintf(stderr,			        \
				     "%s():%s:%u: %s\n",		\
				     __FUNCTION__, __FILE__, __LINE__,	\
				     _message_); fflush(stderr);}while(0);

#endif
