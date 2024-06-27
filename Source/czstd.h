/*
 * clzma.h
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

#ifndef __CZSTD_H__
#define __CZSTD_H__

#include "Platform.h"

#ifndef _WIN32
# include <pthread.h>
#endif

#include "compressor.h"
#include "zstd/zstd.h"

class CZSTD:
  public ICompressor
{
private:
 
  BYTE *next_in; /* next input byte */
  UINT avail_in; /* number of bytes available at next_in */

  BYTE *next_out; /* next output byte should be put there */
  UINT avail_out; /* remaining free space at next_out */

  ZSTD_CCtx* pContext;

public:

  CZSTD();
  virtual ~CZSTD();

  virtual int Init(int level, unsigned int dicSize);
  virtual int End();
  virtual int Compress(bool flush);

  virtual void SetNextIn(char *in, unsigned int size);
  virtual void SetNextOut(char *out, unsigned int size);

  virtual char *GetNextOut();
  virtual unsigned int GetAvailIn();
  virtual unsigned int GetAvailOut();
  virtual const TCHAR *GetName();

  virtual const TCHAR* GetErrStr(int err);
};

#endif
