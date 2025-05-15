/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:40 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/15 14:02:03 by stempels         ###   ########.fr       */
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
	t_token	peek1;

	peek1 = tokens->next;
	if (peek1->type == )
}
t_node	*parse_io_redirect(t_token *tokens)
{
	t_token	peek1;
	t_node	new;

	peek1 = tokens->next;
	new = parse_io_file(tokens);
	if (new)
		return (new);
	new = parse_io_here(tokens);
	return (new);
}

t_node	*parse_io_file(t_token *tokens)
{
	t_token	peek1;

	peek1 = tokens->next;
	if (token->type == DLESS || token->*(char *)content == '<' || token->*(char *)content == '>')
		if (parse_filename(tokens->next)
			/*DO SOMETHING*/;
	else
		return (NULL);
}

t_node	*parse_filename(t_token *tokens)
{
	if (tokens->type == WORD)
		/*DO SOMETHING*/
		/*IF SUCCESS RETURN NODE*/
	else
		return (NULL);
}
