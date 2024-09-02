/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:13:27 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:13:30 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_input(t_command *command)
{
	if (command->io_data.in_fd != -1)
		close(command->io_data.in_fd);
	if (command->io_data.heredoc_del)
	{
		free(command->io_data.heredoc_del);
		unlink(command->io_data.infile);
	}
	if (command->io_data.infile)
		free(command->io_data.infile);
	command->io_data.heredoc_del = 0;
	command->io_data.infile = 0;
	command->io_data.in_fd = -1;
}

int	init_parse_io(t_command *command, t_token **token, int input, t_data *data)
{
	char	**strs;

	*token = (*token)->next;
	strs = expand_var(data, (*token)->str);
	if (!strs)
		return (0);
	if (ft_strs_len(strs) > 1 || !strs[0][0])
	{
		free_str_array(strs);
		print_error(1, (*token)->str, "ambiguous redirect");
		return (0);
	}
	if (input)
	{
		free_input(command);
		command->io_data.infile = strs[0];
	}
	else
	{
		free_output(command);
		command->io_data.outfile = strs[0];
	}
	free(strs);
	return (1);
}

int	parse_input(t_command *command, t_token **token, t_data *data)
{
	if (!init_parse_io(command, token, 1, data))
		return (0);
	if (get_nbr_quotes(command->io_data.infile)
		&& !rm_quotes(&(command->io_data.infile)))
		return (0);
	command->io_data.in_fd = open(command->io_data.infile,
			O_RDONLY, 0664);
	if (command->io_data.in_fd < 0)
	{
		print_error(1, command->io_data.infile, strerror(errno));
		return (0);
	}
	return (1);
}
