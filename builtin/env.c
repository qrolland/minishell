/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:28:41 by qrolland          #+#    #+#             */
/*   Updated: 2023/04/14 21:42:25 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_data *data, char **strs, int export)
{
	int	i;

	if (strs && strs[1])
		return (error_cmd("env", NULL, "too many arguments", 2));
	i = -1;
	if (!data->env)
		return (1);
	while (data->env[++i])
	{
		if (export)
			ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(data->env[i], 1);
	}
	return (0);
}
