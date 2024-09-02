/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:12:35 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:12:39 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operator(t_data *data, int *i)
{
	int		type;
	char	*str;
	t_token	*new;

	type = is_operator(&data->line[*i]);
	if (type == APPEND || type == HEREDOC)
		str = ft_strndup(&data->line[*i], 2);
	else
		str = ft_strndup(&data->line[*i], 1);
	if (!str)
		return (0);
	new = create_token(str, type);
	if (!new)
	{
		free(str);
		return (0);
	}
	add_token(&data->tokens, new);
	if (type == APPEND || type == HEREDOC)
		*i += 1;
	*i += 1;
	return (1);
}

int	add_word(t_data *data, char *str, int len)
{
	t_token	*new;
	char	*new_str;

	new_str = ft_strndup(str, len);
	if (!new_str)
		return (0);
	new = create_token(new_str, WORD);
	if (!new)
	{
		free(new_str);
		return (0);
	}
	add_token(&data->tokens, new);
	return (1);
}

int	get_word(t_data *data, int *i)
{
	int	len;
	int	status;

	len = 0;
	status = DEFAULT;
	while (data->line[*i] && ((!is_space(data->line[*i])
				&& !is_operator(&data->line[*i])) || status))
	{
		if (data->line[*i] == '\"' || data->line[*i] == '\'')
			status = set_quote_status(status, data->line[*i]);
		len++;
		*i += 1;
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			error_msg("unexpected EOF while looking for matching", "\"", 1);
		else
			error_msg("unexpected EOF while looking for matching", "\'", 1);
		error_msg("syntax error", "unexpected end of file", 0);
		return (0);
	}
	if (!add_word(data, &data->line[*i - len], len))
		return (0);
	return (1);
}

int	lexer(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (is_space(data->line[i]))
			i++;
		else if (is_operator(&data->line[i]))
		{
			if (!get_operator(data, &i) || check_syntax(data, 0))
				return (0);
		}
		else
			if (!get_word(data, &i))
				return (0);
	}
	if (!data->tokens || check_syntax(data, 1))
		return (0);
	return (1);
}
