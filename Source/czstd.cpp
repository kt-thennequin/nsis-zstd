/*
 * czstd.cpp
 * 
 * This file is a part of NSIS.
 * 
 * Copyright (C) 1999-2009 Nullsoft and Contributors
 * 
 * Licensed under the zlib/libpng license (the "License");
 * you may not use this file except in compliance with the License.
 * 
 * Licence details can be found in the file COPYING.
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty.
 *
 * Unicode support by Jim Park -- 08/24/2007
 */

#include <algorithm> // for std::min
#include "czstd.h"

using namespace std;


CZSTD::CZSTD()
{
    pContext = ZSTD_createCCtx();
    SetNextOut(NULL, 0);
    SetNextIn(NULL, 0);
}

CZSTD::~CZSTD()
{
  End();

  ZSTD_freeCCtx( pContext );
}

int CZSTD::Init(int level, unsigned int dicSize)
{
  End();

  //int zstdLevel = (level - 0) * (ZSTD_maxCLevel() - ZSTD_minCLevel()) / 9 + ZSTD_minCLevel();
  ZSTD_CCtx_reset(pContext, ZSTD_reset_session_only);
  //ZSTD_CCtx_setParameter(pContext, ZSTD_c_compressionLevel, level);
  ZSTD_CCtx_setParameter(pContext, ZSTD_c_nbWorkers, 8);

  return C_OK;
}

int CZSTD::End()
{
  SetNextOut(NULL, 0);
  SetNextIn(NULL, 0);
  return C_OK;
}

int CZSTD::Compress(bool flush)
{
    ZSTD_outBuffer outbuffer;
    outbuffer.dst = next_out;
    outbuffer.size = avail_out;
    outbuffer.pos = 0;

    ZSTD_inBuffer inbuffer;
    inbuffer.src = next_in;
    inbuffer.size = avail_in;
    inbuffer.pos = 0;

    size_t iRet = ZSTD_compressStream2( pContext, &outbuffer , &inbuffer, flush ? ZSTD_e_flush : ZSTD_e_continue );
    if( ZSTD_isError( iRet ) )
    {
        return -1;
    }

    avail_in = inbuffer.size - inbuffer.pos;
    avail_out = outbuffer.size - outbuffer.pos;
    return iRet == 0 ? C_FINISHED : C_OK;
}

void CZSTD::SetNextIn(char *in, unsigned int size)
{
  next_in = (LPBYTE) in;
  avail_in = size;
}

void CZSTD::SetNextOut(char *out, unsigned int size)
{
  next_out = (LPBYTE) out;
  avail_out = size;
}

char* CZSTD::GetNextOut()
{
  return (char *) next_out;
}

unsigned int CZSTD::GetAvailIn()
{
  return avail_in;
}

unsigned int CZSTD::GetAvailOut()
{
  return avail_out;
}

const TCHAR* CZSTD::GetName()
{
  return _T("zstd");
}

const TCHAR* CZSTD::GetErrStr(int err)
{
  switch (err)
  {
  default:
    return _T("unknown error");
  }
}
