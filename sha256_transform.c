/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:29:56 by yyatsenk          #+#    #+#             */
/*   Updated: 2019/06/17 12:29:58 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static const unsigned int k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

static void			sha256_transform_help_3(t_sha256 *ctx, t_abcd256 abcd256)
{
	ctx->state[0] += abcd256.a;
	ctx->state[1] += abcd256.b;
	ctx->state[2] += abcd256.c;
	ctx->state[3] += abcd256.d;
	ctx->state[4] += abcd256.e;
	ctx->state[5] += abcd256.f;
	ctx->state[6] += abcd256.g;
	ctx->state[7] += abcd256.h;
}

static void			sha256_transform_help(t_sha256 *ctx, const unsigned char data[], t_abcd256 abcd256, unsigned int m[64])
{
	unsigned int	t1;
	unsigned int	t2;
	int i;

	i = -1;
	while(++i < 64)
	{
		t1 = abcd256.h + EP1(abcd256.e) + CH(abcd256.e,abcd256.f,abcd256.g) + k[i] + m[i];
		t2 = EP0(abcd256.a) + MAJ(abcd256.a, abcd256.b, abcd256.c);
		abcd256.h = abcd256.g;
		abcd256.g = abcd256.f;
		abcd256.f = abcd256.e;
		abcd256.e = abcd256.d + t1;
		abcd256.d = abcd256.c;
		abcd256.c = abcd256.b;
		abcd256.b = abcd256.a;
		abcd256.a = t1 + t2;
	}
	sha256_transform_help_3(ctx, abcd256);
}

static void			sha256_transform_help_2(unsigned int *m, const unsigned char data[])
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		m[i] = (data[j] << 24) | (data[j + 1] << 16)\
		| (data[j + 2] << 8) | (data[j + 3]);
		i++;
		j += 4;
	}
	while(i < 64)
	{
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
		i++;
	}
}

void				sha256_transform(t_sha256 *ctx, const unsigned char data[])
{
	unsigned int	m[64];
	t_abcd256		abcd256;

	sha256_transform_help_2(m, data);
	abcd256.a = ctx->state[0];
	abcd256.b = ctx->state[1];
	abcd256.c = ctx->state[2];
	abcd256.d = ctx->state[3];
	abcd256.e = ctx->state[4];
	abcd256.f = ctx->state[5];
	abcd256.g = ctx->state[6];
	abcd256.h = ctx->state[7];
	sha256_transform_help(ctx, data, abcd256, m);
}
