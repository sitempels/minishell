/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:58:37 by stempels          #+#    #+#             */
/*   Updated: 2025/06/02 17:24:57 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_cmd_affix(t_token **token)
{
	t_node	*new;

	new = create_node(token, (*token)->type);
	if ((*token)->type == WORD)
		new->right = parse_io_file(token);
	else
	{
		new->type = ERROR;
		new->use.content = NULL;
	}
	return (new);
}

t_node	*parse_io_redirect(t_token **token)
{
	t_node	*new;

	if ((*token)->type == DLESS)
		new = parse_io_here(token);
	else
		new = parse_cmd_affix(token);
	return (new);
}

t_node	*parse_io_here(t_token **token)
{
	t_node	*new;

	new = NULL;
	new = create_node(token, (*token)->type);
	if (!new)
		return (NULL);
	return (new);
}

t_node	*parse_io_file(t_token **token)
{
	t_node	*new;

	new = parse_filename(token);
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
}
