/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uwu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:43:51 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/20 20:57:26 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tail.h"

char	*append_to_content(char *content, char *buffer, int total_size,
		int bytes)
{
	char	*tmp;

	tmp = malloc(total_size + bytes);
	if (!tmp)
		return (NULL);
	if (content)
	{
		copy_data(tmp, content, total_size);
		free(content);
	}
	copy_data(tmp + total_size, buffer, bytes);
	return (tmp);
}

char	*read_file(int fd, int *file_size)
{
	char	buffer[1024];
	char	*content;
	int		bytes;
	int		total_size;

	total_size = 0;
	content = NULL;
	bytes = read(fd, buffer, sizeof(buffer));
	while (bytes > 0)
	{
		content = append_to_content(content, buffer, total_size, bytes);
		if (!content)
			return (NULL);
		total_size += bytes;
		bytes = read(fd, buffer, sizeof(buffer));
	}
	*file_size = total_size;
	return (content);
}

void	process_stdin(char *bin_name, int bytes)
{
	char	*content;
	int		file_size;

	content = read_file(STDIN_FILENO, &file_size);
	if (content)
	{
		display_tail(content, file_size, bytes);
		free(content);
	}
	else
	{
		print_error(bin_name, "stdin", 0);
	}
}
