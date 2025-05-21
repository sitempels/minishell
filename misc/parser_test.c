/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/05/21 16:54:36 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "test.h"

t_node	*parse_word(t_token *tokens);

t_node	*create_node(t_token *tokens, int type)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node) * 1);
	if (!new)
		return (NULL);
	new->type = type;
	new->content = tokens->content;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_node	*parse_cmd(t_token *tokens)
{
	t_node	*new;

	if (!tokens)
		return (NULL);
	new = create_node(tokens, CMD);
/*	if (!new)
		panic(.tkt);
	if ((token->type) == OPERATOR_FLOW)
	{
		new->left = parse_io_redirect(token_current);
		parse_cmd(token_next);
	}*/
	if (tokens->next && (tokens->next)->type == WORD)
	{
		new->right = parse_word(tokens->next);
		parse_cmd(tokens->next);
	}
//	take(tokens);
	return (new);
}

t_node	*parse_word(t_token *tokens)
{
	t_node	*new;

	new = create_node(tokens, WORD);
/*	if (!new)
		panic(.tkt);*/
	if (tokens->next && (tokens->next)->type == WORD)
		new->left = parse_word(tokens->next);
//	take(tokens);
	return (new);
}
