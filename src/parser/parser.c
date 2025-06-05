/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/06/04 14:36:32 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*UTILS FUNCTIONS*/
void	*expander(t_token *token);
/**/
/*DESCENT FUNCTIONS - BY ORDER OF DESCENT*/
t_node	*parse_pipeline(t_token **token);

t_node	*parser(t_token *token)
{
	t_node	*tree;

	if (!token)
		return (NULL);
	tree = parse_pipeline(&token);
	if (!tree)
		return (NULL);
	return (tree);
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
