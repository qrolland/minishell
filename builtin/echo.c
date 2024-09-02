/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:28:38 by qrolland          #+#    #+#             */
/*   Updated: 2023/04/14 21:28:39 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(char **strs)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (strs[i] && !ft_strncmp(strs[i], "-n", ft_strlen(strs[i])))
	{
		n_flag = 1;
		i++;
	}
	if (!strs[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', 1);
	}
	while (strs[i])
	{
		ft_putstr_fd(strs[i], 1);
		if (strs[i + 1])
			ft_putchar_fd(' ', 1);
		else if (!strs[i + 1] && !n_flag)
			ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
