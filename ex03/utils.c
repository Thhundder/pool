/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:11:58 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/20 20:17:18 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hexdump.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;
	size_t				i;

	i = 0;
	d = (unsigned char *)dest;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

int	read_chunk(int fd, unsigned char *buffer, int size)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, size);
	return (bytes_read);
}

void	read_fill_carry(int fd, unsigned char *buffer, unsigned char *carry,
		int *carry_size)
{
	int	fill;
	int	bytes_read;

	fill = BUFFER_SIZE - *carry_size;
	bytes_read = read_chunk(fd, buffer, fill);
	if (bytes_read > 0)
	{
		ft_memcpy(carry + *carry_size, buffer, bytes_read);
		*carry_size += bytes_read;
	}
}

int	read_file(int fd, unsigned int *offset, unsigned char *carry,
		int *carry_size)
{
	unsigned char	buffer[BUFFER_SIZE];
	int				bytes_read;

	if (*carry_size > 0)
	{
		read_fill_carry(fd, buffer, carry, carry_size);
		handle_carry(offset, carry, carry_size);
	}
	bytes_read = read_chunk(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (1);
	while (bytes_read > 0)
	{
		if (bytes_read < BUFFER_SIZE)
		{
			ft_memcpy(carry, buffer, bytes_read);
			*carry_size = bytes_read;
			return (0);
		}
		process_buffer(offset, buffer, bytes_read);
		bytes_read = read_chunk(fd, buffer, BUFFER_SIZE);
	}
	return (0);
}

int	process_file(char *bin_name, char *filename, unsigned int *offset,
		t_carry *carry)
{
	int	fd;

	if (filename == NULL)
		fd = STDIN_FILENO;
	else
		fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		if (bin_name && filename)
			handle_error(bin_name, filename);
		return (0);
	}
	else
	{
		if (read_file(fd, offset, carry->carry, &carry->size) == 1)
		{
			if (filename)
				close(fd);
			return (2);
		}
		if (filename)
			close(fd);
	}
	return (1);
}
