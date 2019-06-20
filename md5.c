/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:29:56 by yyatsenk          #+#    #+#             */
/*   Updated: 2019/06/17 12:29:58 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static uint32_t r5[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
					5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
					4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
					6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static uint32_t k5[] = {
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

static void		md5_help_3(t_abcd *abcd, uint32_t *f, uint32_t *g, int i)
{
	if (i < 16)
	{
		*f = (abcd->b & abcd->c) | ((~abcd->b) & abcd->d);
		*g = i;
	}
	else if (i < 32)
	{
		*f = (abcd->d & abcd->b) | ((~abcd->d) & abcd->c);
		*g = (5*i + 1) % 16;
	}
	else if (i < 48)
	{
		*f = abcd->b ^ abcd->c ^ abcd->d;
		*g = (3*i + 5) % 16;          
	}
	else 
	{
		*f = abcd->c ^ (abcd->b | (~abcd->d));
		*g = (7*i) % 16;
	}
}

static void		md5_help_2(t_abcd *abcd, uint32_t *w) 
{
	uint32_t	temp;
	int			i;
	uint32_t	f;
	uint32_t	g;

	i = -1;
	while (++i<64)
	{
		md5_help_3(abcd, &f, &g, i);
		temp = abcd->d;
		abcd->d = abcd->c;
		abcd->c = abcd->b;
		abcd->b = abcd->b + LEFTROTATE((abcd->a + f + k5[i] + w[g]), r5[i]);
		abcd->a = temp;
	}
}

static void		md5_help(t_mda5 *md5, int new_len, uint8_t *msg) 
{
	int			offset;
	uint32_t	*w;

	offset = 0;
	while (offset < new_len)
	{
		w = (uint32_t *) (msg + offset);
		t_abcd abcd;
		abcd.a = md5->h0;
		abcd.b = md5->h1;
		abcd.c = md5->h2;
		abcd.d = md5->h3;
		md5_help_2(&abcd, w);
		md5->h0 += abcd.a;
		md5->h1 += abcd.b;
		md5->h2 += abcd.c;
		md5->h3 += abcd.d;
		offset += (512/8);
	}
}
 
void			md5(uint8_t *initial_msg, size_t initial_len, t_mda5 *md5)
{
	uint8_t		*msg;
	int			new_len;
	uint32_t	bits_len;

	md5->h0 = 0x67452301;
	md5->h1 = 0xefcdab89;
	md5->h2 = 0x98badcfe;
	md5->h3 = 0x10325476;
	new_len = initial_len * 8 + 1;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
	msg = calloc(new_len + 64, 1); 
	ft_memcpy(msg, initial_msg, initial_len);
	msg[initial_len] = 128;
	bits_len = 8*initial_len;
	ft_memcpy(msg + new_len, &bits_len, 4); 
	md5_help(md5, new_len, msg);
	free(msg);
}