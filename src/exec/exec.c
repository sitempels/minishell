/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:57:50 by stempels          #+#    #+#             */
/*   Updated: 2025/06/16 14:19:10 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_node *tree, char **env)
{
	int		status;
	pid_t	pid;

	dup2(STDIN_FILENO, 0);
	dup2(STDOUT_FILENO, 1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		execute_descend(tree, env);
		return (1);
	}
	waitpid(pid, &status, 0);
	printf("Program exited with %d\n", status);
	return (status);
}

int	execute_descend(t_node *tree, char **env)
{
	if (!tree)
		return (1);
	if (tree->use.fct(tree, env))
		return (1);
	return (0);
}

int	execute_and_or_if(t_node *tree, char **env)
{
	int	status;

	status = execute(tree->left, env);
	if (status == 0 && tree->type == AND_IF)
		execute_descend(tree->right, env);
	if (status == 256 && tree->type == OR_IF)
		execute_descend(tree->right, env);
	return (1);
}

int	execute_subshell(t_node *tree, char **env)
{
	int	status;

	status = 1;
	if (tree->left)
		execute_descend(tree->left, env);
	if (tree->right)
		status = execute(tree->right, env);
	return (status);
}

int	execute_pipe(t_node *tree, char **env)
{
	int		pipefd[2];
	int		child_nbr;
	int		status;
	pid_t	pid;

	// pid_t	pid2;
	child_nbr = 0;
	if (pipe(pipefd) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execute_descend(tree->left, env);
		exit (1);
	}
	child_nbr++;
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE); //-->handle of other child needed
	if (pid == 0)
	{
		execute_descend(tree->right, env);
		exit (1);
	}
	child_nbr++;
	while (child_nbr > 0)
	{
		wait(&status);
		child_nbr--;
	}
	return (status);
}
