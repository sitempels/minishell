/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:04:05 by stempels          #+#    #+#             */
/*   Updated: 2025/06/11 09:10:22 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_redir_input(t_node *tree, char **env)
{
	int		fd;
	int		fd_in;
	char	*path;

	fd_in = 0;
//	(tree->right)->use.arg = get_arg((tree->right)->use.content, 0);
	path = get_path(((tree->right)->use.arg)[0], env, F_OK + R_OK);
	if (!path)
		return (1);
	fd = open(path, O_RDONLY, O_CLOEXEC);	
	dup2(fd, fd_in);
	close(fd);
	if (tree->left)
		execute_descend(tree->left, env);
	return (0);
}

int	execute_redir_output(t_node *tree, char **env)
{
	int		fd;
	int		fd_out;
	char	*path;

	fd_out = 1;
//	(tree->right)->use.arg = get_arg((tree->right)->use.content, 0);
	path = get_path(((tree->right)->use.arg)[0], env, F_OK + W_OK);
	if (!path)
	{
		path = (tree->right)->use.arg[0];	
		fd = open(path, O_RDWR | O_CREAT, 00644);	
	}
	else
		fd = open(path, O_WRONLY);	
	dup2(fd, fd_out);
	close(fd);
	if (tree->left)
		execute_descend(tree->left, env);
	return (0);
}

int	execute_redir_output_A(t_node *tree, char **env)
{
	int		fd;
	int		fd_out;
	char	*path;

	fd_out = 1;
//	(tree->right)->use.arg = get_arg((tree->right)->use.content, 0);
	path = get_path(((tree->right)->use.arg)[0], env, F_OK + W_OK);
	if (!path)
		path = (tree->right)->use.arg[0];	
	fd = open(path, O_WRONLY, O_CLOEXEC, O_APPEND, O_CREAT, 00644);	
	dup2(fd, fd_out);
	close(fd);
	if (tree->left)
		execute_descend(tree->left, env);
	return (0);
}
