/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:29:56 by yyatsenk          #+#    #+#             */
/*   Updated: 2019/06/17 12:29:58 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void	print_hash(unsigned char *buf)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		ft_printf("%2.2x", buf[i]);
		i++;
	}
}

void	print_algo_str(char *algo, char *str, unsigned char *hash)
{
	if (!ft_strcmp(algo, "SHA256"))
	{
		ft_printf("%s (\"%s\") = ", algo, str);
		print_hash(hash);
		ft_printf("\n");
	}
	else
		ft_printf("%s (\"%s\") = %s\n", algo, str, hash);
}

void	print_algo_file(char *algo, char *str, unsigned char *hash)
{
	if (!ft_strcmp(algo, "SHA256"))
	{
		ft_printf("%s (%s) = ", algo, str);
		print_hash(hash);
		ft_printf("\n");
	}
	else
		ft_printf("%s (%s) = %s\n", algo, str, hash);
}

void	print_str_rev(char *algo, char *str, unsigned char *hash)
{
	if (!ft_strcmp(algo, "SHA256"))
	{
		print_hash(hash);
		ft_printf(" \"%s\"\n", str);
	}
	else
		ft_printf("%s \"%s\"\n", hash, str);
}

void	print_file_rev(char *algo, char *str, unsigned char *hash)
{
	if (!ft_strcmp(algo, "SHA256"))
	{
		print_hash(hash);
		ft_printf(" %s\n", str);
	}
	else
		ft_printf("%s %s\n", hash, str);
}
