/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:29:23 by qrolland          #+#    #+#             */
/*   Updated: 2023/04/14 21:42:07 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_data *data)
{
	char	buf[4096];
	char	*pwd;

	if (data->work_dir)
	{
		ft_putendl_fd(data->work_dir, 1);
		return (0);
	}
	pwd = getcwd(buf, 4096);
	if (!pwd)
	{
		error_cmd("pwd", NULL, strerror(errno), errno);
		return (1);
	}
	ft_putendl_fd(pwd, 1);
	return (0);
}
