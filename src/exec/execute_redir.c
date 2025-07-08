/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:04:05 by stempels          #+#    #+#             */
/*   Updated: 2025/07/07 16:31:24 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_redir_input(t_shell *shell, t_node *tree)
{
	int		fd;
	char	*path;
	char	**arg;

	path = NULL;
	if (tree->right)
	{
		arg = expand(shell, (tree->right)->use.content, NULL);
		path = get_path(arg[0], shell->env, F_OK + R_OK);
	}
	if (!path)
		ft_error(shell, 0, 2, arg[0], get_errnum(I_MISS));
	fd = open(path, O_RDONLY, O_CLOEXEC);
	if (tree->type == DLESS)
		unlink(path);
	dup2(fd, 0);
	close(fd);
	if (path)
		free(path);
	free_array(arg, 0);
	if (tree->left)
		execute_node(shell, tree->left);
	return (0);
}

int	execute_redir_output(t_shell *shell, t_node *tree)
{
	int		fd;
	char	*path;
	char	**arg;

	path = NULL;
	if (tree->right)
	{
		arg = expand(shell, (tree->right)->use.content, NULL);
		path = get_path(arg[0], shell->env, F_OK + R_OK);
	}
	if (!path)
		fd = open(arg[0], O_RDWR | O_CREAT, 00644);
	else
	{
		fd = open(path, O_WRONLY | O_TRUNC);
		free(path);
	}
	dup2(fd, 1);
	close(fd);
	free_array(arg, 0);
	if (tree->left)
		execute_node(shell, tree->left);
	return (0);
}

int	execute_redir_output_a(t_shell *shell, t_node *tree)
{
	int		fd;
	char	*path;
	char	**arg;

	path = NULL;
	if (tree->right)
	{
		arg = expand(shell, (tree->right)->use.content, NULL);
		path = get_path(arg[0], shell->env, F_OK + R_OK);
	}
	if (!path)
		fd = open(arg[0], O_RDWR | O_CREAT, 00644);
	else
	{
		fd = open(path, O_WRONLY | O_TRUNC);
		free(path);
	}
	dup2(fd, 1);
	close(fd);
	free_array(arg, 0);
	if (tree->left)
		execute_node(shell, tree->left);
	return (0);
}
