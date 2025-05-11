/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:40 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 13:40:55 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*ft_parse_tokens(t_token *tokens)
{
	t_tree	*tree;

	if (!tokens)
		return (NULL);
	tree = NULL;
	while (tokens)
		tokens = tokens->next;
	return (tree);
}
