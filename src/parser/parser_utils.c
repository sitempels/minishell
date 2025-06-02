/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:51:06 by stempels          #+#    #+#             */
/*   Updated: 2025/06/02 17:18:30 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_token **token, int type)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node) * 1);
	if (!new)
		return (NULL);
	new->type = type;
	if (token)
	{
		new->use.content = *token;
		*token = munch_token(token);
	}
	else
		new->use.content = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_token	*munch_token(t_token **token)
{
	t_token	*tmp;

	tmp = (*token)->next;
	*token = tmp;
	return (*token);
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
