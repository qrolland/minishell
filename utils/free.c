/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:12:01 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:12:05 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_array(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
}

void	free_commands(t_command *commands)
{
	t_command	*temp;

	while (commands)
	{
		temp = commands->next;
		if (commands->args)
			free_str_array(commands->args);
		if (commands->pipe_fd[0] != -1)
			close(commands->pipe_fd[0]);
		if (commands->pipe_fd[1] != -1)
			close(commands->pipe_fd[1]);
		free_input(commands);
		free_output(commands);
		free(commands);
		commands = temp;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		if (tokens->str)
			free(tokens->str);
		free(tokens);
		tokens = temp;
	}
}

void	free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->commands)
		free_commands(data->commands);
	data->line = 0;
	data->tokens = 0;
	data->commands = 0;
}

void	exit_shell(t_data *data)
{
	int	status;

	status = data->status;
	free_data(data);
	if (data->env)
		free_str_array(data->env);
	rl_clear_history();
	exit(status);
}
