/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:42:06 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 15:42:12 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nbr_quotes(char *str)
{
	int	i;
	int	nbr_quotes;
	int	status;
	int	save;

	i = 0;
	nbr_quotes = 0;
	status = DEFAULT;
	while (str[i])
	{
		save = status;
		if (str[i] == '\'' || str[i] == '\"')
			status = set_quote_status(status, str[i]);
		if (save != status)
			nbr_quotes++;
		i++;
	}
	return (nbr_quotes);
}

int	rm_quotes(char **str)
{
	char	*newstr;
	int		i;
	int		j;
	int		status;
	int		save;

	i = -1;
	j = -1;
	status = DEFAULT;
	newstr = malloc((ft_strlen(*str) - get_nbr_quotes(*str) + 1)
			* sizeof(char));
	if (!newstr)
		return (0);
	while ((*str)[++i])
	{
		save = status;
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
			status = set_quote_status(status, (*str)[i]);
		if (save == status)
			newstr[++j] = (*str)[i];
	}
	newstr[++j] = 0;
	free(*str);
	*str = newstr;
	return (1);
}
