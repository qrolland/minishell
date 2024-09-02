/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:50:46 by afelten           #+#    #+#             */
/*   Updated: 2023/04/17 14:50:51 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "cd", 3))
		return (1);
	else if (!ft_strncmp(str, "echo", 5))
		return (1);
	else if (!ft_strncmp(str, "env", 4))
		return (1);
	else if (!ft_strncmp(str, "exit", 5))
		return (1);
	else if (!ft_strncmp(str, "export", 7))
		return (1);
	else if (!ft_strncmp(str, "pwd", 4))
		return (1);
	else if (!ft_strncmp(str, "unset", 6))
		return (1);
	return (0);
}

int	is_dir(char *cmd)
{
	struct stat	cmd_stat;

	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

char	**get_path(t_data *data)
{
	char	**path;
	int		i;

	i = 0;
	path = 0;
	while (data->env[i] && ft_strncmp(data->env[i], "PATH=", 5))
		i++;
	if (data->env[i])
		path = ft_split(data->env[i] + 5, ':');
	if (!data->env[i] || !path)
		return (0);
	return (path);
}

char	*get_cmd_path(t_data *data, char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = -1;
	while (path[++i])
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (!cmd_path)
		{
			free(cmd);
			free_str_array(path);
			perror_return(data, "malloc: ");
			exit_shell(data);
		}
		if (!access(cmd_path, F_OK | X_OK) && !is_dir(cmd_path))
		{
			free(cmd);
			free_str_array(path);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(cmd);
	free_str_array(path);
	return (0);
}
