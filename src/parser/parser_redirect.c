/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:58:37 by stempels          #+#    #+#             */
/*   Updated: 2025/06/05 12:32:57 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
t_node	*parse_cmd_affix(t_token **token)
{
	t_node	*new;

	new = parse_io_file(token);
	return (new);
}
*/
static void	get_usage(t_node *node, int type);

t_node	*parse_io_redirect(t_token **token)
{
	t_node	*new;

	new = create_node(token, (*token)->type);
	get_usage(new, (*token)->type);
	if (!new)
		return (NULL);
	if (new->type == DLESS)
		return (new);
	if ((*token)->type == WORD)
	{
		if (!new->right)
		{
			new->right = create_node(NULL, FILENAME);
			if (!new->right)
				return (NULL);
		}
		(new->right)->use.content = munch_token(token);
	}
	else
	{
		new->type = ERROR;
		if (!new)
			return (NULL);
	}
	return (new);
}

static void	get_usage(t_node *node, int type)
{
	if (type == LESS || type == DLESS)
		node->use.fct = &execute_redir_input;
	if (type == GREAT)
		node->use.fct = &execute_redir_output;
	if (type == DGREAT)
		node->use.fct = &execute_redir_output_A;
	return ;
}
/*
t_node	*parse_io_here(t_token **token)
{
	t_node	*new;

	new = create_node(token, (*token)->type);
	if (!new)
		return (NULL);
	return (new);
}
*/
/*
t_token	*parse_io_file(t_token **token)
{
	t_token	*new;

	new = NULL;
	if ((*token)->type == WORD)
	{
		new = *token; 
		munch_token(token);
	}
	else
		new = create_node(token, ERROR);
	return (new);
}

t_node	*parse_filename(t_token **token)
{
	t_node	*new;

	new = NULL;
	new = create_node(token, FILENAME);
	if (!new)
		return (NULL);
	return (new);
}*/
