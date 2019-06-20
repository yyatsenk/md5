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

unsigned int	little_big(unsigned int little)
{
	return ((little & 0xff) << 24) + ((little & 0xff00) << 8)\
	+ ((little & 0xff0000) >> 8) + ((little >> 24) & 0xff);
}

static int		do_everything(t_flags flags)
{
	if (flags.algo == 0)
		do_md5(flags);
	else if (flags.algo == 1)
		do_sha256(flags);
	return (0);
}

static void		construct_flags(t_flags *flags)
{
	flags->q = 0;
	flags->p = 0;
	flags->r = 0;
	flags->s = 0;
	flags->str = 0;
	flags->filename = 0;
	flags->algo = -1;
}

static int		parse_param(t_flags *flags, int argv, char **argc)
{
	int			i;

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
			if ((flags->s = 1) && i + 1 != argv)
				flags->str = argc[++i];
			else
				return (0);
		}
		else
		{
			flags->filename = &argc[i];
			break ;
		}
	return (1);
}

int				main(int argv, char **argc)
{
	t_flags		flags;

	if (argv < 2)
	{
		ft_printf("usage: %s [-s]'string' [-q][-p][-r] filename\n", argc[0]);
		return (0);
	}
	construct_flags(&flags);
	if (!ft_strcmp(argc[1], "md5"))
		flags.algo = 0;
	else if (!ft_strcmp(argc[1], "sha256"))
		flags.algo = 1;
	if (!parse_param(&flags, argv, argc))
	{
		ft_printf("usage: %s [-s]'string' [-q][-p][-r] filename\n", argc[0]);
		return (0);
	}
	do_everything(flags);
	return (0);
}
