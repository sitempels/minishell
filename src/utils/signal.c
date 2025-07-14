/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:22:50 by user              #+#    #+#             */
/*   Updated: 2025/07/14 09:15:21 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		g_signal = SIGQUIT;
		if (rl_end > 0)
		{
			write(STDOUT_FILENO, "Quit (core dumped)", 18);
			write(STDOUT_FILENO, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
		}
	}
}

void	handle_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		rl_replace_line("", 0);
		rl_on_new_line();
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
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
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = handle_sigquit;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction(SIGQUIT)");
}
