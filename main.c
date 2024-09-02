/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:13:10 by afelten           #+#    #+#             */
/*   Updated: 2023/04/17 17:35:52 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	use_input(t_data *data)
{
	if (!lexer(data))
	{
		data->status = 2;
		return ;
	}
	if (!parser(data))
	{
		data->status = 1;
		return ;
	}
	execution(data);
}

int	minishell_inter(t_data *data)
{
	while (1)
	{
		free_data(data);
		set_signals_interactive();
		data->line = readline("minishell> ");
		if (!data->line)
			exit_shell(data);
		if (!data->line[0] || check_line(data->line))
			continue ;
		set_signals_noninteractive();
		add_history(data->line);
		use_input(data);
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_data	data;

	(void)argv;
	if (!isatty(0))
		ft_error("Error: fd input not a terminal");
	if (argc > 1)
		ft_error("Error: too many arguments");
	if (!init_data(&data, env))
		return (1);
	minishell_inter(&data);
	return (0);
}
