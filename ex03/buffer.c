/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:13:25 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/17 04:47:25 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hexdump.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

void	process_buffer(unsigned int *offset, unsigned char *buffer, int size)
{
	static unsigned char	last_buffer[BUFFER_SIZE];
	static int				last_size = 0;
	static int				repeated_star = 0;

	if (size == last_size && ft_memcmp(last_buffer, buffer, size) == 0)
	{
		if (repeated_star == 0)
		{
			write(1, "*\n", 2);
			repeated_star = 1;
		}
	}
	else
	{
		repeated_star = 0;
		write_offset(*offset, 0);
		write_hex(buffer, size);
		write_chars(buffer, size);
		ft_memcpy(last_buffer, buffer, size);
		last_size = size;
	}
	*offset += size;
}

void	handle_carry(unsigned int *offset, unsigned char *carry,
		int *carry_size)
{
	static unsigned char	last_buffer[BUFFER_SIZE];
	static int				last_size = 0;
	static int				repeated_star = 0;

	if (*carry_size == last_size && ft_memcmp(last_buffer, carry,
			*carry_size) == 0)
	{
		if (repeated_star == 0)
		{
			write(1, "*\n", 2);
			repeated_star = 1;
		}
	}
	else
	{
		repeated_star = 0;
		write_offset(*offset, 0);
		write_hex(carry, *carry_size);
		write_chars(carry, *carry_size);
		ft_memcpy(last_buffer, carry, *carry_size);
		last_size = *carry_size;
	}
	*offset += *carry_size;
	*carry_size = 0;
}
