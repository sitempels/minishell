/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:10:57 by stempels          #+#    #+#             */
/*   Updated: 2025/08/06 15:27:30 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_node(t_shell *shell, t_node *tree)
{
	if (g_signal != 0)
		return (shell->status);
	if (!shell)
		return (1);
	if (!tree)
		return (0);
	shell->status = tree->use.fct(shell, tree);
	if (g_signal != 0)
		shell->status = g_signal + 128;
	return (shell->status);
}

int	execute_subshell(t_shell *shell, t_node *tree)
{
	if (execute_node(shell, tree->left))
		return (1);
	if (create_fork(shell))
	{
		shell->std_io[0] = ttyname(STDOUT_FILENO);
		shell->std_io[1] = ttyname(STDIN_FILENO);
		if (update_envint(shell->env, "SHLVL", 1))
			return (1);
		execute_node(shell, tree->right);
		clean_shell(shell);
		if (update_envint(shell->env, "SHLVL", -1))
			return (1);
		builtin_exit(shell, 1, NULL);
	}
	wait_and_decrypt_child(shell, 0);
	return (shell->status);
}

pid_t	create_fork(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error(shell, 0, 2, "EXEC: FORK", get_errnum(N_CREAT));
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		shell->child_nbr = 1;
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		shell->child_nbr = 0;
	}
	return (pid);
}

pid_t	create_pipe(t_shell *shell, t_node *tree, int a, int *pipefd)
{
	pid_t	pid;

	pid = create_fork(shell);
	if (pid == 0)
	{
		close(pipefd[a]);
		dup2(pipefd[(-a + 1)], -a + 1);
		close(pipefd[(-a + 1)]);
		execute_node(shell, tree);
		builtin_exit(shell, 1, NULL);
	}
	return (pid);
}

int	wait_and_decrypt_child(t_shell *shell, pid_t pid)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0))
	{
		if (WIFEXITED(status))
		{
			shell->status = WEXITSTATUS(status);
			if (shell->status > 128)
				g_signal = shell->status - 128;
		}
		else if (WIFSIGNALED(status))
		{
			g_signal = WTERMSIG(status);
			if (g_signal == SIGINT)
				write(STDIN_FILENO, "\n", 1);
			shell->status = 128 + g_signal;
		}
	}
	return (shell->status);
}
