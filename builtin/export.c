/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:29:20 by qrolland          #+#    #+#             */
/*   Updated: 2023/04/17 17:11:41 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_env_value(char *str)
{
	char	**env;
	char	*equal;

	equal = ft_strchr(str, '=');
	env = malloc(sizeof(char *) * 3);
	env[0] = ft_substr(str, 0, equal - str);
	env[1] = ft_substr(equal, 1, ft_strlen(equal));
	env[2] = NULL;
	return (env);
}

int	export_builtin(t_data *data, char **strs)
{
	int		i;
	char	**env;

	i = 1;
	if (!strs[i])
		return (env_builtin(data, NULL, 1));
	while (strs[i])
	{
		if (!check_env_var(strs[i]))
		{
			error_cmd("export", strs[i], "not a valid identifier", 1);
			return (1);
		}
		else if (ft_strchr(strs[i], '=') != NULL)
		{
			env = split_env_value(strs[i]);
			add_env_var(data, env[0], env[1]);
			ft_free_strs(env);
		}
		i++;
	}
	return (0);
}
