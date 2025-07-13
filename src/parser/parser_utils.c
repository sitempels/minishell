/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:51:06 by stempels          #+#    #+#             */
/*   Updated: 2025/07/09 17:00:03 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_shell *shell, t_token **token, int type)
{
	t_node	*new;

	new = (t_node *) ft_calloc(1, sizeof(t_node));
	if (!new)
		ft_error(shell, 0, 3, "PARSER", "NODE", get_errnum(N_CREAT));
	new->type = type;
	if (new->type == ARGUMENT || new->type == FILENAME)
		new->use.content = munch_token(token, 0);
	else
		new->use.content = munch_token(token, 1);
	return (new);
}

t_token	*munch_token(t_token **token, int clean)
{
	t_token	*tmp;

	if (!token)
		return (NULL);
	tmp = *token;
	*token = (*token)->next;
	tmp->next = NULL;
	if (clean == 1)
	{
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

t_node	*node_addback(t_node *node, t_node *new, int mode)
{
	t_node	*tmp;

	if (!node)
	{
		node = new;
		return (node);
	}
	tmp = node;
	if (mode == 0)
	{
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = new;
	}
	if (mode == 1)
	{
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new;
	}
	return (node);
}

void	verif_tree(t_shell *shell, t_node *tree, t_node *previous)
{
	size_t	len;
	char	*error;

	if (!tree)
		return ;
	error = NULL;
	if (tree->type == ERROR)
	{
		if (previous->type == WORD)
		{
			len = (previous->use.content)->size;
			error = (char *) ft_calloc(len + 1, sizeof(char));
			ft_strlcpy(error, (previous->use.content)->start, len + 1);
		}
		else
			error = get_type(previous->type);
		shell->status = 1;
		ft_error(shell, 0, 4, get_errnum(NEAR), "\'", error, "\'");
		return ;
	}
	if (shell->tree && tree->left)
		verif_tree(shell, tree->left, tree);
	if (shell->tree && tree->right)
		verif_tree(shell, tree->right, tree);
	return ;
}

void	is_quoted(t_token *end, int *quoted)
{
	size_t	i;

	i = 0;
	*quoted = 0;
	while (i < end->size)
	{
		if (end->start[i] == '\'' || end->start[i] == '\"')
			(*quoted)++;
		i++;
	}
}
