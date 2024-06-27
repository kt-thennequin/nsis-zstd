/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under both the BSD-style license (found in the
 * LICENSE file in the root directory of this source tree) and the GPLv2 (found
 * in the COPYING file in the root directory of this source tree).
 * You may select, at your option, one of the above-listed licenses.
 */

/* This file provides common libc dependencies that zstd requires.
 * The purpose is to allow replacing this file with a custom implementation
 * to compile zstd without libc support.
 */

/* Need:
 * NULL
 * INT_MAX
 * UINT_MAX
 * ZSTD_memcpy()
 * ZSTD_memset()
 * ZSTD_memmove()
 */
#ifndef ZSTD_DEPS_COMMON
#define ZSTD_DEPS_COMMON

#include <limits.h>
#include <stddef.h>
#include <string.h>

#if defined(__GNUC__) && __GNUC__ >= 4
# define ZSTD_memcpy(d,s,l) __builtin_memcpy((d),(s),(l))
# define ZSTD_memmove(d,s,l) __builtin_memmove((d),(s),(l))
# define ZSTD_memset(p,v,l) __builtin_memset((p),(v),(l))
#else
# define ZSTD_memcpy(d,s,l) memcpy((d),(s),(l))
# define ZSTD_memmove(d,s,l) memmove((d),(s),(l))
# define ZSTD_memset(p,v,l) memset((p),(v),(l))

inline void mini_memcpy(void *out, const void *in, unsigned long len)
{
  char *c_out=(char*)out;
  char *c_in=(char *)in;
  while (len-- > 0)
  {
    *c_out++=*c_in++;
  }
}

inline void mini_memset(void *out, int val, unsigned long len)
{
  char *c_out=(char*)out;
  while (len-- > 0)
  {
    *c_out++=val;
  }
}

inline void *mini_memmove(void *dest, const void *src, unsigned long n)
{
   char *cdest;
   char *csrc;   cdest = (char *)dest;
   csrc = (char *)src;

    //If the destination point in memory (dest) is before/less than the source block of memory (src), the copy will work as expected. Even if the copied bytes overlaps the beginning of the src block, that specific data has already been copied to the dest block (image 1).

    if (dest <= src)
   {
      while(n--)
      {
        *cdest++ = *csrc++;
      }
   }
   else if (dest > src)
   {
      cdest += n - 1;
      csrc += n - 1;
      while(n--)
      {
         *cdest-- = *csrc--;
      }
   }
   return (dest);
}

// # define ZSTD_memcpy(d,s,l) mini_memcpy((d),(s),(l))
// # define ZSTD_memmove(d,s,l) mini_memmove((d),(s),(l))
// # define ZSTD_memset(p,v,l) mini_memset((p),(v),(l))
#endif

#endif /* ZSTD_DEPS_COMMON */

/* Need:
 * ZSTD_malloc()
 * ZSTD_free()
 * ZSTD_calloc()
 */
#ifdef ZSTD_DEPS_NEED_MALLOC
#ifndef ZSTD_DEPS_MALLOC
#define ZSTD_DEPS_MALLOC

#include <stdlib.h>

#define ZSTD_malloc(s) malloc(s)
#define ZSTD_calloc(n,s) calloc((n), (s))
#define ZSTD_free(p) free((p))

#endif /* ZSTD_DEPS_MALLOC */
#endif /* ZSTD_DEPS_NEED_MALLOC */

/*
 * Provides 64-bit math support.
 * Need:
 * U64 ZSTD_div64(U64 dividend, U32 divisor)
 */
#ifdef ZSTD_DEPS_NEED_MATH64
#ifndef ZSTD_DEPS_MATH64
#define ZSTD_DEPS_MATH64

#define ZSTD_div64(dividend, divisor) ((dividend) / (divisor))

#endif /* ZSTD_DEPS_MATH64 */
#endif /* ZSTD_DEPS_NEED_MATH64 */

/* Need:
 * assert()
 */
#ifdef ZSTD_DEPS_NEED_ASSERT
#ifndef ZSTD_DEPS_ASSERT
#define ZSTD_DEPS_ASSERT

#include <assert.h>

#endif /* ZSTD_DEPS_ASSERT */
#endif /* ZSTD_DEPS_NEED_ASSERT */

/* Need:
 * ZSTD_DEBUG_PRINT()
 */
#ifdef ZSTD_DEPS_NEED_IO
#ifndef ZSTD_DEPS_IO
#define ZSTD_DEPS_IO

#include <stdio.h>
#define ZSTD_DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__)

#endif /* ZSTD_DEPS_IO */
#endif /* ZSTD_DEPS_NEED_IO */

/* Only requested when <stdint.h> is known to be present.
 * Need:
 * intptr_t
 */
#ifdef ZSTD_DEPS_NEED_STDINT
#ifndef ZSTD_DEPS_STDINT
#define ZSTD_DEPS_STDINT

#include <stdint.h>

#endif /* ZSTD_DEPS_STDINT */
#endif /* ZSTD_DEPS_NEED_STDINT */
