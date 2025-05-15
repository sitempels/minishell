/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:40 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/12 19:52:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*ft_parse_tokens(t_token *tokens)
{
	t_tree	*tree;

	if (!tokens)
		return (NULL);
	tree = ft_new_tree(0, NULL, NULL);
	if (!tree)
		return (NULL);
	while (tokens)
		tokens = tokens->next;
	return (tree);
}
