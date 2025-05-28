/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/05/28 12:11:36 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_node	*create_node(t_token **tokens, int type);
t_token	*munch_token(t_token **token);
//t_node	*parse_pipeline(t_token *token);
t_node	*parse_word(t_token **token);
t_node	*parse_cmd(t_token **token, int iter);
/*
t_node	*parse_cmd_prefix(t_token *tokens);
t_node	*parse_cmd_suffix(t_token *tokens);
t_node	*parse_io_redirect(t_token *tokens);
t_node	*parse_io_file(t_token *tokens);
t_node	*parse_filename(t_token *tokens);
*/
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
	tree = parse_cmd(&token, 0);
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
//	free(*token);
	*token = tmp;
	return (target);
}

void	*expander(t_token **token)
{
	int	i;
	int	size;
	char	*start;
	char	*new;

	if (TYPE == EOL)
		return (NULL);
	start = (TOKEN->start);
	size = TOKEN->size;
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
//	if (type != CMD)
	new->use.content = expander(token);
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
t_node	*parse_cmd(t_token **token, int	iter)
{
	t_node	*new;

	if (TYPE == EOL)
		return (NULL);
//	if (iter == 0)
//		new = create_node(token, CMD);
/*	if (!new)
		panic(.tkt);*/
/*
	if (TYPE == LESS)
	{
		new->left = parse_io_redirect(TOKEN);
		if (N_TOKEN)
			new->right = parse_cmd(N_TOKEN, iter + 1);
	}
*/
	if (TYPE == WORD)
		{
		new->left = parse_word(token);
	}
	if (N_TOKEN)
		new->right = parse_cmd(&N_TOKEN, iter + 1);
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

t_node	*parse_word(t_token **token)
{
	t_node	*new;
//	t_token	*target;

//	target = munch_token(token); 
	if (TYPE == EOL)
		return (NULL);
	new = create_node(token, WORD);
	if (!new)
		return (NULL);	
//	if (token && token->type == WORD)
//		new->left = parse_word(token);
//	if (token && token->type == GREAT)
//		new->left = parse_cmd(token, 0);
	return (new);
}
/*
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
*/
/*
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
			return (NULL);
		new->right = NULL;
	}
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
	}
	return (new);
}
*/
