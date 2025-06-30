/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:22:50 by user              #+#    #+#             */
/*   Updated: 2025/06/26 14:20:05 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include "minishell.h"

volatile sig_atomic_t	g_signal;

/*
 * We should find another way to handle the prompt redisplay logic by
 * using the global variable
 */
static void	sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal != SIGINT)
			g_signal = SIGINT;
		write(STDOUT_FILENO, "\n\n", 2);
		display_prompt();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
/*
static void	sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		if (g_signal != SIGQUIT)
			g_signal = SIGQUIT;
		return ;
	}
}
*/

void	signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = &sigint;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error: sigaction");
}
