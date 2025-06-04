/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:58:37 by stempels          #+#    #+#             */
/*   Updated: 2025/06/04 14:25:29 by stempels         ###   ########.fr       */
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
t_node	*parse_io_redirect(t_token **token)
{
	t_node	*new;

	new = create_node(token, (*token)->type);
	if (!new)
		return (NULL);
	if (new->type == DLESS)
		return (new);
	if ((*token)->type == WORD)
		new->use.content = munch_token(token);
	else
	{
		new->type = ERROR;
		if (!new)
			return (NULL);
	}
	return (new);
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
