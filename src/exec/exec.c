/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:57:50 by stempels          #+#    #+#             */
/*   Updated: 2025/06/25 12:41:39 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isbuiltin(t_shell *shell, t_env *env, char **argv);

int	execute_and_or_if(t_shell *shell, t_node *tree, t_env *env)
{
	int		status;

	status = execute_node(shell, tree->left, env);
	if (status > 0 && tree->type == OR_IF)
	{
		status = execute_node(shell, tree->right, env);
		if (status > 0)
			ft_error(shell, 1, 2, "EXEC", " 1");
	}
	else if (status == 0 && tree->type == AND_IF)
	{
		status = execute_node(shell, tree->right, env);
		if (status > 0)
			ft_error(shell, 1, 2, "EXEC", " 2");
	}
	return (status);
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
			builtin_exit(shell, 0, 1, EXIT_FAILURE);
		clean_shell(shell);
		exit(0);
	}
	else
	{
		if (create_pipe(&child_nbr, shell, pipefd, &pid))
		{
			if (execute_node(shell, tree->right, env))
				builtin_exit(shell, 0, 1, EXIT_FAILURE);
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

int	execute_subshell(t_shell *shell, t_node *tree, t_env *env)
{
	int		status;
	pid_t	pid;

	if (update_envint(env, "SHLVL", 0, 1))
		return (1);
	if (execute_node(shell, tree->left, env))
		return (ft_error(shell, 0, 2, "EXEC", "REDIRECTION FAILED"));
	if (create_fork(shell, &pid))
	{
		if (execute_node(shell, tree->right, env))
			ft_error(shell, 1, 2, "EXEC", "SUBSHELL");
		clean_shell(shell);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (update_envint(env, "SHLVL", 0, -1))
		return (1);
	return (status);
}

int	execute_cmd(t_shell *shell, t_node *tree, t_env *env)
{
	int		status;
	char	*path;
	char	**argv;
	pid_t	pid;

	pid = 0;
	argv = NULL;
	if (execute_node(shell, tree->left, env))
		return (ft_error(shell, 0, 2, "EXEC", "REDIRECTION FAILED"));
	if (tree->right)
		argv = get_arg((tree->right)->use.content, 0, shell->env, 0);
	status = isbuiltin(shell, env, argv);
	if (status >= 0)
		return (status);
	if (create_fork(shell, &pid))
	{
		path = get_path(argv[0], env, F_OK + X_OK);
		execve(path, argv, envp_from_env(env));
		ft_error(shell, 1, 3, argv[0], ": ", get_errnum(C_MISS));
	}
	waitpid(pid, &status, 0);
	return (status);
}

static int	isbuiltin(t_shell *shell, t_env *env, char **argv)
{
	int	status;

	if (!argv)
		return (-1);
	status = -1;
	if (!ft_strcmp(argv[0], "cd"))
		status = builtin_cd(env, argv[1]);
	else if (!ft_strcmp(argv[0], "echo"))
		status = builtin_echo(argv);
	else if (!ft_strcmp(argv[0], "env"))
		status = builtin_env(env);
	else if (!ft_strcmp(argv[0], "exit"))
	{
		if (!argv[1])
			status = builtin_exit(shell, 1, 0);
		status = builtin_exit(shell, 1, ft_atoi(argv[1]));
	}
	else if (!ft_strcmp(argv[0], "export"))
		status = builtin_export(env, argv);
	else if (!ft_strcmp(argv[0], "pwd"))
		status = builtin_pwd();
	else if (!ft_strcmp(argv[0], "unset"))
		status = builtin_unset(&env, argv);
	return (status);
}
