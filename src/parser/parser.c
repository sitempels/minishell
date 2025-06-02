/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/06/02 09:53:52 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*UTILS FUNCTIONS*/
t_node	*create_node(t_token **tokens, int type);
t_token	*munch_token(t_token **token);
void	*expander(t_token *token);
/**/
/*DESCENT FUNCTIONS - BY ORDER OF DESCENT*/
t_node	*parse_pipeline(t_token **token);
t_node	*parse_cmd(t_token **token);
t_node	*parse_simple_cmd(t_token **token);
t_node	*parse_word(t_token **token);
t_node	*parse_cmd_prefix(t_token **tokens);
//t_node	*parse_cmd_suffix(t_token *tokens);
t_node	*parse_io_redirect(t_token **token);
t_node	*parse_io_here(t_token **token);
t_node	*parse_io_file(t_token **token);
t_node	*parse_filename(t_token **token);
/**/

/*PROTO GRAMMAR FUNCTION NON TERMINAL*/
/*
t_node	*parse_*(t_token token)
{
	if (grammar condition)
		then parse* OR create*;
	
}
*/
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

t_token	*munch_token(t_token **token)
{
	t_token	*tmp;

	tmp = (*token)->next;
	*token = tmp;
	return (*token);
}

void	*expander(t_token *token)
{
	int		i;
	int		size;
	char	*start;
	char	*new;

	if (token->type == EOL)
		return (NULL);
	start = (token->start);
	size = token->size;
	new = (char *) malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = '\0';
	i = 0;
	while (i < size)
	{
		new[i] = start[i];
		i++;
	}
	return ((void *)new);
}

t_node	*create_node(t_token **token, int type)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node) * 1);
	if (!new)
		return (NULL);
	new->type = type;
	if (token)
	{
		new->use.content = expander(*token);
		*token = munch_token(token);
	}
	else
		new->use.content = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_node	*parse_pipeline(t_token **token)
{
	t_node	*node;
	t_node	*new;

	if (TYPE == EOL)
		return (NULL);
	new = NULL;
	node = parse_cmd(token);
	if (TYPE == OR)
	{
		new = create_node(token, OR);
		if (!new)
			return (NULL);
		new->left = node;
		if (TYPE != EOL)
		{
			new->right = parse_pipeline(token);
			if ((new->right)->type != CMD && (new->right)->type != SUBSHELL)
				new->right = create_node(NULL, ERROR);
		}
	}
	else
		new = node;
	return (new);
}

t_node	*parse_cmd(t_token **token)
{
	t_node	*node;
	t_node	*new;

	if (TYPE == EOL)
		return (NULL);
	new = NULL;
	node = parse_simple_cmd(token);
	if (TYPE == LEFT_PAREN)
	{
		new = create_node(token, SUBSHELL);
		if (!new)
			return (NULL);
		new->right = parse_cmd(token);
		if (TYPE != RIGHT_PAREN)
			return (create_node(NULL, ERROR));
		if (TYPE == RIGHT_PAREN)
			munch_token(token);
	}
	else
	{
		new = node;
	}
	return (new);
}

t_node	*node_addback(t_node *node, t_node *new, int mode)
{
	t_node	*tmp;

	if (!node)
	{
		node = new;
		return (node);
	}
	tmp = node;
	if (mode == 0)
	{
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = new;
	}
	if (mode == 1)
	{
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new;
	}
	return (node);
}

t_node	*parse_simple_cmd(t_token **token)
{
	t_node	*new;

	new = create_node(NULL, CMD);
	while (TYPE == LESS || TYPE == DLESS || TYPE == GREAT
		|| TYPE == DGREAT || TYPE == WORD)
	{
		if ((*token)->type == LESS || (*token)->type == GREAT
			|| TYPE == DLESS || TYPE == DGREAT)
			new = node_addback(new, parse_io_redirect(token), LEFT);
		else if (TYPE == WORD)
			new = node_addback(new, parse_word(token), RIGHT);
		else
			break ;
	}
	return (new);
}

t_node	*parse_word(t_token **token)
{
	t_node	*new;

	new = create_node(token, WORD);
	return (new);
}

t_node	*parse_cmd_prefix(t_token **token)
{
	t_node	*new;

	new = create_node(token, (*token)->type);
	if ((*token)->type == WORD)
		new->right = parse_io_file(token);
	else
	{
		new->type = ERROR;
		new->use.content = "ERROR";
	}
	return (new);
}

t_node	*parse_io_redirect(t_token **token)
{
	t_node	*new;

	if (TYPE == DLESS)
		new = parse_io_here(token);
	else
		new = parse_cmd_prefix(token);
	return (new);
}

t_node	*parse_io_here(t_token **token)
{
	t_node	*new;

	new = NULL;
	new = create_node(token, TYPE);
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
