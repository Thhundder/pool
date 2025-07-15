/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:15:17 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/20 20:50:36 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEXDUMP_H
# define FT_HEXDUMP_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 16

typedef struct s_carry
{
	unsigned char	carry[BUFFER_SIZE];
	int				size;
}					t_carry;

typedef struct s_args
{
	int				argc;
	char			**argv;
}					t_args;

typedef struct s_counters
{
	int				count_file;
	int				empty;
	char			*file_name;
}					t_counters;

int					process_files(int argc, char **argv);
int					process_file(char *bin_name, char *file_name,
						unsigned int *hex_position, t_carry *carry);
int					read_file(int file_handle, unsigned int *hex_position,
						unsigned char *leftover_data, int *leftover_size);
int					read_chunk(int file_handle, unsigned char *data_block,
						int max_capacity);
void				read_fill_carry(int file_handle, unsigned char *data_block,
						unsigned char *leftover_data, int *leftover_size);
void				process_buffer(unsigned int *hex_position,
						unsigned char *data_block, int data_length);
void				handle_carry(unsigned int *hex_position,
						unsigned char *leftover_data, int *leftover_size);
void				write_offset(unsigned int hex_position, int is_terminal);
void				write_hex(unsigned char *data_block, int data_length);
void				write_hex_byte(unsigned char single_byte);
void				write_chars(unsigned char *data_block, int data_length);
void				handle_error(char *bin_name, char *file_name);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_strlen(char *str);
int					is_empty(char *file_name);
void				process_non_empty_file(char *bin_name, unsigned int *offset,
						t_carry *carry, t_counters *counters);
void				finalize_process(unsigned int offset, t_carry *carry,
						t_counters counters);
void				process_stdin(unsigned int *offset, t_carry *carry);
#endif
