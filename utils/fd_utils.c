/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:48:14 by afelten           #+#    #+#             */
/*   Updated: 2023/04/17 14:48:22 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes(t_command *commands, t_data *data)
{
	int	pipefd[2];

	while (commands)
	{
		if (commands->next)
		{
			if (pipe(pipefd))
				return (perror_return(data, "pipe: "));
			commands->pipe_fd[1] = pipefd[1];
			commands->next->pipe_fd[0] = pipefd[0];
		}
		commands = commands->next;
	}
	return (1);
}

void	close_pipes(t_command *commands, t_command *cmd)
{
	while (commands)
	{
		if (commands != cmd)
		{
			if (commands->pipe_fd[0] != -1)
				close(commands->pipe_fd[0]);
			if (commands->pipe_fd[1] != -1)
				close(commands->pipe_fd[1]);
			commands->pipe_fd[0] = -1;
			commands->pipe_fd[1] = -1;
		}
		commands = commands->next;
	}
}

int	redirect_io(t_command *command, t_data *data)
{
	int	fd_in;
	int	fd_out;

	fd_in = -1;
	fd_out = -1;
	if (command->io_data.infile)
		fd_in = command->io_data.in_fd;
	else if (command->pipe_fd[0] != -1)
		fd_in = command->pipe_fd[0];
	if (command->io_data.outfile)
		fd_out = command->io_data.out_fd;
	else if (command->pipe_fd[1] != -1)
		fd_out = command->pipe_fd[1];
	if (fd_in != -1)
		if (dup2(fd_in, 0) == -1)
			return (perror_return(data, "dup2: "));
	if (fd_out != -1)
		if (dup2(fd_out, 1) == -1)
			return (perror_return(data, "dup2: "));
	return (1);
}
