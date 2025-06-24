/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:57:50 by stempels          #+#    #+#             */
/*   Updated: 2025/06/24 18:22:51 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isbuiltin(t_shell *shell, t_env *env, char **argv);

int	execute_and_or_if(t_shell *shell, t_node *tree, t_env *env)
{
	int		status;
	pid_t	pid;

	if (create_fork(shell, &pid))
	{
		if (execute_node(shell, tree->left, env))
			ft_error(shell, 1, 2, "EXEC", strerror(errno));
		clean_shell(shell);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (status == EXIT_SUCCESS && tree->type == AND_IF)
	{
		if (execute_node(shell, tree->right, env))
			ft_error(shell, 1, 2, "EXEC", strerror(errno));
	}
	printf("%d\n", status);
	if (status == EXIT_FAILURE && tree->type == OR_IF)
	{
		if (execute_node(shell, tree->right, env))
			ft_error(shell, 1, 2, "EXEC", strerror(errno));
	}
	return (0);
}

int	execute_pipe(t_shell *shell, t_node *tree, t_env *env)
{
	int		pipefd[2];
	int		child_nbr;
	int		status;
	pid_t	pid;

	child_nbr = 0;
	if (pipe(pipefd) == -1)
		ft_error(shell, 0, 2, "EXEC: PIPE", get_errnum(N_CREAT));
	if (create_pipe(&child_nbr, shell, pipefd, &pid))
	{
		if (execute_node(shell, tree->left, env))
			ft_error(shell, 1, 2, "EXEC:", "TRUC");
		clean_shell(shell);
		exit(0);
	}	
	else
	{
		if (create_pipe(&child_nbr, shell, pipefd, &pid))
		{
			if (execute_node(shell, tree->right, env))
				ft_error(shell, 1, 2, "EXEC:", "TRUC");
			clean_shell(shell);
			exit(0);
		}
	}	
	close(pipefd[0]);
	close(pipefd[1]);
	while (child_nbr > 0)
	{
		wait(&status);
		child_nbr--;
	}
	return (status);
}

int	execute_cmd(t_shell *shell, t_node *tree, t_env *env)
{
	int		status;
	char	*path;
	char	**argv;
	pid_t	pid;

	pid = 0;
	if (tree->left)
		execute_node(shell, tree->left, env);
	argv = get_arg((tree->right)->use.content, 0, shell->env, 0);
	if (!argv)
		return (1);
	(tree->right)->use.arg = argv;
	if (isbuiltin(shell, env, argv))
		return (0);
	if (create_fork(shell, &pid))
	{
		path = get_path(argv[0], env, F_OK + X_OK);
		execve(path, argv, envp_from_env(env));
		ft_error(shell, 1, 1, "EXEC:", strerror(errno));
	}
	waitpid(pid, &status, 0);
	return (status);
}

static int	isbuiltin(t_shell *shell, t_env *env, char **argv)
{
	if (!ft_strcmp(argv[0], "cd"))
		builtin_cd(env, argv[1]);
	else if (!ft_strcmp(argv[0], "echo"))
		builtin_echo(argv);
	else if (!ft_strcmp(argv[0], "env"))
		builtin_env(env);
	else if (!ft_strcmp(argv[0], "exit"))
		builtin_exit(shell);
	else if (!ft_strcmp(argv[0], "export"))
		builtin_export(env, argv);
	else if (!ft_strcmp(argv[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(argv[0], "unset"))
		builtin_unset(&env, argv);
	else
		return (0);
	return (1);
}
