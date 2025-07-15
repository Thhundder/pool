/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:15:55 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/20 20:56:23 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tail.h"

void	print_error(char *bin_name, char *filename, int file)
{
	write(2, bin_name, ft_strlen(bin_name));
	write(2, ": ", 2);
	if (file == 1)
	{
		write(2, "cannot open '", 13);
		write(2, filename, ft_strlen(filename));
		write(2, "' for reading: ", 15);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	else
	{
		write(2, filename, ft_strlen(filename));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
}

int	ft_atoi_valid(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr);
}

void	copy_data(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
}

void	display_tail(char *content, int file_size, int bytes)
{
	if (bytes > file_size)
		bytes = file_size;
	write(1, content + (file_size - bytes), bytes);
}

int	main(int argc, char **argv)
{
	int	bytes;
	int	multiple_files;
	int	i;

	bytes = verify_input(argv[0], argc, argv);
	if (bytes == -1)
		return (1);
	if (bytes == 0)
		return (0);
	multiple_files = argc - 3;
	if (argc == 3)
		process_stdin(argv[0], bytes);
	else
	{
		i = 3;
		while (i < argc)
		{
			process_file(argv[0], argv[i], bytes, multiple_files);
			i++;
		}
	}
	return (0);
}
