/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:50:26 by afelten           #+#    #+#             */
/*   Updated: 2023/04/17 14:50:34 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size_spt(char *str, t_exp_var *values)
{
	int	size;
	int	i;

	size = 0;
	i = -1;
	if (str[0])
	{
		size++;
		i = values->start - 1;
	}
	while (str[++i] && i < values->start + values->end - 1)
	{
		if (str[i] == ' ' && str[i + 1] && str[i + 1] != ' ')
			size++;
	}
	if (str[i])
		size++;
	i = -1;
	while (values->args[++i])
		size++;
	return (size);
}

static int	free_var_split(char **args, char **newargs, char *str)
{
	if (!newargs && args)
		free_str_array(args);
	if (newargs)
	{
		free_str_array(newargs);
		free(args);
	}
	if (str)
		free(str);
	return (0);
}

static int	len_until_space(char *str, int i, int len_var, t_exp_var *values)
{
	int	len;

	len = 0;
	while (str[i] && (str[i] != ' ' || i < values->start
			|| i >= values->start + len_var))
	{
		len++;
		if (i < values->start + len_var)
			values->pos += 1;
		i++;
	}
	return (len);
}

static char	*copy_until_space(char *str, int *i, int len_var, t_exp_var *values)
{
	int	len;

	values->pos = 0;
	if (*i < values->start)
	{
		len = len_until_space(str, 0, len_var, values);
		*i = len - 1;
		return (ft_strndup(str, len));
	}
	else
	{
		len = len_until_space(str, *i, len_var, values);
		*i += len - 1;
		return (ft_strndup(str + *i - len + 1, len));
	}
}

int	split_var(t_exp_var *values, char *str, int len_var)
{
	int		i;
	int		j;
	char	**newargs;

	newargs = ft_calloc(get_size_spt(str, values) + 1, sizeof(char *));
	if (!newargs)
		return (free_var_split(values->args, 0, str));
	i = -1;
	j = -1;
	while ((values->args)[++i])
		newargs[++j] = (values->args)[i];
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && i < values->start + len_var)
		{
			newargs[++j] = copy_until_space(str, &i, len_var, values);
			if (!newargs[j])
				return (free_var_split(values->args, newargs, str));
		}
	}
	free(str);
	free(values->args);
	values->args = newargs;
	return (1);
}
