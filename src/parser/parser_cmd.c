/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:11:21 by stempels          #+#    #+#             */
/*   Updated: 2025/06/16 13:12:11 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_cmd(t_token **token)
{
	t_node	*new;

	if ((*token)->type == EOL)
		return (NULL);
	new = NULL;
	if ((*token)->type != LEFT_PAREN)
		new = parse_simple_cmd(token);
	else
	{
		new = create_node(token, SUBSHELL);
		new->use.fct = &execute_subshell;
		if (!new)
			return (NULL);
		new->right = parse_complete_cmd(token);
		if ((*token)->type != RIGHT_PAREN)
			return (create_node(NULL, ERROR));
		if ((*token)->type == RIGHT_PAREN)
			munch_token(token, 1);
		while ((*token)->type == LESS || (*token)->type == GREAT
			|| (*token)->type == DLESS || (*token)->type == DGREAT)
			new = node_addback(new, parse_io_redirect(token), LEFT);
	}
	return (new);
}

t_node	*parse_simple_cmd(t_token **token)
{
	t_token	*tmp;
	t_node	*new;

	new = create_node(NULL, CMD);
	new->use.fct = &execute_cmd;
	if (!new)
		return (NULL);
	while ((*token)->type == LESS || (*token)->type == DLESS
		|| (*token)->type == GREAT || (*token)->type == DGREAT
		|| (*token)->type == WORD)
	{
		if ((*token)->type == LESS || (*token)->type == DLESS
			|| (*token)->type == GREAT || (*token)->type == DGREAT)
			new = node_addback(new, parse_io_redirect(token), LEFT);
		else if ((*token)->type == WORD)
		{
			if (!new->right)
				new->right = create_node(NULL, ARGUMENT);
			tmp = (new->right)->use.content;
			(new->right)->use.content = token_addback(&tmp, munch_token(token, 0));
		}
		else
			break ;
	}
	return (new);
}
/*
t_node	*parse_word(t_token **token)
{
	t_node	*new;

	new = create_node(token, WORD);
	return (new);
}*/
