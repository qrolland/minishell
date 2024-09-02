/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:47:27 by afelten           #+#    #+#             */
/*   Updated: 2023/04/17 14:47:36 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	if (!env || !env[0])
		return (0);
	while (env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		return (0);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (0);
		i++;
	}
	data->env[i] = 0;
	return (1);
}

int	init_data(t_data *data, char **env)
{
	data->env = 0;
	if (!copy_env(data, env))
	{
		free_str_array(data->env);
		ft_putstr_fd("minishell: Environment initialisation unsuccessful\n",
			2);
		return (0);
	}
	data->work_dir = 0;
	data->old_work_dir = 0;
	data->line = 0;
	data->status = 0;
	data->tokens = 0;
	data->commands = 0;
	return (1);
}
