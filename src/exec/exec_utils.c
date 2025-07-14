/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:10:57 by stempels          #+#    #+#             */
/*   Updated: 2025/07/14 19:15:32 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_node(t_shell *shell, t_node *tree)
{
	if (g_signal == SIGINT || g_signal == SIGQUIT)
		return (g_signal + 128);
	if (!shell)
		return (1);
	if (!tree)
		return (0);
	tree->use.fct(shell, tree);
	return (shell->status);
}

int	create_fork(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error(shell, 0, 2, "EXEC: FORK", get_errnum(N_CREAT));
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_DFL);
		return (1);
	}
	else
		shell->child_nbr++;
	return (0);
}

int	create_pipe(t_shell *shell, t_node *tree, int a, int *pipefd)
{
	if (create_fork(shell))
	{
		close(pipefd[a]);
		dup2(pipefd[(-a + 1)], -a + 1);
		close(pipefd[(-a + 1)]);
		execute_node(shell, tree);
		builtin_exit(shell, 0, NULL);
	}
	return (0);
}

int	wait_and_decrypt_child(t_shell *shell)
{
	int	status;

	status = 0;
	if (wait(&status))
	{
		if (WIFEXITED(status))
			shell->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->status = (WTERMSIG(status));
	}
	return (shell->status);
}
