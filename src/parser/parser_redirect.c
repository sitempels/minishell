/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:58:37 by stempels          #+#    #+#             */
/*   Updated: 2025/06/12 15:47:33 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_usage(t_node *node, int type);

t_node	*parse_io_redirect(t_token **token)
{
	t_node	*new;

	if ((*token)->type == EOL)
		return (NULL);
	new = create_node(token, (*token)->type);
	if (!new)
		return (NULL);
	get_usage(new, (new)->type);
	if ((*token)->type == WORD)
	{
		new->right = create_node(NULL, FILENAME);
		if (!new->right)
			return (NULL);
		(new->right)->use.arg = get_arg(munch_token(token), 0);
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
		node->use.fct = &execute_redir_output_a;
	return ;
}
