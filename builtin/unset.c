/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:29:26 by qrolland          #+#    #+#             */
/*   Updated: 2023/04/14 21:41:59 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_data *data, char **strs)
{
	int	i;
	int	index;

	i = 1;
	while (strs[i])
	{
		if (!check_env_var(strs[i]) || ft_strchr(strs[i], '='))
		{
			error_cmd("unset", strs[i], "not a valid identifier", 0);
			return (1);
		}
		else
		{
			index = get_env_var_index(data->env, strs[i]);
			if (index != -1)
				delete_env_var(data, index);
		}
		i++;
	}
	return (0);
}
