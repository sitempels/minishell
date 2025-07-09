/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:04:05 by stempels          #+#    #+#             */
/*   Updated: 2025/07/09 14:45:27 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_arrlen(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	execute_redir_input(t_shell *shell, t_node *tree)
{
	int		fd;
	char	*path;
	char	**arg;

	path = NULL;
	if (tree->right)
	{
		arg = expand(shell, (tree->right)->use.content, NULL);
		if (ft_arrlen(arg) > 1)
			ft_error(shell, 0, 1, "ambiguous redirect");
		path = get_path(arg[0], shell->env, F_OK + R_OK);
	}
	if (!path)
		ft_error(shell, 0, 2, arg[0], get_errnum(I_MISS));
	fd = open(path, O_RDONLY, O_CLOEXEC);
	dup2(fd, 0);
	close(fd);
//	if (path)
//		free(path);
	free_array(arg, 0);
	if (tree->left)
		execute_node(shell, tree->left);
	return (0);
}

int	execute_heredoc(t_shell *shell, t_node *tree)
{
	int		fd;
//	char	*path;

//	path = tree->right->use.content->start;
//	if (!path)
//		ft_error(shell, 0, 2, path, get_errnum(I_MISS));
//	fd = open(path, O_RDONLY, O_CLOEXEC);
	fd = (tree->right)->use.fd;
	(tree->right)->use.content = NULL;
//	unlink(path);
	dup2(fd, 0);
	close(fd);
//	free(path);
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
//		free(path);
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
//		free(path);
	}
	dup2(fd, 1);
	close(fd);
	free_array(arg, 0);
	if (tree->left)
		execute_node(shell, tree->left);
	return (0);
}
