/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/06/20 13:26:51 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*UTILS FUNCTIONS*/
// void	*expander(t_token *token);
/**/
/*DESCENT FUNCTIONS - BY ORDER OF DESCENT*/

t_node	*parser(t_shell *shell, t_token **token)
{
	t_node	*tree;

	if (!token)
		return (NULL);
	tree = parse_complete_cmd(shell, token);
	if ((*token)->type == EOL)
	{
		free(*token);
		*token = NULL;
	}
	else
		ft_error(shell, "PARSER: SOMETHING WENT WRONG !!!\n", N_PRINT);
	if (!tree)
		ft_error(shell, "PARSER: Tree not planted !\n", N_PRINT);
	return (tree);
}

t_node	*parse_complete_cmd(t_shell *shell, t_token **token)
{
	t_node	*node;
	t_node	*new;

	if ((*token)->type == EOL)
		return (NULL);
	new = NULL;
	node = parse_pipeline(shell, token);
	if ((*token)->type == AND_IF || (*token)->type == OR_IF)
	{
		new = create_node(shell, token, (*token)->type);
		new->use.fct = &execute_and_or_if;
		new->left = node;
		new->right = parse_complete_cmd(shell, token);
	}
	else
		new = node;
	return (new);
}

t_node	*parse_pipeline(t_shell *shell, t_token **token)
{
	t_node	*node;
	t_node	*new;

	if ((*token)->type == EOL)
		return (NULL);
	new = NULL;
	node = parse_cmd(shell, token);
	if ((*token)->type == OR)
	{
		new = create_node(shell, token, OR);
		new->use.fct = &execute_pipe;
		new->left = node;
		if ((*token)->type != EOL)
			new->right = parse_pipeline(shell, token);
	}
	else
		new = node;
	return (new);
}
