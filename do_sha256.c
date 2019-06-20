/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:29:56 by yyatsenk          #+#    #+#             */
/*   Updated: 2019/06/17 12:29:58 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static void			do_sha256_str(t_flags flags, t_sha256 ctx,\
unsigned char *buf)
{
	if (flags.str != NULL)
	{
		sha256_update(&ctx, (unsigned char *)flags.str, strlen(flags.str));
		sha256_res(&ctx, buf);
		if (flags.q)
		{
			print_hash(buf);
			ft_printf("\n");
		}
		else if (flags.r)
			print_str_rev("SHA256", flags.str, buf);
		else
			print_algo_str("SHA256", flags.str, buf);
	}
}

static void			do_sha256_file_help(t_flags flags, unsigned char *buf)
{
	if (flags.q)
	{
		print_hash(buf);
		ft_printf("\n");
	}
	else if (flags.r)
		print_file_rev("SHA256", flags.filename[0], buf);
	else
		print_algo_file("SHA256", flags.filename[0], buf);
}

static void			do_sha256_file(t_flags flags, t_sha256 ctx,\
unsigned char *buf, char *buff_input)
{
	int				fd;
	int				i;

	while (flags.filename[0] != NULL)
	{
		fd = open(flags.filename[0], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("md5: %s: No such file or directory\n",\
				flags.filename[0]);
			return ;
		}
		buff_input = ft_strnew(B_SIZE);
		if ((i = read(fd, buff_input, B_SIZE)) < 0)
			return ;
		buff_input[i] = '\0';
		sha256_update(&ctx, (unsigned char *)buff_input, strlen(buff_input));
		sha256_res(&ctx, buf);
		do_sha256_file_help(flags, buf);
		flags.filename++;
	}
}

int					do_sha256(t_flags flags)
{
	t_sha256		ctx;
	char			*buff_input;
	int				i;
	unsigned char	buf[SHA256_BLOCK_SIZE];

	buff_input = NULL;
	ctx.bitlen = 0;
	if ((!flags.filename && !flags.str) || flags.p)
	{
		buff_input = ft_strnew(B_SIZE);
		if ((i = read(0, buff_input, B_SIZE)) < 0)
			return (-1);
		buff_input[i] = '\0';
		sha256_update(&ctx, (unsigned char *)buff_input, strlen(buff_input));
		sha256_res(&ctx, buf);
		if (flags.p)
			ft_printf("%s", buff_input);
		print_hash(buf);
		ft_printf("\n");
		free(buff_input);
	}
	do_sha256_str(flags, ctx, buf);
	if (flags.filename != NULL)
		do_sha256_file(flags, ctx, buf, buff_input);
	return (0);
}
