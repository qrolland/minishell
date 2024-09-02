/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:28:28 by qrolland          #+#    #+#             */
/*   Updated: 2023/04/14 21:28:29 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	check_env_var(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	get_env_var_index(char **env, char *var)
{
	int		i;
	char	*search;

	search = ft_strjoin(var, "=");
	if (!search)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(search, env[i], ft_strlen(search)))
		{
			free_str(search);
			return (i);
		}
		i++;
	}
	free_str(search);
	return (-1);
}

char	*get_env_var_value(char **env, char *str)
{
	int		i;
	char	*join;

	join = ft_strjoin(str, "=");
	if (!join)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(join, env[i], ft_strlen(join)) == 0)
		{
			free_str(join);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_str(join);
	return (NULL);
}
