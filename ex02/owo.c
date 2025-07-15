/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   owo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:57:33 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/20 21:06:46 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tail.h"

int	open_file_descriptor(char *filename)
{
	if (filename == NULL)
		return (STDIN_FILENO);
	return (open(filename, O_RDONLY));
}

void	handle_file_content(char *filename, int fd,
		t_file_info *info)
{
	char	*content;
	int		file_size;

	content = read_file(fd, &file_size);
	if (content)
	{
		if (info->multiple_files > 1)
		{
			write(1, "==> ", 4);
			write(1, filename, ft_strlen(filename));
			write(1, " <==\n", 5);
		}
		display_tail(content, file_size, info->bytes);
		free(content);
		print_newline(info->multiple_files);
	}
}

void	process_file(char *bin_name, char *filename, int bytes,
		int multiple_files)
{
	int			fd;
	t_file_info	info;

	info.bytes = bytes;
	info.multiple_files = multiple_files;
	fd = open_file_descriptor(filename);
	if (fd == -1)
	{
		print_error(bin_name, filename, 1);
		return ;
	}
	handle_file_content(filename, fd, &info);
	if (filename)
		close(fd);
}
