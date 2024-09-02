/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:49:42 by afelten           #+#    #+#             */
/*   Updated: 2023/04/17 14:49:47 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_var(t_exp_var *values, char *str, int len_var);

static int	check_var(char *str, t_exp_var *values)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			values->status = set_quote_status(values->status, str[i]);
		else if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?') && values->status != SQUOTE)
			return (1);
		i++;
	}
	return (0);
}

void	get_index_var(char *str, t_exp_var *values)
{
	int	i;
	int	status;

	status = values->status;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			status = set_quote_status(status, str[i]);
		else if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?') && values->status != SQUOTE)
		{
			values->start = i + values->pos;
			i += 2;
			if (str[i - 1] != '?')
				while (ft_isalnum(str[i]))
					i++;
			values->end = i + values->pos;
			return ;
		}
		i++;
	}
	values->start = 0;
	values->end = 0;
}

int	replace_var(char **str, char *var, int start, int end)
{
	char	*newstr;
	int		i[3];

	newstr = malloc(sizeof(char) * (ft_strlen(*str)
				- (start - end) + ft_strlen(var)));
	if (!newstr)
		return (!free_return(*str) && free_return(var));
	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	while (++i[0] < start && (*str)[i[0]])
		newstr[++i[1]] = (*str)[i[0]];
	while (var[++i[2]])
		newstr[++i[1]] = var[i[2]];
	i[0] = end - 1;
	while ((*str)[++i[0]])
		newstr[++i[1]] = (*str)[i[0]];
	newstr[i[1] + 1] = 0;
	free(*str);
	*str = newstr;
	free(var);
	return (1);
}

char	**replace_first_var(t_exp_var *values)
{
	char	*var;
	int		len_var;
	int		len_args;

	len_args = ft_strs_len(values->args);
	get_index_var(values->args[len_args - 1] + values->pos, values);
	var = get_var_env(values->data,
			values->args[len_args - 1] + values->start + 1);
	if (!var)
		return (0);
	len_var = ft_strlen(var);
	if (!replace_var(&values->args[len_args - 1],
			var, values->start, values->end))
		return (0);
	if (values->status == DQUOTE || !values->args[len_args - 1][0])
	{
		values->pos = values->start + len_var;
		return (values->args);
	}
	var = values->args[len_args - 1];
	values->args[len_args - 1] = 0;
	if (!split_var(values, var, len_var))
		return (0);
	return (values->args);
}

char	**expand_var(t_data *data, char *str)
{
	t_exp_var	values;

	values.data = data;
	values.args = malloc(sizeof(char *) * 2);
	if (!values.args)
		return (0);
	values.args[0] = ft_strdup(str);
	values.args[1] = 0;
	if (!values.args[0])
	{
		free(values.args);
		return (0);
	}
	values.pos = 0;
	values.status = DEFAULT;
	while (check_var(values.args[ft_strs_len(values.args) - 1] + values.pos,
			&values))
	{
		values.args = replace_first_var(&values);
		if (!values.args)
			return (0);
	}
	return (values.args);
}
