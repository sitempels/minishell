/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:49:17 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/12 20:23:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmds(const char *cmds)
{
	if (!cmds)
		return ;
	free((void *)cmds);
}

void	ft_free_arr(char **arr)
{
	size_t	count;

	if (!arr || !*arr)
		return ;
	count = ft_stralen(arr);
	while (count > 0)
	{
		free(arr[count]);
		arr[count] = NULL;
	}
	free(arr);
}

void	ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = (tokens)->next;
		free((tokens)->token);
		free(tokens);
		tokens = tmp;
	}
}

void	ft_free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->cmd)
		free(tree->cmd);
	if (tree->args)
		ft_free_args(tree->args);
	if (tree->infile > 2)
		close(tree->infile);
	if (tree->outfile > 2)
		close(tree->outfile);
	if (tree->right)
		ft_free_tree(tree->right);
	if (tree->left)
		ft_free_tree(tree->left);
	free(tree);
	tree = NULL;
}

void	ft_free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->cmds)
		ft_free_cmds(shell->cmds);
	if (shell->envs)
		ft_free_arr(shell->envs);
	if (shell->tokens)
		ft_free_tokens(shell->tokens);
	if (shell->tree)
		ft_free_tree(shell->tree);
	free(shell);
	shell = NULL;
}
