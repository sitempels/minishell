/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:10:57 by stempels          #+#    #+#             */
/*   Updated: 2025/07/01 13:11:23 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_node(t_shell *shell, t_node *tree)
{
	int	status;

	if (!shell)
		return (1);
	if (!tree)
		return (0);
	status = tree->use.fct(shell, tree);
	shell->status = status;
	return (status);
}

int	create_fork(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error(shell, 0, 2, "EXEC: FORK", get_errnum(N_CREAT));
	if (pid == 0)
		return (1);
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
		if (execute_node(shell, tree))
			builtin_exit(shell, 0, EXIT_FAILURE);
		clean_shell(shell);
		exit(0);
	}
	return (0);
}

int	wait_and_decrypt_child(t_shell *shell)
{
	wait(&shell->status);
	if (WIFEXITED(shell->status))
		shell->status = WEXITSTATUS(shell->status);
	else if (WIFSIGNALED(shell->status))
		shell->status = (WTERMSIG(shell->status));
	return (shell->status);
}
