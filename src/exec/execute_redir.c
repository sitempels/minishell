/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:04:05 by stempels          #+#    #+#             */
/*   Updated: 2025/07/26 15:46:59 by stempels         ###   ########.fr       */
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
		arg = expand(shell, (tree->right)->use.content, NULL);
	fd = open(arg[0], O_RDONLY, O_CLOEXEC);
	if (fd < 0)
	{
		ft_error(shell, 0, 3, arg[0], ": ", strerror(errno));
		return (ft_free_array_pos(&arg, 0), 1);
	}
	dup2(fd, 0);
	close(fd);
	ft_free_array_pos(&arg, 0);
	if (tree->left)
		execute_node(shell, tree->left);
	return (0);
}

int	execute_heredoc(t_shell *shell, t_node *tree)
{
	int		fd;

	fd = (tree->right)->use.fd;
	(tree->right)->use.content = NULL;
	dup2(fd, 0);
	close(fd);
	if (tree->left)
		execute_node(shell, tree->left);
	return (0);
}

int	execute_redir_output(t_shell *shell, t_node *tree)
{
	int		fd;
	char	**arg;

	if (tree->right)
		arg = expand(shell, (tree->right)->use.content, NULL);
	fd = open(arg[0], O_WRONLY | O_TRUNC | O_CREAT, 00644);
	if (fd < 0)
	{
		ft_error(shell, 0, 3, arg[0], ": ", strerror(errno));
		return (ft_free_array_pos(&arg, 0), 1);
	}
	dup2(fd, 1);
	close(fd);
	ft_free_array_pos(&arg, 0);
	if (tree->left)
		execute_node(shell, tree->left);
	return (0);
}

int	execute_redir_output_a(t_shell *shell, t_node *tree)
{
	int		fd;
	char	**arg;

	if (tree->right)
		arg = expand(shell, (tree->right)->use.content, NULL);
	fd = open(arg[0], O_WRONLY | O_APPEND | O_CREAT, 00644);
	if (fd < 0)
	{
		ft_error(shell, 0, 3, arg[0], ": ", strerror(errno));
		return (ft_free_array_pos(&arg, 0), 1);
	}
	dup2(fd, 1);
	close(fd);
	ft_free_array_pos(&arg, 0);
	if (tree->left)
		execute_node(shell, tree->left);
	return (0);
}
