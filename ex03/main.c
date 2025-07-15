/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:10:07 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/20 20:16:22 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hexdump.h"

void	process_non_empty_file(char *bin_name, unsigned int *offset,
		t_carry *carry, t_counters *counters)
{
	int	count;

	if (counters->file_name == NULL)
		count = process_file(bin_name, NULL, offset, carry);
	else
		count = process_file(bin_name, counters->file_name, offset, carry);
	if (count == 1)
		counters->count_file++;
}

void	finalize_process(unsigned int offset, t_carry *carry,
		t_counters counters)
{
	if (carry->size > 0)
		handle_carry(&offset, carry->carry, &carry->size);
	if (counters.count_file > 0)
	{
		write_offset(offset, 1);
		write(1, "\n", 1);
	}
}

void	process_stdin(unsigned int *offset, t_carry *carry)
{
	unsigned char	buffer[BUFFER_SIZE];
	int				bytes_read;
	int				i;

	bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			carry->carry[carry->size++] = buffer[i];
			if (carry->size == 16)
			{
				process_buffer(offset, carry->carry, carry->size);
				carry->size = 0;
			}
			i++;
		}
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	}
	if (carry->size > 0)
	{
		handle_carry(offset, carry->carry, &carry->size);
	}
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

int	main(int argc, char **argv)
{
	if (argc < 2 || ft_strcmp(argv[1], "-C") != 0)
	{
		write(2, "Usage: ./ft_hexdump -C file1 [file2 ...]\n", 41);
		return (1);
	}
	if (process_files(argc, argv) == 0)
	{
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, ": all input file arguments failed\n", 34);
	}
	return (0);
}
