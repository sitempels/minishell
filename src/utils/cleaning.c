/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:14:47 by stempels          #+#    #+#             */
/*   Updated: 2025/07/07 16:20:06 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_tree(t_node **tree)
{
	if (!tree || !*tree)
		return ;
	if ((*tree)->left)
		clean_tree(&(*tree)->left);
	if ((*tree)->right)
		clean_tree(&(*tree)->right);
	if ((*tree)->type == ARGUMENT || (*tree)->type == FILENAME)
	{
		if ((*tree)->use.content)
		{
			free((*tree)->use.content);
			(*tree)->use.content = NULL;
		}
	}
	free(*tree);
	*tree = NULL;
	return ;
}

char	**free_array(char **array, int pos)
{
	if (!array)
		return (NULL);
	while (array[pos])
	{
		if (array[pos])
		{
			free(array[pos]);
			array[pos] = NULL;
		}
		pos++;
	}
	return (NULL);
}

void	clean_token_lst(t_token **token_lst)
{
	if (!token_lst || !*token_lst)
		return ;
	if ((*token_lst)->next)
		clean_token_lst(&(*token_lst)->next);
	free(*token_lst);
	*token_lst = NULL;
	return ;
}

void	clean_shell(t_shell *shell)
{
	if (shell->tokens)
		clean_token_lst(&shell->tokens);
	shell->tokens = NULL;
	if (shell->tree)
		clean_tree(&shell->tree);
	shell->tree = NULL;
	if (shell->cli)
		free(shell->cli);
	shell->cli = NULL;
	g_signal = 0;
	return ;
}

void	destroy_shell(t_shell *shell)
{
	t_env	*tmp;

	clean_shell(shell);
	while (shell->env)
	{
		tmp = shell->env;
		shell->env = (shell->env)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	shell->env = NULL;
	free(shell);
	rl_clear_history();
	return ;
}
