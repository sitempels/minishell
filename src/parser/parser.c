/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:25 by stempels          #+#    #+#             */
/*   Updated: 2025/05/26 13:20:37 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_node	*create_node(t_token *tokens, int type);
t_node	*parse_word(t_token *tokens);
t_node	*parse_cmd(t_token *tokens);
t_node	*parse_cmd_prefix(t_token *tokens);
t_node	*parse_cmd_suffix(t_token *tokens);
t_node	*parse_io_redirect(t_token *tokens);
t_node	*parse_io_file(t_token *tokens);
t_node	*parse_filename(t_token *tokens);

t_node	*parser(t_token *tokens)
{
	t_node	*tree;

	if (!tokens)
		return (NULL);
	tree = parse_cmd(tokens);
	if (!tree)
		return (NULL);
	return (tree);
}

t_node	*create_node(t_token *tokens, int type)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node) * 1);
	if (!new)
		return (NULL);
	new->type = type;
	new->use.content = tokens->start;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_node	*parse_cmd(t_token *tokens)
{
	t_node	*new;

	if (!tokens)
		return (NULL);
	new = create_node(tokens, CMD);
/*	if (!new)
		panic(.tkt);*/
	if (tokens->type == LESS)
	{
		new->left = parse_io_redirect(tokens);
		new->right = parse_cmd(tokens->next);
	}
	if (tokens->type == WORD)
	{
		new->right = parse_word(tokens);
		//parse_cmddd(tokens->next);
	}
	if (tokens->type == GREAT)
	{
		new->left = parse_cmd_suffix(tokens);
		new->right = parse_cmd(tokens->next);
	}
//	take(tokens);
	return (new);
}

t_node	*parse_word(t_token *tokens)
{
	t_node	*new;

	new = create_node(tokens, WORD);
/*	if (!new)
		panic(.tkt);*/
	if (tokens->next && (tokens->next)->type == WORD)
		new->left = parse_word(tokens->next);
//	take(tokens);
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
