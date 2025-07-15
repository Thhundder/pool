/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:53:39 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/14 20:54:44 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

int	error_handling(int argc, char **argv)
{
	int	fd;

	if (argc == 1)
	{
		write(2, "File name missing.\n", 19);
		return (-1);
	}
	if (argc > 2)
	{
		write(2, "Too many arguments.\n", 20);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (-1);
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	buffer[1000];
	int		bytes;

	fd = error_handling(argc, argv);
	if (fd == -1)
		return (1);
	bytes = read(fd, buffer, sizeof(buffer));
	while (bytes > 0)
	{
		write(1, buffer, bytes);
		bytes = read(fd, buffer, sizeof(buffer));
	}
	if (bytes == -1)
		write(2, "Error reading file.\n", 20);
	close(fd);
	return (0);
}
