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
# define SSL_H

# include "ft_printf/libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>

# define SHA256_BLOCK_SIZE 32
# define B_SIZE 4096
# define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

typedef struct			s_flags
{
	unsigned			p;
	unsigned			q;
	unsigned			r;
	unsigned			s;
	char				**filename;
	char				*str;
	short				algo;
}						t_flags;

typedef struct			s_abcd
{
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
}						t_abcd;

typedef struct			s_mda5
{
	uint32_t			h0;
	uint32_t			h1;
	uint32_t			h2;
	uint32_t			h3;
	t_flags				flags;
}						t_mda5;

typedef struct			s_abcd256
{
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
	uint32_t			e;
	uint32_t			f;
	uint32_t			g;
	uint32_t			h;
}						t_abcd256;

typedef struct			s_sha256
{
	unsigned char		data[64];
	unsigned int		datalen;
	unsigned long long	bitlen;
	unsigned int		state[8];
	t_abcd256			abcd256;
	t_flags				flags;
}						t_sha256;

# define ROT_LEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
# define ROT_RIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

# define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define EP0(x) (ROT_RIGHT(x,2) ^ ROT_RIGHT(x,13) ^ ROT_RIGHT(x,22))
# define EP1(x) (ROT_RIGHT(x,6) ^ ROT_RIGHT(x,11) ^ ROT_RIGHT(x,25))
# define SIG0(x) (ROT_RIGHT(x,7) ^ ROT_RIGHT(x,18) ^ ((x) >> 3))
# define SIG1(x) (ROT_RIGHT(x,17) ^ ROT_RIGHT(x,19) ^ ((x) >> 10))

void					print_hash(unsigned char *buf);
void					print_algo_str(char *algo, char *str,\
	unsigned char *hash);
void					print_algo_file(char *algo, char *str,\
	unsigned char *hash);
void					print_str_rev(char *algo, char *str,\
	unsigned char *hash);
void					print_file_rev(char *algo, char *str,\
	unsigned char *hash);
void					md5(uint8_t *initial_msg,\
	size_t initial_len, t_mda5 *md5);
void					sha256_update(t_sha256 *ctx,\
	unsigned char data[], size_t len);
void					sha256_res(t_sha256 *ctx,\
	unsigned char hash[]);
void					sha256_transform(t_sha256 *ctx,\
	const unsigned char data[]);
int						do_md5(t_flags flags);
char					*get_str_md5(t_mda5 md5_data);
unsigned int			little_big(unsigned int little);
int						do_sha256(t_flags flags);

#endif
