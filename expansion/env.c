/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:43:52 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:43:56 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_env(t_data *data, char *var)
{
	int		i;
	int		j;
	char	*val;

	if (var[0] && var[0] == '?')
		return (ft_itoa(data->status));
	j = 0;
	while (data->env[j])
	{
		i = 0;
		while (data->env[j] && data->env[j][i] && data->env[j][i] != '=')
			i++;
		if (!ft_strncmp(data->env[j], var, i) && (!var[i]
				|| (!ft_isalnum(var[i]) && var[i] != '_')))
		{
			val = ft_strdup(data->env[j] + i + 1);
			if (!val)
				return (0);
			return (val);
		}
		j++;
	}
	return (ft_strdup(""));
}

static int	get_int_size(int nbr)
{
	int	size;

	size = 0;
	if (!nbr)
		return (1);
	while (nbr)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

int	get_var_size(t_data *data, char *var)
{
	int		i;
	int		j;
	int		size;

	size = 0;
	if (var[0] && var[0] == '?')
		return (get_int_size(data->status));
	j = 0;
	while (data->env[j])
	{
		i = 0;
		while (data->env[j] && data->env[j][i] && data->env[j][i] != '=')
			i++;
		if (!ft_strncmp(data->env[j], var, i) && (!var[i]
				|| (!ft_isalnum(var[i]) && var[i] != '_')))
		{
			while (*(data->env[j] + i + 1 + size))
				size++;
			return (size);
		}
		j++;
	}
	return (0);
}
