/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:14:20 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:14:24 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_new_word_size(t_data *data, char *str, int heredoc)
{
	int	i;
	int	size;
	int	quotes;

	i = 0;
	size = 0;
	quotes = DEFAULT;
	while (str[i])
	{
		quotes = set_quote_status(quotes, str[i]);
		if (is_env_var(&str[i]) && (quotes != SQUOTE || heredoc == DEFAULT))
		{
			i++;
			size += get_var_size(data, &str[i]);
			if (str[i] == '?')
				i++;
			else
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
			continue ;
		}
		i++;
		size++;
	}
	return (size);
}

static int	check_var(char *str, int heredoc)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = DEFAULT;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quotes = set_quote_status(quotes, str[i]);
		else if (is_env_var(&str[i])
			&& (quotes != SQUOTE || heredoc == DEFAULT))
			return (1);
		i++;
	}
	return (0);
}

int	copy_var_env(char *str, char *var, int *i)
{
	int	j;

	j = 0;
	if (!var)
		return (0);
	while (var[j])
	{
		str[*i] = var[j];
		*i += 1;
		j++;
	}
	free(var);
	return (1);
}

int	fill_newstr(char *newstr, char *str, t_data *data, int heredoc)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	j = 0;
	quotes = DEFAULT;
	while (str[i])
	{
		quotes = set_quote_status(quotes, str[i]);
		if (is_env_var(&str[i]) && (quotes != SQUOTE || heredoc == DEFAULT))
		{
			if (!copy_var_env(newstr, get_var_env(data, &str[++i]), &j))
				return (0);
			if (str[i] == '?')
				i++;
			else
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
			continue ;
		}
		newstr[j++] = str[i++];
	}
	newstr[j] = 0;
	return (1);
}

int	replace_var_heredoc(char **str, int heredoc, t_data *data)
{
	char	*newstr;

	if (heredoc > DEFAULT || !check_var(*str, heredoc))
		return (1);
	newstr = malloc((get_new_word_size(data, *str, heredoc) + 1)
			* sizeof(char));
	if (!newstr)
		return (0);
	if (!fill_newstr(newstr, *str, data, heredoc))
	{
		free(newstr);
		return (0);
	}
	free(*str);
	*str = newstr;
	return (1);
}
