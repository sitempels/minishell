/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/06/16 11:13:51 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*UTILS FUNCTIONS*/
// void	*expander(t_token *token);
/**/
/*DESCENT FUNCTIONS - BY ORDER OF DESCENT*/
t_node	*parse_pipeline(t_token **token);

t_node	*parser(t_token **token)
{
	t_node	*tree;

	if (!token)
		return (NULL);
	tree = parse_complete_cmd(token);
	if (!tree)
		return (NULL);
	return (tree);
}

t_node	*parse_complete_cmd(t_token **token)
{
	t_node	*node;
	t_node	*new;

	if ((*token)->type == EOL)
		return (create_node(token, (*token)->type));
	new = NULL;
	node = parse_pipeline(token);
	if ((*token)->type == AND_IF || (*token)->type == OR_IF)
	{
		new = create_node(token, (*token)->type);
		new->use.fct = &execute_and_or_if;
		if (!new)
			return (NULL);
		new->left = node;
		new->right = parse_complete_cmd(token);
	}
	else
		new = node;
	return (new);
}

t_node	*parse_pipeline(t_token **token)
{
	t_node	*node;
	t_node	*new;

	if ((*token)->type == EOL)
		return (NULL);
	new = NULL;
	node = parse_cmd(token);
	if ((*token)->type == OR)
	{
		new = create_node(token, OR);
		new->use.fct = &execute_pipe;
		if (!new)
			return (NULL);
		new->left = node;
		if ((*token)->type != EOL)
			new->right = parse_pipeline(token);
	}
	else
		new = node;
	return (new);
}
