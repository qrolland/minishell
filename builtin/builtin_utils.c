/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:28:17 by qrolland          #+#    #+#             */
/*   Updated: 2023/04/14 21:41:47 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

char	*join_free_str(char *s1, char *s2)
{
	char	*dest;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	dest = ft_strjoin(s1, s2);
	free_str(s1);
	return (dest);
}

static int	check_for_quotes(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0)
		return (1);
	return (0);
}

int	error_cmd(char *command, char *detail, char *error, int nb)
{
	char	*msg;
	int		quotes;

	quotes = check_for_quotes(command);
	msg = ft_strdup("minishell: ");
	if (command)
	{
		msg = join_free_str(msg, command);
		msg = join_free_str(msg, ": ");
	}
	if (detail)
	{
		if (quotes)
			msg = join_free_str(msg, "`");
		msg = join_free_str(msg, detail);
		if (quotes)
			msg = join_free_str(msg, "'");
		msg = join_free_str(msg, ": ");
	}
	msg = join_free_str(msg, error);
	ft_putendl_fd(msg, 2);
	free_str(msg);
	return (nb);
}
