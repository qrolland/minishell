/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:35:44 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 17:35:46 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (0);
	command->str = 0;
	command->args = 0;
	command->pipe_fd[0] = -1;
	command->pipe_fd[1] = -1;
	command->prev = 0;
	command->next = 0;
	command->io_data.infile = 0;
	command->io_data.outfile = 0;
	command->io_data.heredoc_del = 0;
	command->io_data.in_fd = -1;
	command->io_data.out_fd = -1;
	return (command);
}

void	add_command(t_command **commands, t_command *new)
{
	t_command	*list;

	list = *commands;
	while (list && list->next)
		list = list->next;
	if (!list)
		*commands = new;
	else
	{
		list->next = new;
		new->prev = list;
	}
}

char	**add_str_arr(char **strs, char *str)
{
	int		i;
	char	**newstrs;

	i = 0;
	while (strs[i])
		i++;
	newstrs = malloc(sizeof(char *) * (i + 2));
	if (!newstrs)
		return (0);
	i = -1;
	while (strs[++i])
		newstrs[i] = strs[i];
	newstrs[i] = str;
	newstrs[i + 1] = 0;
	free(strs);
	return (newstrs);
}

char	**add_strs_to_array(char **strs1, char **strs2)
{
	char	**newstrs;
	int		i;
	int		j;

	newstrs = malloc(sizeof(char *)
			* (ft_strs_len(strs1) + ft_strs_len(strs2) + 1));
	if (!newstrs)
	{
		free_str_array(strs1);
		return (0);
	}
	i = -1;
	j = -1;
	while (strs1[++i])
		newstrs[++j] = strs1[i];
	i = -1;
	while (strs2[++i])
		newstrs[++j] = strs2[i];
	newstrs[j + 1] = 0;
	free(strs1);
	return (newstrs);
}
