/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uw.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:43:15 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/20 20:56:49 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tail.h"
#include <stdio.h>

void	print_newline(int multiple_files)
{
	static int	i = 1;

	if (i < multiple_files)
	{
		write(1, "\n", 1);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	verify_input(char *bin_name, int argc, char **argv)
{
	int		bytes;
	char	*cpy;

	cpy = argv[2];
	if (argc < 3 || ft_strcmp(argv[1], "-c") != 0)
	{
		write(2, bin_name, ft_strlen(bin_name));
		write(2, ": option requires an argument -- 'c'\n", 37);
		write(2, "Try ", 4);
		write(2, bin_name, ft_strlen(bin_name));
		write(2, " --help' for more information.\n", 31);
		return (-1);
	}
	bytes = ft_atoi_valid(cpy);
	if (bytes < 0)
	{
		write(2, bin_name, ft_strlen(bin_name));
		write(2, ": invalid number of bytes: '", 28);
		write(2, argv[2], ft_strlen(argv[2]));
		write(2, "'\n", 2);
		return (-1);
	}
	return (bytes);
}
