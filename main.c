/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:29:56 by yyatsenk          #+#    #+#             */
/*   Updated: 2019/06/17 12:29:58 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
//#include <stdint.h>


void print_hash(unsigned char *buf)
{
	int i;

	i = 0;
	while(i < 32)
	{
		printf("%2.2x", buf[i]);
		i++;
	}
}

void print_algo_str(char *algo, char *str, char *hash)
{
	if (!ft_strcmp(algo, "SHA256"))
	{
		printf("%s (\"%s\") =", algo, str);
		print_hash(hash);
		printf("\n");
	}
	else
		printf("%s (\"%s\") = %s\n", algo, str, hash);
}

void print_algo_file(char *algo, char *str, char *hash)
{
	if (!ft_strcmp(algo, "SHA256"))
	{
		printf("%s (%s) =", algo, str);
		print_hash(hash);
		printf("\n");
	}
	else
		printf("%s (%s) = %s\n", algo, str, hash);
}

void print_str_rev(char *algo, char *str, char *hash)
{
	if (!ft_strcmp(algo, "SHA256"))
	{
		print_hash(hash);
		printf(" \"%s\"\n", str);
	}
	else
		printf("%s \"%s\"\n", hash, str);
}

void print_file_rev(char *algo, char *str, char *hash)
{
	if (!ft_strcmp(algo, "SHA256"))
	{
		print_hash(hash);
		printf(" %s\n", str);
	}
	else
		printf("%s %s\n", hash, str);
}

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

typedef unsigned uint32_t;
typedef unsigned  char uint8_t;

void md5_help_3(t_abcd *abcd, int *f, int *g, int i)
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

void md5_help_2(t_abcd *abcd, uint32_t *w) 
{
	uint8_t *p;
	uint32_t temp;
	for(int i = 0; i<64; i++) {

			p=(uint8_t *)&abcd->a;
			p=(uint8_t *)&abcd->b;
			p=(uint8_t *)&abcd->c;
			p=(uint8_t *)&abcd->d;
			uint32_t f;
			uint32_t g;

			md5_help_3(abcd, &f, &g, i);
			temp = abcd->d;
			abcd->d = abcd->c;
			abcd->c = abcd->b;
			abcd->b = abcd->b + LEFTROTATE((abcd->a + f + k5[i] + w[g]), r5[i]);
			abcd->a = temp;
		}
}

void md5_help(t_mda5 *md5, int new_len, uint8_t *msg) 
{
	int offset;
	for(offset=0; offset<new_len; offset += (512/8))
	{
		uint32_t *w = (uint32_t *) (msg + offset);
		int j;
		t_abcd abcd;
		abcd.a = md5->h0;
		abcd.b = md5->h1;
		abcd.c = md5->h2;
		abcd.d = md5->h3;
		uint32_t i;
		md5_help_2(&abcd, w);
		md5->h0 += abcd.a;
		md5->h1 += abcd.b;
		md5->h2 += abcd.c;
		md5->h3 += abcd.d;
	}
}
 
void md5(uint8_t *initial_msg, size_t initial_len, t_mda5 *md5)
{
 
	uint8_t *msg;
	int new_len;
	uint32_t bits_len;

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
 

//sha256

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

void sha256_transform_help(t_sha256 *ctx, const unsigned char data[], t_abcd256 abcd256, unsigned int m[64])
{
	unsigned int t1;
	unsigned int t2;
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
	ctx->state[0] += abcd256.a;
	ctx->state[1] += abcd256.b;
	ctx->state[2] += abcd256.c;
	ctx->state[3] += abcd256.d;
	ctx->state[4] += abcd256.e;
	ctx->state[5] += abcd256.f;
	ctx->state[6] += abcd256.g;
	ctx->state[7] += abcd256.h;
}

void sha256_transform_help_2(unsigned int *m, const unsigned char data[])
{
	unsigned int i;
	unsigned int j;

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

void sha256_transform(t_sha256 *ctx, const unsigned char data[])
{
	unsigned int m[64];
	t_abcd256 abcd256;

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

void sha256_create(t_sha256 *ctx)
{
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}

void sha256_update(t_sha256 *ctx, const unsigned char data[], size_t len)
{
	unsigned int i;

	i = -1;
	while (++i < len)
	{
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64)
		{
			sha256_transform(ctx, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
	}
}

void sha256_res_help(t_sha256 *ctx, unsigned char hash[])
{
	int i;

	i = -1;
	ctx->bitlen += ctx->datalen * 8;
	ctx->data[63] = ctx->bitlen;
	ctx->data[62] = ctx->bitlen >> 8;
	ctx->data[61] = ctx->bitlen >> 16;
	ctx->data[60] = ctx->bitlen >> 24;
	ctx->data[59] = ctx->bitlen >> 32;
	ctx->data[58] = ctx->bitlen >> 40;
	ctx->data[57] = ctx->bitlen >> 48;
	ctx->data[56] = ctx->bitlen >> 56;
	sha256_transform(ctx, ctx->data);
	while(++i < 4)
	{
		hash[i] = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
	}
}

void sha256_res(t_sha256 *ctx, unsigned char hash[])
{
	unsigned int i;

	i = ctx->datalen;
	if (ctx->datalen < 56)
	{
		ctx->data[i++] = 0x80;
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else
	{
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		sha256_transform(ctx, ctx->data);
		ft_memset(ctx->data, 0, 56);
	}
	sha256_res_help(ctx, hash);
}

#define B_SIZE 4096

unsigned int little_big(unsigned int little)
{
	return ((little & 0xff) << 24) + ((little & 0xff00) << 8)\
	+ ((little & 0xff0000) >> 8) + ((little >> 24) & 0xff);
}

char *get_str_md5(t_mda5 md5_data)
{
	char *input_hash;
	char *tmp;

	input_hash = NULL;
	tmp = NULL;
	input_hash = ft_itoa_base(little_big(md5_data.h0), 16, 0);
	tmp = input_hash;
	input_hash = ft_strjoin(input_hash, ft_itoa_base(little_big(md5_data.h1), 16, 0));
	free(tmp);
	tmp = input_hash;
	input_hash = ft_strjoin(input_hash, ft_itoa_base(little_big(md5_data.h2), 16, 0));
	free(tmp);
	tmp = input_hash;
	input_hash = ft_strjoin(input_hash, ft_itoa_base(little_big(md5_data.h3), 16, 0));
	free(tmp);
	return (input_hash);
}
int do_everything(t_flags flags)
{
	t_mda5 md5_data;
	t_sha256 ctx;
	char *res;
	char *buff_input;
	int i;
	int j;
	unsigned char buf[SHA256_BLOCK_SIZE];

	buff_input = NULL;
	j = 0;
	if (flags.algo == 0)
	{
		if (flags.filename == NULL && flags.str == NULL || flags.p)
		{
			buff_input = ft_strnew(B_SIZE);
			if ((i = read(0, buff_input, B_SIZE)) < 0)
				return (-1);
			buff_input[i] = '\0';
			md5(buff_input, i, &md5_data);
			res = get_str_md5(md5_data);
			if(flags.p)
				printf("%s", buff_input);
			printf("%s\n", res);
			free(buff_input);
		}
		if (flags.str != NULL)
		{
			md5(flags.str, ft_strlen(flags.str), &md5_data);
			res = get_str_md5(md5_data);
			if (flags.q)
				printf("%s\n", res);
			else if (flags.r)
				print_str_rev("MD5", flags.str, res);
			else
				print_algo_str("MD5", flags.str, res);
		}
		while (flags.filename[0] != NULL)
		{
			int fd;

			fd = open(flags.filename[j], O_RDONLY);
			if (fd < 0)
			{
				printf("md5: %s: No such file or directory\n", flags.filename[j]);
				return (-1);
			}
			buff_input = ft_strnew(B_SIZE);
			if ((i = read(fd, buff_input, B_SIZE)) < 0)
			{
				printf("md5: %s: Bad file passed\n", flags.filename[j]);
				return (-1);
			}
			buff_input[i] = '\0';
			md5(buff_input, i, &md5_data);
			res = get_str_md5(md5_data);
			if (flags.q)
				printf("%s\n", res); 
			else if (flags.r)
				print_file_rev("MD5", flags.filename[j], res);
			else
				print_algo_file("MD5", flags.filename[j], res);
			flags.filename++;
		}	
	}
	if (flags.algo == 1)
	{
		if (flags.filename == NULL && flags.str == NULL || flags.p)
		{
			buff_input = ft_strnew(B_SIZE);
			if ((i = read(0, buff_input, B_SIZE)) < 0)
				return (-1);
			buff_input[i] = '\0';
			sha256_create(&ctx);
			sha256_update(&ctx, buff_input, strlen(buff_input));
			sha256_res(&ctx, buf);
			if(flags.p)
				printf("%s", buff_input);
			print_hash(buf);
			printf("\n");
			free(buff_input);
		}
		if (flags.str != NULL)
		{
			sha256_create(&ctx);
			sha256_update(&ctx, flags.str, strlen(flags.str));
			sha256_res(&ctx, buf);
			if(flags.q)
				print_hash(buf);
			else if (flags.r)
				print_str_rev("SHA256", flags.str, buf);
			else
				print_algo_str("SHA256", flags.str, buf);
		}
		while (flags.filename[0] != NULL)
		{
			int fd;

			fd = open(flags.filename[j], O_RDONLY);
			if (fd < 0)
			{
				printf("md5: %s: No such file or directory\n", flags.filename[0]);
				return (-1);
			}
			buff_input = ft_strnew(B_SIZE);
			if ((i = read(fd, buff_input, B_SIZE)) < 0)
			return (-1);
			buff_input[i] = '\0';
			sha256_create(&ctx);
			sha256_update(&ctx, buff_input, strlen(buff_input));
			sha256_res(&ctx, buf);
			if(flags.q)
			{
				print_hash(buf);
				printf("\n");
			}
			else if (flags.r)
				print_file_rev("SHA256", flags.filename[0], buf);
			else
				print_algo_file("SHA256", flags.filename[0], buf);
			flags.filename++;
		}
	}
	return (0);
}

void construct_flags(t_flags *flags)
{
	flags->q = 0;
	flags->p = 0;
	flags->r = 0;
	flags->s = 0;
	flags->str = 0;
	flags->filename = 0;
	flags->algo = -1;
}

int parse_param(t_flags *flags, int argv, char **argc)
{
	int i;

	i = 1;
	if (flags->algo == -1)
		return (0);
	while (++i < argv)
		if (!ft_strcmp(argc[i], "-q"))
			flags->q = 1;
		else if (!ft_strcmp(argc[i], "-p"))
			flags->p = 1;
		else if (!ft_strcmp(argc[i], "-r"))
			flags->r = 1;
		else if (!ft_strcmp(argc[i], "-s"))
		{
			if ((flags->s = 1) &&i + 1 != argv)
				flags->str = argc[++i];
			else
				return (0);
		}
		else
		{
			flags->filename = &argc[i];
			break;
		}
	return (1);
}

int main(int argv, char **argc)
{
	t_mda5 md5_data;
	char *msg;
	size_t len;
	t_flags flags;
	
	int i = 1;
	if (argv < 2) {
		printf("usage: %s 'string'\n", argc[0]);
		return 0;
	}
	construct_flags(&flags);
	if (!ft_strcmp(argc[1], "md5"))
		flags.algo = 0;
	else if (!ft_strcmp(argc[1], "sha256"))
		flags.algo = 1;
	if (!parse_param(&flags, argv, argc))
	{
		printf("usage: %s 'string'\n", argc[0]);
		return 0;
	}
	do_everything(flags);
	return(0);
}
