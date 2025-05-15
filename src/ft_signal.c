/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:45:05 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/13 01:20:31 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	ft_isinteractive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

static void	ft_handl_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		ft_display_prompt();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ft_handl_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		g_signal = SIGQUIT;
	}
}

static void	ft_handl_sigterm(int sig)
{
	if (sig == SIGTERM)
	{
		g_signal = SIGTERM;
	}
}

static void	ft_set_signal(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(signum, &sa, NULL);
}

int	ft_setup_signals(void)
{
	if (!ft_isinteractive())
		return (FAILURE);
	ft_set_signal(SIGINT, ft_handl_sigint);
	ft_set_signal(SIGQUIT, ft_handl_sigquit);
	ft_set_signal(SIGTERM, ft_handl_sigterm);
	return (SUCCESS);
}
