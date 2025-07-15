/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:15:55 by emorreal          #+#    #+#             */
/*   Updated: 2025/02/20 20:20:48 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hexdump.h"

void	process_stdin_mode(unsigned int *offset, t_carry *carry,
		t_counters *counters)
{
	process_stdin(offset, carry);
	counters->count_file++;
}

void	process_file_mode(t_args *args, unsigned int *offset, t_carry *carry,
		t_counters *counters)
{
	int	i;

	i = 2;
	while (i < args->argc)
	{
		counters->empty += is_empty(args->argv[i]);
		if (is_empty(args->argv[i]))
		{
			i++;
			continue ;
		}
		counters->file_name = args->argv[i];
		process_non_empty_file(args->argv[0], offset, carry, counters);
		i++;
	}
}

int	process_files(int argc, char **argv)
{
	unsigned int	offset;
	t_carry			carry;
	t_counters		counters;
	t_args			args;

	args.argc = argc;
	args.argv = argv;
	offset = 0;
	carry.size = 0;
	counters.count_file = 0;
	counters.empty = 0;
	if (argc == 2)
		process_stdin_mode(&offset, &carry, &counters);
	else
		process_file_mode(&args, &offset, &carry, &counters);
	finalize_process(offset, &carry, counters);
	return (counters.count_file + counters.empty);
}
