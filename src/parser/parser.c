/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/05/27 13:18:10 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_node	*create_node(t_token *tokens, int type);
void	munch_token(t_token **token);
t_node	*parse_pipeline(t_token *token);
t_node	*parse_word(t_token *tokens);
t_node	*parse_cmd(t_token *tokens, int iter);
t_node	*parse_cmd_prefix(t_token *tokens);
t_node	*parse_cmd_suffix(t_token *tokens);
t_node	*parse_io_redirect(t_token *tokens);
t_node	*parse_io_file(t_token *tokens);
t_node	*parse_filename(t_token *tokens);

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
void	munch_token(t_token **token)
{
	t_token	*tmp;

	tmp = (*token)->next;
	free(*token);
	token = &tmp;
	return ;
}

void	*expander(t_token *token)
{
	int	i;
	int	size;
	char	*start;
	char	*new;

	start = (token->start);
	size = token->size;
	new = (char *) malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = '\0';
	i = 0;
	while (i < size + 1)
	{
		new[i] = start[i];
		i++;
	}
	return ((void *)new);
}

t_node	*create_node(t_token *tokens, int type)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node) * 1);
	if (!new)
		return (NULL);
	new->type = type;
	if (type != CMD)
		new->use.content = expander(tokens);
	new->left = NULL;
	new->right = NULL;
	return (new);
}

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

t_node	*parse_cmd(t_token *token, int	iter)
{
	t_node	*new;

	if (!token)
		return (NULL);
	if (iter == 0)
		new = create_node(token, CMD);
/*	if (!new)
		panic(.tkt);*/
/*
	if (token->type == LESS)
	{
		new->left = parse_io_redirect(token);
		new->right = parse_word(token->next);
	}
*/
	if (token->type == WORD)
	{
		new->left = parse_word(token);
		new->right = parse_cmd(token->next, iter + 1);
	}
/*
	if (token->type == GREAT)
	{
		new->left = parse_cmd_suffix(token);
		new->right = parse_word(token->next);
	}
*/
//	take(tokens);
	return (new);
}
t_node	*parse_word(t_token *token)
{
	t_node	*new;

	new = create_node(token, WORD);
	if (!new)
		return (NULL);	
	munch_token(&token);
	if (token && token->type == WORD)
		new->left = parse_word(token);
	if (token && token->type == GREAT)
		new->left = parse_cmd(token, 0);
	return (new);
}

t_node	*parse_cmd_prefix(t_token *tokens) //!! NOT SURE THE LOGIC WORK LIKE THAT
{
	t_node	*new;

	new = create_node(tokens, LESS);
	new = parse_io_redirect(tokens);
	if (new)
		return (new);
	new = parse_cmd_prefix(tokens);
	if (new)
		return (new);
	return (new);
}

t_node	*parse_cmd_suffix(t_token *tokens) //!! NOT SURE THE LOGIC WORK LIKE THAT
{
	t_node	*new;

	new = parse_io_redirect(tokens);
	if (new)
		return (new);
	new->left = parse_cmd_suffix(tokens);
	if (new)
		return (new);
	if (tokens->type == WORD)
	{
		new = parse_word(tokens);
		return (new);
	}
	new = parse_cmd_suffix(tokens);
	return (new);
}

t_node	*parse_io_redirect(t_token *tokens)
{
	t_node	*new;

	new = parse_io_file(tokens);
	if (new)
		return (new);
//	new = parse_io_here(tokens);
	return (new);
}

t_node	*parse_io_file(t_token *tokens)
{
	t_node	*new;

	new = NULL;
	if (tokens->type == LESS || tokens->type == GREAT || tokens->type == DLESS)
	{
		new = create_node(tokens, tokens->type);
		if (!new)
		{
			//take_node(tokens);
			return (NULL);
		}
		new->type = tokens->type;
		new->use.content = tokens->start;
		new->left = parse_filename(tokens->next);
//		if (new->left)
//			(new->left)->parent = new;
		new->right = NULL;
	}
	return (new);
}

t_node	*parse_filename(t_token *tokens)
{
	t_node	*new;
	char	*content;

	new = NULL;
	content = tokens->start;
	if (tokens->type == WORD)
	{
		new = (t_node *) malloc(sizeof(t_node) * 1);
		if (!new)
		{
			//take_node(tokens);
			return (NULL);
		}
		new->type = FILENAME;
		new->use.content = tokens->start;
		new->parent = NULL;
		new->left = NULL;
		new->right = NULL;
	}
	return (new);
}
