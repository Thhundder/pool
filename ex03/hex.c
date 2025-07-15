/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:14:41 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/19 18:10:15 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hexdump.h"

void	write_offset(unsigned int offset, int final)
{
	char	hex[9];
	int		index;

	index = 7;
	while (index >= 0)
	{
		hex[index] = "0123456789abcdef"[offset % 16];
		offset /= 16;
		index--;
	}
	hex[8] = '\0';
	write(1, hex, 8);
	if (final == 0)
		write(1, "  ", 2);
}

void	write_hex_byte(unsigned char byte)
{
	char	hex[3];

	hex[0] = "0123456789abcdef"[byte / 16];
	hex[1] = "0123456789abcdef"[byte % 16];
	hex[2] = ' ';
	write(1, hex, 3);
}

void	write_hex(unsigned char *buffer, int size)
{
	int	index;

	index = 0;
	while (index < BUFFER_SIZE)
	{
		if (index < size)
			write_hex_byte(buffer[index]);
		else
			write(1, "   ", 3);
		if (index == 7)
			write(1, " ", 1);
		index++;
	}
}

void	write_chars(unsigned char *buffer, int size)
{
	int		index;
	char	c;

	write(1, " |", 2);
	index = 0;
	while (index < size)
	{
		c = '.';
		if (buffer[index] >= 32 && buffer[index] <= 126)
			c = buffer[index];
		write(1, &c, 1);
		index++;
	}
	write(1, "|\n", 2);
}

int	is_empty(char *file_name)
{
	int		fd;
	int		count;
	char	buffer[BUFFER_SIZE];

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (0);
	count = read(fd, buffer, BUFFER_SIZE);
	close(fd);
	if (count == 0)
		return (1);
	return (0);
}
