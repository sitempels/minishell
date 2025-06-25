/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:04:05 by stempels          #+#    #+#             */
/*   Updated: 2025/06/25 11:29:29 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_redir_input(t_shell *shell, t_node *tree, t_env *env)
{
	int		fd;
	char	*path;

	path = NULL;
	if (tree->right)
		path = get_path(((tree->right)->use.arg)[0], env, F_OK + R_OK);
	if (!path)
		ft_error(shell, 0, 2, (tree->right)->use.arg[0], get_errnum(I_MISS));
	fd = open(path, O_RDONLY, O_CLOEXEC);
	if (tree->type == DLESS)
		unlink(path);
	close(0);
	dup2(fd, 0);
	close(fd);
	if (tree->left)
		execute_node(shell, tree->left, env);
	return (0);
}

int	execute_redir_output(t_shell *shell, t_node *tree, t_env *env)
{
	int		fd;
	char	*path;

	path = NULL;
	if (tree->right)
		path = get_path(((tree->right)->use.arg)[0], env, F_OK + W_OK);
	if (!path)
	{
		path = (tree->right)->use.arg[0];
		fd = open(path, O_RDWR | O_CREAT, 00644);
	}
	else
		fd = open(path, O_WRONLY | O_TRUNC);
	close(1);
	dup2(fd, 1);
	close(fd);
	if (tree->left)
		execute_node(shell, tree->left, env);
	return (0);
}

int	execute_redir_output_a(t_shell *shell, t_node *tree, t_env *env)
{
	int		fd;
	char	*path;

	path = NULL;
	if (tree->right)
		path = get_path(((tree->right)->use.arg)[0], env, F_OK + W_OK);
	if (!path)
	{
		path = (tree->right)->use.arg[0];
		fd = open(path, O_RDWR | O_CREAT, 00644);
	}
	else
		fd = open(path, O_WRONLY | O_APPEND, 00644);
	close(1);
	dup2(fd, 1);
	close(fd);
	if (tree->left)
		execute_node(shell, tree->left, env);
	return (0);
}
