/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:30:26 by yyatsenk          #+#    #+#             */
/*   Updated: 2019/06/17 12:30:27 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
#define SSL_H
#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <fcntl.h>

#define SHA256_BLOCK_SIZE 32

#define PRINT_HASH(buf)   \
{\
    int i = 0;                      \
    while(i < 32)               \
    {                           \
        printf("%2.2x", buf[i]);    \
        i++;                        \
    }  \
}\

#define PRINT_ALGO_STR(algo, str, hash)         \
if (!ft_strcmp(algo, "SHA256"))                 \
{                                               \
    printf("%s (\"%s\") =", algo, str);         \
    PRINT_HASH(hash);                           \
    printf("\n");                                \
}                                               \
else                                             \
    printf("%s (\"%s\") = %s\n", algo, str, hash); \



#define PRINT_ALGO_FILE(algo, filename, hash)         \
if (!ft_strcmp(algo, "SHA256"))                 \
{                                               \
    printf("%s (\"%s\") = ", algo, filename);         \
    PRINT_HASH(hash);                           \
    printf("\n");                                \
}                                               \
else                                             \
    printf("%s (%s) = %s\n", algo, filename, hash); \



#define PRINT_STR_REV(algo, str, hash)         \
if (!ft_strcmp(algo, "SHA256"))                 \
{                                                        \
    PRINT_HASH(hash);                           \
    printf(" \"%s\"\n", str);                                \
}                                               \
else                                             \
    printf("%s \"%s\"\n", hash, str); \




#define PRINT_FILE_REV(algo, filename, hash)         \
if (!ft_strcmp(algo, "SHA256"))                 \
{        \
    PRINT_HASH(hash);                                                                  \
    printf(" %s\n", filename); \
}                                               \
else                                             \
    printf("%s %s\n", hash, filename); \

//#define PRINT_ALGO_FILE(algo, filename, hash)   printf("%s (%s) = %s\n", algo, filename, hash)
//#define PRINT_STR_REV(str, hash)                printf("%s \"%s\"\n", hash, str)
//#define PRINT_FILE_REV(filename, hash)          printf("%s %s\n", hash, filename)
                             

typedef unsigned char BYTE;  
typedef unsigned int  WORD;

uint32_t r5[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    uint32_t k5[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

typedef struct  s_flags
{
    unsigned p;
    unsigned q;
    unsigned r;
    unsigned s;
    char *filename;
    char *str;
    short algo; // 0 - md5, 1 - sh256
}               t_flags;

typedef struct  s_abcd
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
}               t_abcd;

typedef struct  s_mda5
{
	uint32_t h0;
    uint32_t h1;
    uint32_t h2;
    uint32_t h3;
    t_flags flags;
}               t_mda5;

typedef struct  s_abcd256
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
}               t_abcd256;

typedef struct  s_sha256
{
	unsigned char data[64];
	unsigned int datalen;
	unsigned long long bitlen;
	unsigned int state[8];
    t_abcd256 abcd256;
    t_flags flags;
}               t_sha256;

#define ROT_LEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROT_RIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROT_RIGHT(x,2) ^ ROT_RIGHT(x,13) ^ ROT_RIGHT(x,22))
#define EP1(x) (ROT_RIGHT(x,6) ^ ROT_RIGHT(x,11) ^ ROT_RIGHT(x,25))
#define SIG0(x) (ROT_RIGHT(x,7) ^ ROT_RIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROT_RIGHT(x,17) ^ ROT_RIGHT(x,19) ^ ((x) >> 10))

void sha256_create(t_sha256 *ctx);
void sha256_update(t_sha256 *ctx, const BYTE data[], size_t len);
void sha256_res(t_sha256 *ctx, BYTE hash[]);


#endif


