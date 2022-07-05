#ifndef _B64_H_
#define _B64_H_

/*
 * Unlicensed :)
 * C++ implementation was ripped from tomykaira's gist
 * https://gist.github.com/tomykaira/f0fd86b6c73063283afe550bc5d77594
 *
 * written by skullchap
 * https://github.com/skullchap/b64
 */

#include "stdlib.h"
#include "string.h"

#define B64_LEN(inlen) ((((inlen) + 2) / 3) * 4)
#define B64_REV(inlen) (((inlen) / 4) * 3)

/* b64Encode - encodes an array of bytes to base64
 * Inputs:
 * - dst : the destination array (if it's NULL, the function will allocate the
 * buffer)
 * - src : the source array
 * - srclen : the length of the source array
 * Safety:
 * if dst is not NULL, then it must point to an array that has the size of at
 * least ((srclen + 2) / 3 * 4)
 */
char *b64Encode(char *dst, char *src, size_t srclen) {
  static const char b64e[] = {
      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

  size_t i;
  char *p;
  size_t inlen = srclen;
  size_t outlen = B64_LEN(inlen);

  if (!dst) {
    dst = malloc(outlen + 1);
    /* malloc failed so return early */
    if (!dst) {
      return NULL;
    }
  }
  dst[outlen] = '\0';
  p = dst;

  for (i = 0; i < inlen - 2; i += 3) {
    *p++ = b64e[(src[i] >> 2) & 0x3F];
    *p++ = b64e[((src[i] & 0x3) << 4) | ((src[i + 1] & 0xF0) >> 4)];
    *p++ = b64e[((src[i + 1] & 0xF) << 2) | ((src[i + 2] & 0xC0) >> 6)];
    *p++ = b64e[src[i + 2] & 0x3F];
  }

  if (i < inlen) {
    *p++ = b64e[(src[i] >> 2) & 0x3F];
    if (i == (inlen - 1)) {
      *p++ = b64e[((src[i] & 0x3) << 4)];
      *p++ = '=';
    } else {
      *p++ = b64e[((src[i] & 0x3) << 4) | ((src[i + 1] & 0xF0) >> 4)];
      *p++ = b64e[((src[i + 1] & 0xF) << 2)];
    }
    *p++ = '=';
  }

  return dst;
}

/* b64Decode - decodes an array of bytes from base64
 * Inputs:
 * - dst : the destination array (if it's NULL, the function will allocate the
 * buffer)
 * - src : the source array
 * - srclen : the length of the source array
 * Safety:
 * if dst is not NULL, then it must point to an array that has the size of at
 * least (srclen / 4 * 3)
 */
char *b64Decode(char *dst, char *src, char srclen) {
  static const char b64d[] = {
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63, 52, 53, 54, 55, 56, 57,
      58, 59, 60, 61, 64, 64, 64, 64, 64, 64, 64, 0,  1,  2,  3,  4,  5,  6,
      7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
      25, 64, 64, 64, 64, 64, 64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64};
  size_t i, j;
  size_t inlen = srclen;
  size_t outlen = B64_REV(inlen);

  if (inlen == 0 || inlen % 4)
    return NULL;
  if (src[inlen - 1] == '=')
    outlen--;
  if (src[inlen - 2] == '=')
    outlen--;

  if (!dst) {
    dst = malloc(outlen + 1);
    /* malloc failed so return early */
    if (!dst)
      return NULL;
  }
  dst[outlen] = '\0';

  for (i = 0, j = 0; i < inlen;) {
    unsigned int a = src[i] == '=' ? 0 & i++ : b64d[(src[i++])];
    unsigned int b = src[i] == '=' ? 0 & i++ : b64d[(src[i++])];
    unsigned int c = src[i] == '=' ? 0 & i++ : b64d[(src[i++])];
    unsigned int d = src[i] == '=' ? 0 & i++ : b64d[(src[i++])];

    unsigned int triple =
        (a << 3 * 6) + (b << 2 * 6) + (c << 1 * 6) + (d << 0 * 6);

    if (j < outlen)
      dst[j++] = (triple >> 2 * 8) & 0xFF;
    if (j < outlen)
      dst[j++] = (triple >> 1 * 8) & 0xFF;
    if (j < outlen)
      dst[j++] = (triple >> 0 * 8) & 0xFF;
  }

  return dst;
}

#endif
