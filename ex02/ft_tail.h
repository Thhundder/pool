/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:31:11 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/20 20:59:50 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TAIL_H
# define FT_TAIL_H

# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_file_info
{
	int	bytes;
	int	multiple_files;
}	t_file_info;

void	print_error(char *bin_name, char *filename, int file);
int		verify_input(char *bin_name, int argc, char **argv);
void	process_file(char *bin_name, char *filename, int bytes,
			int multiple_files);
void	display_tail(char *content, int file_size, int bytes);
void	print_newline(int multiple_files);
int		ft_atoi_valid(char *str);
void	copy_data(char *dest, char *src, int size);
int		ft_strlen(char *str);
char	*append_to_content(char *content, char *buffer, int total_size,
			int bytes);
char	*read_file(int fd, int *file_size);
void	process_stdin(char *bin_name, int bytes);

#endif
