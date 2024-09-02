/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:47:51 by afelten           #+#    #+#             */
/*   Updated: 2023/04/17 14:48:01 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_print_nl(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
}

void	signal_print_nl_quit(int signal)
{
	(void)signal;
	write(1, "Quit\n", 5);
	rl_on_new_line();
}

void	signal_rl_reset(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_interactive(void)
{
	struct sigaction	act_c;
	struct sigaction	act_slash;

	ft_memset(&act_c, 0, sizeof(struct sigaction));
	ft_memset(&act_slash, 0, sizeof(struct sigaction));
	act_c.sa_handler = &signal_rl_reset;
	act_slash.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act_c, 0);
	sigaction(SIGQUIT, &act_slash, 0);
}

void	set_signals_noninteractive(void)
{
	struct sigaction	act_c;
	struct sigaction	act_slash;

	ft_memset(&act_c, 0, sizeof(struct sigaction));
	ft_memset(&act_slash, 0, sizeof(struct sigaction));
	act_c.sa_handler = &signal_print_nl;
	act_slash.sa_handler = signal_print_nl_quit;
	sigaction(SIGINT, &act_c, 0);
	sigaction(SIGQUIT, &act_slash, 0);
}
