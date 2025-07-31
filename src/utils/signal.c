/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:22:50 by user              #+#    #+#             */
/*   Updated: 2025/07/31 07:28:18 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigpipe(int sig);

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		rl_replace_line("", 0);
		rl_on_new_line();
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n") < 0)
			perror("minishell: ioctl failed");
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		g_signal = SIGQUIT;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

static void	handle_sigpipe(int sig)
{
	g_signal = sig;
}

void	signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = handle_sigint;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("sigaction(SIGINT)");
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction(SIGQUIT)");
	signal(SIGPIPE, handle_sigpipe);
}
