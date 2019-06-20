/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:29:56 by yyatsenk          #+#    #+#             */
/*   Updated: 2019/06/17 12:29:58 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

char		*get_str_md5(t_mda5 md5_data)
{
	char	*input_hash;
	char	*tmp;

	input_hash = NULL;
	tmp = NULL;
	input_hash = ft_itoa_base(little_big(md5_data.h0), 16, 0);
	tmp = input_hash;
	input_hash = ft_strjoin(input_hash,\
		ft_itoa_base(little_big(md5_data.h1), 16, 0));
	free(tmp);
	tmp = input_hash;
	input_hash = ft_strjoin(input_hash,\
		ft_itoa_base(little_big(md5_data.h2), 16, 0));
	free(tmp);
	tmp = input_hash;
	input_hash = ft_strjoin(input_hash,\
		ft_itoa_base(little_big(md5_data.h3), 16, 0));
	free(tmp);
	return (input_hash);
}

static void	do_md5_str(t_flags flags, t_mda5 md5_data)
{
	char	*res;

	if (flags.str != NULL)
	{
		md5((uint8_t *)flags.str, ft_strlen(flags.str), &md5_data);
		res = get_str_md5(md5_data);
		if (flags.q)
			printf("%s\n", res);
		else if (flags.r)
			print_str_rev("MD5", flags.str, (unsigned char *)res);
		else
			print_algo_str("MD5", flags.str, (unsigned char *)res);
	}
}

static void	do_md5_file_help(t_flags flags, char *res)
{
	if (flags.q)
		printf("%s\n", res); 
	else if (flags.r)
		print_file_rev("MD5", flags.filename[0], (unsigned char *)res);
	else
		print_algo_file("MD5", flags.filename[0], (unsigned char *)res);
}

static void	do_md5_file(t_flags flags, char *buff_input, t_mda5 md5_data, int i)
{
	char	*res;
	int		fd;

	while (flags.filename[0] != NULL)
	{
		fd = open(flags.filename[0], O_RDONLY);
		if (fd < 0)
		{
			printf("md5: %s: No such file or directory\n", flags.filename[0]);
			return ;
		}
		buff_input = ft_strnew(B_SIZE);
		if ((i = read(fd, buff_input, B_SIZE)) < 0)
		{
			printf("md5: %s: Bad file passed\n", flags.filename[0]);
			return ;
		}
		buff_input[i] = '\0';
		md5((uint8_t *)buff_input, i, &md5_data);
		res = get_str_md5(md5_data);
		do_md5_file_help(flags, res);
		flags.filename++;
	}
}

int			do_md5(t_flags flags)
{
	char	*res;
	char	*buff_input;
	t_mda5	md5_data;
	int		i;

	buff_input = NULL;
	if ((!flags.filename && !flags.str) || flags.p)
	{
		buff_input = ft_strnew(B_SIZE);
		if ((i = read(0, buff_input, B_SIZE)) < 0)
			return (-1);
		buff_input[i] = '\0';
		md5((uint8_t *)buff_input, i, &md5_data);
		res = get_str_md5(md5_data);
		if(flags.p)
			printf("%s", buff_input);
		printf("%s\n", res);
		free(buff_input);
	}
	do_md5_str(flags, md5_data);
	if(flags.filename != NULL)
		do_md5_file(flags, buff_input, md5_data, i);
	return (0);
}