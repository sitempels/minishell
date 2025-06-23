/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:57:50 by stempels          #+#    #+#             */
/*   Updated: 2025/06/23 09:20:58 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_and_or_if(t_shell *shell, t_node *tree, char **env)
{
	int	status;
	pid_t	pid;

	if (create_fork(shell, &pid))
		execute_node(shell, tree->left, env);
	waitpid(pid, &status, 0);
	if (status == 0 && tree->type == AND_IF)
		execute_node(shell, tree->right, env);
	if (status == 256 && tree->type == OR_IF)
		execute_node(shell, tree->right, env);
	return (1);
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
	if (create_pipe(&child_nbr, shell, pipefd, &pid))
		execute_node(shell, tree->left, env);
	if (create_pipe(&child_nbr, shell, pipefd, &pid))
		execute_node(shell, tree->right, env);
	close(pipefd[0]);
	close(pipefd[1]);
	while (child_nbr > 0)
	{
		wait(&status);
		child_nbr--;
	}
	return (status);
}

int	execute_cmd(t_shell *shell, t_node *tree, char **env)
{
	char	*path;
	char	**argv;

	if (tree->left)
		execute_node(shell, tree->left, env);
	argv = get_arg((tree->right)->use.content, 0, env_from_envp(env), 0);
	if (!argv)
		return (1);
	(tree->right)->use.arg = argv;
	path = get_path(argv[0], env, F_OK + X_OK);
	execve(path, argv, env);
	ft_error(shell, 1, "EXEC:", strerror(errno));
	return (1);
}
