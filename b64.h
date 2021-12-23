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

char *b64Encode(char *data)
{
    static const char b64e[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'};

    ssize_t inlen = strlen(data);
    ssize_t outlen = B64_LEN(inlen);

    char *out = malloc(outlen + 1);
    if (out == NULL) return NULL;
    out[outlen] = '\0';
    char *p = out;

    ssize_t i;
    for (i = 0; i < inlen - 2; i += 3)
    {
        *p++ = b64e[(data[i] >> 2) & 0x3F];
        *p++ = b64e[((data[i] & 0x3) << 4) | ((data[i + 1] & 0xF0) >> 4)];
        *p++ = b64e[((data[i + 1] & 0xF) << 2) | ((data[i + 2] & 0xC0) >> 6)];
        *p++ = b64e[data[i + 2] & 0x3F];
    }

    if (i < inlen)
    {
        *p++ = b64e[(data[i] >> 2) & 0x3F];
        if (i == (inlen - 1))
        {
            *p++ = b64e[((data[i] & 0x3) << 4)];
            *p++ = '=';
        }
        else
        {
            *p++ = b64e[((data[i] & 0x3) << 4) | ((data[i + 1] & 0xF0) >> 4)];
            *p++ = b64e[((data[i + 1] & 0xF) << 2)];
        }
        *p++ = '=';
    }

    return out;
}

char *b64Decode(char *data)
{
    static const char b64d[] = {
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
        64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
        64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64};

    ssize_t inlen = strlen(data);
    if (inlen == 0 || inlen % 4) return NULL;
    ssize_t outlen = B64_REV(inlen);

    if (data[inlen - 1] == '=') outlen--;
    if (data[inlen - 2] == '=') outlen--;

    char *out = malloc(outlen + 1);
    if (out == NULL) return NULL;
    out[outlen] = '\0';
    char *p = out;

    typedef unsigned int u32;
    for (ssize_t i = 0, j = 0; i < inlen;)
    {
        u32 a = data[i] == '=' ? 0 & i++ : b64d[(data[i++])];
        u32 b = data[i] == '=' ? 0 & i++ : b64d[(data[i++])];
        u32 c = data[i] == '=' ? 0 & i++ : b64d[(data[i++])];
        u32 d = data[i] == '=' ? 0 & i++ : b64d[(data[i++])];

        u32 triple = (a << 3 * 6) + (b << 2 * 6) +
                          (c << 1 * 6) + (d << 0 * 6);

        if (j < outlen) out[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < outlen) out[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < outlen) out[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return out;
}

#endif
