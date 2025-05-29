/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/05/29 13:44:00 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_node	*create_node(t_token *tokens, int type);
t_token	*munch_token(t_token **token);
//t_node	*parse_pipeline(t_token *token);
t_node	*parse_word(t_token *token);
t_node	*parse_cmd(t_token *token, int iter);

t_node	*parse_cmd_prefix(t_token *tokens);
t_node	*parse_cmd_suffix(t_token *tokens);
t_node	*parse_io_redirect(t_token *tokens);
t_node	*parse_io_file(t_token *tokens);
t_node	*parse_filename(t_token *tokens);

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
	tree = parse_cmd(token, 0);
	if (!tree)
		return (NULL);
	return (tree);
}

t_token	*munch_token(t_token **token)
{
	t_token	*target;
	t_token	*tmp;

	tmp = (*token)->next;
	target = *token;
	*token = tmp;
	return (target);
}

void	*expander(t_token *token)
{
	int	i;
	int	size;
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
/*
t_node	*parse_pipeline(t_token *token)
{
	t_node	*node;
	t_node	*new;

	node = parse_cmd(token, 0);
	if (TYPE == OR)	
	{
		new = create_node(token, OR);
		if (!new)
			return (NULL);
		munch_token(&token);
		new->left = node;
		new->right = parse_cmd(token, 0);
	}
	else
		new = node;
	return (new);
}
*/
t_node	*node_addback(t_node *node, t_node *new, int mode)
{
	t_node	*tmp;

	if (node == NULL)
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

t_node	*parse_cmd(t_token *token, int	iter)
{
	t_node	*new;
	int	LEFT = 0;
	int	RIGHT = 1;

	new = create_node(NULL, CMD);
	while (token->type != EOL)
	{
		if (token->type == LESS || token->type == GREAT)
		{
			new = node_addback(new, parse_cmd_prefix(token), LEFT);
//			token = (token->next);
		}
		else if (token->type == WORD)
		{
			new = node_addback(new, parse_word(token), RIGHT);
		}
/*
	else if (token->type == GREAT || token->type == DGREAT)
	{
		new = node_addback(new, parse_cmd_suffix(token), LEFT);
		token = (token->next);
	}
*/
/*	if (token->type == LESS || token->type == DLESS || token->type == WORD || token->type == GREAT || token->type == DGREAT)
		new = node_addback(new, parse_cmd(token->next, iter + 1), RIGHT);
	*/
		else
			break ;
		token = token->next;
	}
	return (new);
}

t_node	*parse_word(t_token *token)
{
	t_node	*new;

	new = create_node(token, WORD);
	return (new);
}

t_node	*parse_cmd_prefix(t_token *token) //!! NOT SURE THE LOGIC WORK LIKE THAT
{
	t_node	*new;

	new = create_node(token, token->type);
	if (/*token->type == LESS && */(token->next)->type == WORD)
	{
		new->right = parse_io_file(token->next);
		*token = *(token->next);
	}
	else
	{
		new->type = ERROR;
		new->use.content = "ERROR";
	}
//	if (token->type == DLESS)
//		new->left = parse_io_here(token);
	return (new);
}


t_node	*parse_cmd_suffix(t_token *token) //!! NOT SURE THE LOGIC WORK LIKE THAT
{
	t_node	*new;
/*
	if (token->type == WORD)
	{
		new = create_node(token, WORD);
		if (token->next)
			new->right = parse_cmd_suffix(token->next);
	}
*/
	new = create_node(token, token->type);
	if (token->type == GREAT && (token->next)->type == WORD)
	{
		new->right = parse_io_file(token->next);
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

	if (TYPE == WORD)
	{
		new = create_node(token, FILENAME);
		if (!new)
			return (NULL);
//		munch_token(&token);
	}
	return (new);
}
