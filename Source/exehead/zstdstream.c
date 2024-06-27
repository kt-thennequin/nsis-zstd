#include "zstdstream.h"
#include <stdlib.h>

int zstd_stream_init(zstd_stream* pStream)
{
    return 0;
}

int zstd_stream_reset(zstd_stream* pStream)
{
    if (pStream->pContext == NULL)
    {
        pStream->pContext = ZSTD_createDCtx();
        // TODO delete context ?
    }

    ZSTD_DCtx_reset(pStream->pContext, ZSTD_reset_session_only);

    return 0;
}


int zstd_stream_decode(zstd_stream* pStream)
{
    ZSTD_outBuffer outbuffer;
    outbuffer.dst = pStream->next_out;
    outbuffer.size = pStream->avail_out;
    outbuffer.pos = 0;

    ZSTD_inBuffer inbuffer;
    inbuffer.src = pStream->next_in;
    inbuffer.size = pStream->avail_in;
    inbuffer.pos = 0;

    size_t iDecomp = ZSTD_decompressStream(pStream->pContext, &outbuffer, &inbuffer);
    if (ZSTD_isError(iDecomp))
    {
        return -1;
    }
    else if (iDecomp == 0)
    {
        return 1;
    }
    pStream->next_out += outbuffer.pos;
    pStream->next_in += inbuffer.pos;
    pStream->avail_out -= outbuffer.pos;
    pStream->avail_in -= inbuffer.pos;
    return 0;
}
