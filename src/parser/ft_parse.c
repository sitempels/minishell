/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:40 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/15 15:29:16 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*ft_parser(t_token *tokens)
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
		new = parse_cmd_word(tokens->next);
		if (new)
			*new = parse_cmd_suffix(tokens->new);
		return (new);
	}
	new = parse_cmd_name(tokens);
	if (new)
		*new = parse_cmd_suffix(tokens->next);
	return (new);
}

t_node	*parse_cmd_suffix(tokens) //!! NOT SURE THE LOGIC WORK LIKE THAT
{
	t_node	*new;

	new = NULL;
	new = parse_io_redirect(tokens);
	if (new)
		return (new);
	new = parse_cmd_suffix(tokens);
	if (new)
		return (new);
	if (token->type == ASSIGNMENT_WORD)
	{
		/*DO SOMETHING*/; //-->NEED TO LOOK WHAT ARE ASSIGNMENT WORD
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
			return (/*ERROR HANDLING*/);
		}
		new->type = token->type; //!!! WON'T WORK AS IT IS, NEED THINKERING
		new->use.pointer_fct = /*FCT NEEDED*/
		new->parent = NULL;
		new->left = parse_filename(tokens->next);
		if (new->left)
			new->left->parent = new;
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
	}
	take_node(tokens);
	return (new);
}
