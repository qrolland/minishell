/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:51:00 by afelten           #+#    #+#             */
/*   Updated: 2023/04/17 14:51:04 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_data *data, t_command *command)
{
	if (!ft_strncmp(command->str, "cd", 3))
		return (cd_builtin(data, command->args));
	else if (!ft_strncmp(command->str, "echo", 5))
		return (echo_builtin(command->args));
	else if (!ft_strncmp(command->str, "env", 4))
		return (env_builtin(data, command->args, 0));
	else if (!ft_strncmp(command->str, "exit", 5))
		return (exit_builtin(data, command->args));
	else if (!ft_strncmp(command->str, "export", 7))
		return (export_builtin(data, command->args));
	else if (!ft_strncmp(command->str, "pwd", 4))
		return (pwd_builtin(data));
	else if (!ft_strncmp(command->str, "unset", 6))
		return (unset_builtin(data, command->args));
	return (data->status);
}

int	execute_env_cmd(t_data *data, t_command *command)
{
	char	**path;
	char	*cmd;

	cmd = ft_strjoin("/", command->str);
	if (!cmd)
		return (perror_return(data, "malloc: "));
	path = get_path(data);
	if (!path)
	{
		free(cmd);
		return (1);
	}
	cmd = get_cmd_path(data, path, cmd);
	if (!cmd)
		return (1);
	execve(cmd, command->args, data->env);
	free(cmd);
	return (perror_cmd_return(data, command->str));
}

int	execute_local_cmd(t_data *data, t_command *command)
{
	if (command->str[0] != '/' && ft_strncmp(command->str, "./", 2))
	{
		data->status = 127;
		return (print_error(0, command->str, "command not found"));
	}
	else if (access(command->str, F_OK))
		return (perror_cmd_return(data, command->str));
	else if (is_dir(command->str))
	{
		data->status = 126;
		return (print_error(1, command->str, "Is a directory"));
	}
	else if (access(command->str, F_OK | X_OK))
		return (perror_cmd_return(data, command->str));
	execve(command->str, command->args, data->env);
	return (perror_cmd_return(data, command->str));
}
