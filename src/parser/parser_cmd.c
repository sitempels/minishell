/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:11:21 by stempels          #+#    #+#             */
/*   Updated: 2025/06/25 16:27:09 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_usage(t_node *node, int type);

t_node	*parse_cmd(t_shell *shell, t_token **token)
{
	t_node	*new;

	if ((*token)->type == EOL)
		return (NULL);
	new = NULL;
	if ((*token)->type != LEFT_PAREN)
		new = parse_simple_cmd(shell, token);
	else
	{
		new = create_node(shell, token, SUBSHELL);
		new->use.fct = &execute_subshell;
		new->right = parse_complete_cmd(shell, token);
		if ((*token)->type != RIGHT_PAREN)
			ft_error(shell, 0, 1, "PARSER: Unexpected ')'");
		if ((*token)->type == RIGHT_PAREN)
			munch_token(token, 1);
		while ((*token)->type == LESS || (*token)->type == GREAT
			|| (*token)->type == DLESS || (*token)->type == DGREAT)
			new = node_addback(new, parse_io_redirect(shell, token), LEFT);
	}
	return (new);
}

t_node	*parse_simple_cmd(t_shell *shell, t_token **token)
{
	t_token	**tmp;
	t_node	*new;

	new = create_node(shell, NULL, CMD);
	new->use.fct = &execute_cmd;
	while ((*token)->type == LESS || (*token)->type == DLESS
		|| (*token)->type == GREAT || (*token)->type == DGREAT
		|| (*token)->type == WORD)
	{
		if ((*token)->type == LESS || (*token)->type == DLESS
			|| (*token)->type == GREAT || (*token)->type == DGREAT)
			new = node_addback(new, parse_io_redirect(shell, token), LEFT);
		else if ((*token)->type == WORD)
		{
			if (!new->right)
				new->right = create_node(shell, NULL, ARGUMENT);
			tmp = &(new->right)->use.content;
			*tmp = token_addback(tmp, munch_token(token, 0));
		}
		else
			break ;
	}
	return (new);
}

t_node	*parse_io_redirect(t_shell *shell, t_token **token)
{
	t_node	*new;

	if ((*token)->type == EOL)
		return (NULL);
	new = create_node(shell, token, (*token)->type);
	if ((*token)->type == WORD)
	{
		get_usage(new, (new)->type);
		new->right = create_node(shell, NULL, FILENAME);
		(new->right)->use.arg = get_arg(munch_token(token, 0), 0, NULL, 0);
	}
	else
	{
		new->right = create_node(shell, NULL, ERROR);
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
