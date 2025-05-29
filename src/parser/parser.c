/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/05/29 15:58:36 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*UTILS FUNCTIONS*/
t_node	*create_node(t_token *tokens, int type);
t_token	*munch_token(t_token **token);
void	*expander(t_token *token);
/**/
/*DESCENT FUNCTIONS - BY ORDER OF DESCENT*/
t_node	*parse_pipeline(t_token *token);
t_node	*parse_cmd(t_token *token);
t_node	*parse_simple_cmd(t_token *token);
t_node	*parse_word(t_token *token);
t_node	*parse_cmd_prefix(t_token *tokens);
//t_node	*parse_cmd_suffix(t_token *tokens);
//t_node	*parse_io_redirect(t_token *tokens);
t_node	*parse_io_file(t_token *tokens);
t_node	*parse_filename(t_token *tokens);
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
	tree = parse_pipeline(token);
	if (!tree)
		return (NULL);
	return (tree);
}

/*
t_token	*munch_token(t_token *token)
{
	t_token	tmp;

	tmp = *(token)->next;
	free(token);
	token = &tmp;
	return (target);
}
*/

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

t_node	*create_node(t_token *token, int type)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node) * 1);
	if (!new)
		return (NULL);
	new->type = type;
	if (token)
		new->use.content = expander(token);
	else
		new->use.content = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_node	*parse_pipeline(t_token *token)
{
	t_node	*node;
	t_node	*new;

	if (token->type == EOL)
		return (NULL);
	node = parse_cmd(token);
	if (TYPE == OR)
	{
		new = create_node(token, OR);
		if (!new)
			return (NULL);
		new->left = node;
		if (token->next)
		{
			new->right = parse_cmd(token->next);
			if ((new->right)->type != CMD && (new->right)->type != SUBSHELL)
				new->right = create_node(NULL, ERROR);
		}
	}
	else
		new = node;
	return (new);
}

t_node	*parse_cmd(t_token *token)
{
	t_node	*node;
	t_node	*new;

	new = NULL;
	verif = 0;
	if (token->type == EOL)
		return (NULL);
	node = parse_simple_cmd(token);
	if (token->type == LEFT_PAREN)
	{
		verif = 1;
		new = create_node(token, SUBSHELL);
		if (!new)
			return (NULL);
		*token = *(token->next);
		new->right = parse_simple_cmd(token);
	}
	else
		new = node;
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

t_node	*parse_simple_cmd(t_token *token)
{
	t_node	*new;

	new = create_node(NULL, CMD);
	while (TYPE == LESS || TYPE == DLESS || TYPE == GREAT
		|| TYPE == DGREAT || TYPE == WORD)
	{
		if (token->type == LESS || token->type == GREAT)
			new = node_addback(new, parse_cmd_prefix(token), LEFT);
		else if (token->type == WORD)
			new = node_addback(new, parse_word(token), RIGHT);
		else
			break ;
		*token = *(token->next);
	}
	return (new);
}

t_node	*parse_word(t_token *token)
{
	t_node	*new;

	new = create_node(token, WORD);
	return (new);
}

t_node	*parse_cmd_prefix(t_token *token)
{
	t_node	*new;

	new = create_node(token, token->type);
	if ((token->next)->type == WORD)
	{
		new->right = parse_io_file(token->next);
		*token = *(token->next);
	}
	else
	{
		new->type = ERROR;
		new->use.content = "ERROR";
	}
	return (new);
}

/*
t_node	*parse_io_redirect(t_token *tokens)
{
	t_node	*new;

	new = parse_io_file(tokens);
	if (new)
		return (new);
//	new = parse_io_here(tokens);
	return (new);
}
*/

t_node	*parse_io_file(t_token *token)
{
	t_node	*new;

	new = parse_filename(token);
	return (new);
}

t_node	*parse_filename(t_token *token)
{
	t_node	*new;

	new = NULL;
	if (TYPE == WORD)
	{
		new = create_node(token, FILENAME);
		if (!new)
			return (NULL);
	}
	return (new);
}
