/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:57:50 by stempels          #+#    #+#             */
/*   Updated: 2025/06/20 15:26:16 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	create_fork(int *child_nbr, t_shell *shell, int *pipefd);

int	execute(t_shell *shell, t_node *tree, char **env)
{
	execute_descend(shell, tree, env);
	return (0);
}

int	execute_descend(t_shell *shell, t_node *tree, char **env)
{
	if (!tree)
		return (1);
	if (tree->use.fct(shell, tree, env))
		return (1);
	return (0);
}

int	execute_and_or_if(t_shell *shell, t_node *tree, char **env)
{
	int	status;

	status = execute(shell, tree->left, env);
	if (status == 0 && tree->type == AND_IF)
		execute_descend(shell, tree->right, env);
	if (status == 256 && tree->type == OR_IF)
		execute_descend(shell, tree->right, env);
	return (1);
}

int	execute_subshell(t_shell *shell, t_node *tree, char **env)
{
	int	status;

	status = 1;
	if (tree->left)
		execute_descend(shell, tree->left, env);
	if (tree->right)
		status = execute(shell, tree->right, env);
	return (status);
}

int	execute_pipe(t_shell *shell, t_node *tree, char **env)
{
	int		pipefd[2];
	int		child_nbr;
	int		status;
	pid_t	pid;

	child_nbr = 0;
	if (pipe(pipefd) == -1)
		ft_error(shell, 2, "EXEC: PIPE", get_errnum(N_CREAT));
	pid = create_fork(&child_nbr, shell, pipefd);
	if (pid == 0)
		execute_descend(shell, tree->left, env);
	pid = create_fork(&child_nbr, shell, pipefd);
	if (pid == 0)
		execute_descend(shell, tree->right, env);
	while (child_nbr > 0)
	{
		wait(&status);
		child_nbr--;
	}
	return (status);
}

static pid_t	create_fork(int *child_nbr, t_shell *shell, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error(shell, 2, "EXEC: PIPE", get_errnum(N_CREAT));
	if (pid == 0 && *child_nbr == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	else if (pid == 0 && *child_nbr == 1)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	else
		(*child_nbr)++;
	return (pid);
}
