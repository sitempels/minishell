/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/07/09 13:54:46 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*UTILS FUNCTIONS*/
// void	*expander(t_token *token);
/**/
/*DESCENT FUNCTIONS - BY ORDER OF DESCENT*/

t_node	*parser(t_shell *shell, t_token **token)
{
	if (!token)
		return (NULL);
	shell->tree = parse_complete_cmd(shell, token);
	if (g_signal == SIGINT)
	{
		clean_shell(shell);
		return (NULL);
	}
	if ((*token)->type == EOL && !(*token)->next)
	{
		free(*token);
		*token = NULL;
	}
	if (shell->tree)
		verif_tree(shell, shell->tree, NULL);
	else
		ft_error(shell, 0, 1, "PARSER: Tree not planted !\n");
	return (shell->tree);
}

t_node	*parse_complete_cmd(t_shell *shell, t_token **token)
{
	t_node	*node;
	t_node	*new;

	if (g_signal == SIGINT || (*token)->type == EOL)
		return (NULL);
	new = NULL;
	node = parse_pipeline(shell, token);
	if ((*token)->type == AND_IF || (*token)->type == OR_IF)
	{
		new = create_node(shell, token, (*token)->type);
		new->left = node;
		if (!new->left->right || (*token)->type == EOL)
		{
			free(new->left);
			new->left = NULL;
			new->right = create_node(shell, NULL, ERROR);
			return (new);
		}
		new->use.fct = &execute_and_or_if;
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

	if (g_signal == SIGINT || (*token)->type == EOL)
		return (NULL);
	new = NULL;
	node = parse_cmd(shell, token);
	if ((*token)->type == OR)
	{
		new = create_node(shell, token, OR);
		new->left = node;
		if (!new->left->right || (*token)->type == EOL)
		{
			free(new->left);
			new->left = NULL;
			new->right = create_node(shell, NULL, ERROR);
			return (new);
		}
		new->use.fct = &execute_pipe;
		new->right = parse_pipeline(shell, token);
	}
	else
		new = node;
	return (new);
}
