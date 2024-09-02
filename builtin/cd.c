/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:28:35 by qrolland          #+#    #+#             */
/*   Updated: 2023/04/14 21:43:04 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_dir(t_data *data, char *str)
{
	add_env_var(data, "OLDPWD", get_env_var_value(data->env, "PWD"));
	add_env_var(data, "PWD", str);
	if (data->old_work_dir)
	{
		free_str(data->old_work_dir);
		data->old_work_dir = ft_strdup(data->work_dir);
	}
	if (data->work_dir)
	{
		free_str(data->work_dir);
		data->work_dir = ft_strdup(str);
	}
	free_str(str);
}

/*chdir can sometimes set errno to ESTALE ("Stale file handle") when a parent
directory is removed on some systems. This is due to the inode table entry
being recycled. This is a fix to display "no such file or directory"
error instead.*/
static int	change_dir(t_data *data, char *path)
{
	char	*new_wd;
	char	*join;
	char	cwd[4096];

	new_wd = NULL;
	if (chdir(path) != 0)
	{
		if (errno == ESTALE)
			errno = ENOENT;
		return (error_cmd("cd", path, strerror(errno), 0));
	}
	new_wd = getcwd(cwd, 4096);
	if (!new_wd)
	{
		error_cmd("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		join = ft_strjoin(data->work_dir, "/");
		new_wd = ft_strjoin(join, path);
		free_str(join);
	}
	else
		new_wd = ft_strdup(cwd);
	update_dir(data, new_wd);
	return (1);
}

int	cd_builtin(t_data *data, char **strs)
{
	char	*path;

	if (strs[1] && strs[2])
		return (error_cmd("cd", NULL, "too many arguments", 1));
	if (!strs[1] || (strs[1][0] == ' ') || (strs[1][0] >= '\t'
		&& strs[1][0] <= '\r') || ft_strncmp(strs[1], "--", 3) == 0)
	{
		path = get_env_var_value(data->env, "HOME");
		if (!path)
			return (error_cmd("cd", NULL, "HOME not set", 1));
		return (!change_dir(data, path));
	}
	if (ft_strncmp(strs[1], "-", 2) == 0)
	{
		path = get_env_var_value(data->env, "OLDPWD");
		if (!path)
			return (error_cmd("cd", NULL, "OLDPWD not set", 1));
		return (!change_dir(data, path));
	}
	return (!change_dir(data, strs[1]));
}
