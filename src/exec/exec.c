/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:57:50 by stempels          #+#    #+#             */
/*   Updated: 2025/06/11 07:32:52 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_node *tree, char **env)
{
	int		status;
	pid_t	pid;

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
	free(tree);
	tree = NULL;
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
	pid_t	pid;

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
		return (1);
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	execute_descend(tree->right, env);
	return (0);
}

char	**free_array(char **array, int pos)
{
	if (!array)
		return (NULL);
	while (array[pos])
	{
		if (array[pos])
		{
			free(array[pos]);
			array[pos] = NULL;
		}
		pos++;
	}
	return (NULL);
}
