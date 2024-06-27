#ifndef __ZSTDSTREAM_H__
#define __ZSTDSTREAM_H__

#include "../zstd/zstd.h"
#include <stdint.h>

struct zstd_stream_s
{
    /* io */
    unsigned char* next_in;    /* next input byte */
    unsigned int avail_in;  /* number of bytes available at next_in */

    unsigned char* next_out;   /* next output byte should be put there */
    unsigned int avail_out; /* remaining free space at next_out */

    ZSTD_DCtx* pContext;
};
typedef struct zstd_stream_s zstd_stream;

int zstd_stream_init(zstd_stream* pStream);
int zstd_stream_reset(zstd_stream* pStream);
int zstd_stream_decode(zstd_stream* pStream);

#endif //__ZSTDSTREAM_H__