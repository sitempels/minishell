/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:57:50 by stempels          #+#    #+#             */
/*   Updated: 2025/07/01 13:03:10 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isbuiltin(t_shell *shell, char **argv);

int	execute_and_or_if(t_shell *shell, t_node *tree)
{
	shell->status = execute_node(shell, tree->left);
	wait(&shell->status);
	if (WIFEXITED(shell->status))
		shell->status = WEXITSTATUS(shell->status);
	else if (WIFSIGNALED(shell->status))
		shell->status = (WTERMSIG(shell->status));
	if (shell->status > 0 && tree->type == OR_IF)
	{
		shell->status = execute_node(shell, tree->right);
		if (shell->status > 0)
			ft_error(shell, 1, 2, "EXEC", " 1");
	}
	else if (shell->status == 0 && tree->type == AND_IF)
	{
		shell->status = execute_node(shell, tree->right);
		if (shell->status > 0)
			ft_error(shell, 1, 2, "EXEC", " 2");
	}
	return (shell->status);
}

int	execute_pipe(t_shell *shell, t_node *tree)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		ft_error(shell, 0, 2, "EXEC: PIPE", get_errnum(N_CREAT));
	create_pipe(shell, tree->left, 0, pipefd);
	create_pipe(shell, tree->right, 1, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}

int	execute_subshell(t_shell *shell, t_node *tree)
{
	if (execute_node(shell, tree->left))
		return (ft_error(shell, 0, 2, "EXEC", "REDIRECTION FAILED"));
	if (create_fork(shell))
	{
		if (update_envint(shell->env, "SHLVL", 0, 1))
			return (1);
		if (execute_node(shell, tree->right))
			ft_error(shell, 1, 2, "EXEC", "SUBSHELL");
		clean_shell(shell);
		if (update_envint(shell->env, "SHLVL", 0, -1))
			return (1);

		exit(0);
	}
	return (0);
}

int	execute_cmd(t_shell *shell, t_node *tree)
{
	int	status;
	char	*path;
	char	**argv;

	argv = NULL;
	if (execute_node(shell, tree->left))
		return (ft_error(shell, 0, 2, "EXEC", "REDIRECTION FAILED"));
	if (tree->right)
		argv = get_arg(shell, (tree->right)->use.content, 0);
	status = isbuiltin(shell, argv);
	if (status >= 0)
		return (status);
	if (create_fork(shell))
	{
		path = get_path(argv[0], shell->env, F_OK + X_OK);
		shell->status = execve(path, argv, envp_from_env(shell->env));
		ft_error(shell, 1, 3, argv[0], ": ", get_errnum(C_MISS));
	}
	return (0);
}

static int	isbuiltin(t_shell *shell, char **argv)
{
	int	status;

	if (!argv || !argv[0])
		return (-1);
	status = -1;
	if (!ft_strcmp(argv[0], "cd"))
		status = builtin_cd(shell->env, argv[1]);
	else if (!ft_strcmp(argv[0], "echo"))
		status = builtin_echo(argv);
	else if (!ft_strcmp(argv[0], "env"))
		status = builtin_env(shell->env);
	else if (!ft_strcmp(argv[0], "exit"))
	{
		if (!argv[1])
			status = builtin_exit(shell, 1, 0);
		status = builtin_exit(shell, 1, ft_atoi(argv[1]));
	}
	else if (!ft_strcmp(argv[0], "export"))
		status = builtin_export(shell->env, argv);
	else if (!ft_strcmp(argv[0], "pwd"))
		status = builtin_pwd();
	else if (!ft_strcmp(argv[0], "unset"))
		status = builtin_unset(&shell->env, argv);
	return (status);
}
