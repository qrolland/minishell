/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:28:28 by qrolland          #+#    #+#             */
/*   Updated: 2023/04/14 21:28:29 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**realloc_env(t_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	new_env[size] = NULL;
	i = 0;
	while (data->env[i] && i < size)
	{
		new_env[i] = ft_strdup(data->env[i]);
		free_str(data->env[i]);
		i++;
	}
	free(data->env);
	return (new_env);
}

int	delete_env_var(t_data *data, int i)
{
	if (i > env_var_count(data->env))
		return (0);
	free_str(data->env[i]);
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_str(data->env[i + 1]);
		i++;
	}
	data->env = realloc_env(data, i);
	if (!data->env)
		return (0);
	return (1);
}

int	add_env_var(t_data *data, char *key, char *value)
{
	int		i;
	char	*equal;

	i = get_env_var_index(data->env, key);
	if (value == NULL)
		value = "";
	equal = ft_strjoin("=", value);
	if (!equal)
		return (0);
	if (i != -1 && data->env[i])
	{
		free_str(data->env[i]);
		data->env[i] = ft_strjoin(key, equal);
	}
	else
	{
		i = env_var_count(data->env);
		data->env = realloc_env(data, i + 1);
		if (!data->env)
			return (0);
		data->env[i] = ft_strjoin(key, equal);
	}
	free_str(equal);
	return (1);
}
