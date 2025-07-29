/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:57:50 by stempels          #+#    #+#             */
/*   Updated: 2025/07/29 17:00:21 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isbuiltin(t_shell *shell, char **argv, int status);

int	execute_and_or_if(t_shell *shell, t_node *tree)
{
	execute_node(shell, tree->left);
	restore_std_io(shell);
	if (shell->status != 0 && tree->type == OR_IF)
		execute_node(shell, tree->right);
	else if (shell->status == 0 && tree->type == AND_IF)
		execute_node(shell, tree->right);
	return (shell->status);
}

int	execute_pipe(t_shell *shell, t_node *tree)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (ft_error(shell, 0, 2, "PIPE", get_errnum(N_CREAT)), 1);
	create_pipe(shell, tree->left, 0, pipefd);
	create_pipe(shell, tree->right, 1, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
//	signal(SIGINT, handle_sigint);
	while (shell->child_nbr > 0)
	{
		wait_and_decrypt_child(shell);
		shell->child_nbr--;
		if (g_signal == SIGINT)
			g_signal = 0;
	}
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
		builtin_exit(shell, 0, NULL);
	}
	wait_and_decrypt_child(shell);
	return (shell->status);
}

int	execute_cmd(t_shell *shell, t_node *tree)
{
	char	*path;
	char	**argv;

	argv = NULL;
	if (execute_node(shell, tree->left))
		return (1);
	if (tree->right)
		argv = expand(shell, (tree->right)->use.content, NULL);
	if (!isbuiltin(shell, argv, 0) && create_fork(shell))
	{
		path = get_path(shell, argv[0], shell->env, F_OK + X_OK);
		if (path)
		{
			execve(path, argv, envp_from_env(shell->env));
			perror(argv[0]);
		}
		ft_free_array_pos(&argv, 0);
		shell->status = 127;
		builtin_exit(shell, 0, NULL);
	}
	ft_free_array_pos(&argv, 0);
	wait_and_decrypt_child(shell);
	signal(SIGINT, handle_sigint);
	return (shell->status);
}

static int	isbuiltin(t_shell *shell, char **argv, int found)
{
	if (!argv || !argv[0])
		return (-1);
	found = 1;
	if (!ft_strcmp(argv[0], "cd"))
		shell->status = builtin_cd(shell->env, argv[1]);
	else if (!ft_strcmp(argv[0], "echo"))
		shell->status = builtin_echo(argv);
	else if (!ft_strcmp(argv[0], "env"))
		shell->status = builtin_env(shell->env);
	else if (!ft_strcmp(argv[0], "exit"))
		builtin_exit(shell, 1, argv);
	else if (!ft_strcmp(argv[0], "export"))
		shell->status = builtin_export(&shell->env, argv);
	else if (!ft_strcmp(argv[0], "pwd"))
		shell->status = builtin_pwd();
	else if (!ft_strcmp(argv[0], "unset"))
		shell->status = builtin_unset(&shell->env, argv);
	else
		found = 0;
	return (found);
}
