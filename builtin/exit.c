/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:29:07 by qrolland          #+#    #+#             */
/*   Updated: 2023/04/17 17:32:02 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long int	atol_exit(const char *nptr, int *too_big)
{
	int						sign;
	unsigned long long int	num;

	sign = 1;
	num = 0;
	while ((*nptr == ' ') || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + (*nptr - '0');
		if ((sign == 1 && num > LONG_MAX)
			|| (sign == -1 && num > -(unsigned long)LONG_MIN))
		{
			*too_big = 1;
			break ;
		}
		nptr++;
	}
	return (num * sign);
}

int	check_str_numeric(char *str)
{
	int		i;

	i = 0;
	while ((str[i] == ' ') || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!((str[i] == ' ') || (str[i] >= '\t' && str[i] <= '\r'))
			&& !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_exit_alone(t_data *data)
{
	t_command	*cmd;

	cmd = data->commands;
	if (!cmd)
		return (1);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (0);
	return (1);
}

int	exit_builtin(t_data *data, char **strs)
{
	int		too_big;
	int		alone;

	alone = check_exit_alone(data);
	too_big = 0;
	if (alone)
		ft_putendl_fd("exit", 2);
	if (strs && strs[1])
	{
		data->status = atol_exit(strs[1], &too_big) % 256;
		if (too_big || !check_str_numeric(strs[1]))
			data->status = error_cmd("exit", strs[1],
					"numeric argument required", 2);
		else if (strs[2])
		{
			return (error_cmd("exit", NULL, "too many arguments", 1));
		}
	}
	exit_shell(data);
	return (2);
}
