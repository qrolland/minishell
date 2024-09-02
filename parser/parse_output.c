/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:13:36 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:13:39 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_output(t_command *command)
{
	if (command->io_data.out_fd != -1)
		close(command->io_data.out_fd);
	if (command->io_data.outfile)
		free(command->io_data.outfile);
	command->io_data.outfile = 0;
	command->io_data.out_fd = -1;
}

int	parse_trunc(t_command *command, t_token **token, t_data *data)
{
	if (!init_parse_io(command, token, 0, data))
		return (0);
	if (get_nbr_quotes((*token)->str) && !rm_quotes(&((*token)->str)))
		return (0);
	command->io_data.out_fd = open(command->io_data.outfile,
			O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (command->io_data.out_fd < 0)
	{
		print_error(1, command->io_data.outfile, strerror(errno));
		return (0);
	}
	return (1);
}

int	parse_append(t_command *command, t_token **token, t_data *data)
{
	if (!init_parse_io(command, token, 0, data))
		return (0);
	if (get_nbr_quotes((*token)->str) && !rm_quotes(&((*token)->str)))
		return (0);
	command->io_data.out_fd = open(command->io_data.outfile,
			O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (command->io_data.out_fd < 0)
	{
		print_error(1, command->io_data.outfile, strerror(errno));
		return (0);
	}
	return (1);
}
