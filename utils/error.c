/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:11:50 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:11:54 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *msg, char *token, int quoting)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	if (quoting)
		ft_putstr_fd(" `", 2);
	else
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(token, 2);
	if (quoting)
		ft_putstr_fd("\'", 2);
	ft_putstr_fd("\n", 2);
}

int	perror_return(t_data *data, char *str)
{
	data->status = errno;
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	return (0);
}

int	perror_cmd_return(t_data *data, char *str)
{
	data->status = errno;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (0);
}

int	print_error(int start, char *cmd, char *str)
{
	if (start)
		ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}
