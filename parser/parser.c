/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:14:03 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:14:06 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_arg_command(t_command *command, t_token *token, t_data *data)
{
	char	**args;

	args = expand_var(data, token->str);
	if (!args)
		return (0);
	if (!command->args)
	{
		command->args = malloc(sizeof(char *));
		if (!command->args)
			return (0);
		command->args[0] = 0;
	}
	command->args = add_strs_to_array(command->args, args);
	if (!command->args)
	{
		free_str_array(args);
		return (0);
	}
	free(args);
	return (1);
}

int	fill_command(t_command *command, t_token **token, t_data *data)
{
	if ((*token)->type == TRUNC)
		return (parse_trunc(command, token, data));
	else if ((*token)->type == APPEND)
		return (parse_append(command, token, data));
	else if ((*token)->type == INPUT)
		return (parse_input(command, token, data));
	else if ((*token)->type == HEREDOC)
		return (parse_heredoc(command, token, data));
	else if ((*token)->type == WORD)
		return (add_arg_command(command, *token, data));
	return (1);
}

int	create_command(t_data *data, t_token **tokens)
{
	t_command	*new;
	int			i;

	new = init_command();
	if (!new)
		return (0);
	add_command(&data->commands, new);
	while (*tokens && (*tokens)->type != PIPE && (*tokens)->type != END)
	{
		if (!fill_command(new, tokens, data))
			return (0);
		*tokens = (*tokens)->next;
	}
	i = -1;
	while (new->args && new->args[++i] && new->args[i][0])
	{
		if (get_nbr_quotes(new->args[i]) && !rm_quotes(&new->args[i]))
			return (0);
		if (!new->str)
			new->str = new->args[i];
	}
	return (1);
}

int	parser(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	while (token)
	{
		if (!create_command(data, &token))
			return (0);
		if (token)
			token = token->next;
	}
	return (1);
}
