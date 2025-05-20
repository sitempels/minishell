/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:45:26 by stempels          #+#    #+#             */
/*   Updated: 2025/05/19 14:45:30 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_simple_cmd(t_token *tokens);
t_node	*parse_filename(t_token *tokens);
t_node	*parse_cmd_prefix(t_token *tokens);
t_node	*parse_cmd_suffix(t_token *tokens);
t_node	*parse_io_redirect(t_token *tokens);
t_node	*parse_io_file(t_token *tokens);

t_node	*ft_parser(t_token *tokens)
{
	t_node	*tree;

	if (!tokens)
		return (NULL);
	tree = ft_new_tree(0, NULL, NULL);
	if (!tree)
		return (NULL);
	while (tokens)
		tokens = tokens->next;
	return (tree);
}

t_node	*parse_simple_cmd(t_token *tokens)
{
	t_node	*new;

	new = parse_cmd_prefix(tokens);
	if (new)
	{
		new->left = parse_cmd_word(tokens);
		if (new->left)
			new->right = parse_cmd_suffix(tokens);
		return (new);
	}
	new = parse_cmd_name(tokens);
	if (new)
		new->left = parse_cmd_suffix(tokens->next);
	return (new);
}

t_node	*parse_cmd_prefix(t_token *tokens) //!! NOT SURE THE LOGIC WORK LIKE THAT
{
	t_node	*new;

	new = NULL;
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

	new = NULL;
	new = parse_io_redirect(tokens);
	if (new)
		return (new);
	new = parse_cmd_suffix(tokens);
	if (new)
		return (new);
	if (tokens->type == WORD)
	{
		/*DO SOMETHING*/;
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
	new = parse_io_here(tokens);
	return (new);
}

t_node	*parse_io_file(t_token *tokens)
{
	t_node	*new;

	new = NULL;
	if (token->type == LESS || token->type == GREAT || token->type == DLESS)
	{
		new = (t_node *) malloc(sizeof(t_node) * 1);
		if (!new)
		{
			take_node(tokens);
			return (/*RETURN ERROR_NODE FOR ERROR HANDLING*/);
		}
		new->type = token->type; //!!! WON'T WORK AS IT IS, NEED THINKERING
		new->use.fct = /*handle_io*/;
		new->parent = NULL;
		new->left = parse_filename(tokens->next);
		if (new->left)
			(new->left)->parent = new;
		new->right = NULL;
		take_node(tokens);
	}
	return (new);
}

t_node	*parse_filename(t_token *tokens)
{
	t_node	*new;
	char	*content;

	new = NULL;
	content = (char *)tokens->content;
	if (tokens->type == WORD)
	{
		new = (t_node *) malloc(sizeof(t_node) * 1);
		if (!new)
		{
			take_node(tokens);
			return (/*ERROR HANDLING*/);
		}
		new->type = FILENAME;
		new->use.content = (void *) ft_substr(content, 0, tokens->size);
		new->parent = NULL;
		new->left = NULL;
		new->right = NULL;
		take_node(tokens);
	}
	return (new);
}
