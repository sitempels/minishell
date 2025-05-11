/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:45:05 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 19:42:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	ft_isinteractive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

static void	ft_handl_sigint(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		ft_display_prompt();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ft_handl_sigquit(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGQUIT)
	{
		g_signal = SIGQUIT;
		exit(1);
	}
}

static void	ft_handl_sigeof(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGTERM)
	{
		g_signal = SIGTERM;
	}
}

int	ft_setup_signals(void)
{
	struct sigaction	sa;

	if (!ft_isinteractive())
		return (FAILURE);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handl_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_sigaction = ft_handl_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_sigaction = ft_handl_sigeof;
	sigaction(SIGTERM, &sa, NULL);
	return (SUCCESS);
}
