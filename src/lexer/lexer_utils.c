/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:16:13 by stempels          #+#    #+#             */
/*   Updated: 2025/06/04 13:37:38 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_create(int type, char *start, size_t size)
{
	t_token	*new;

	new = (t_token *) ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->start = start;
	new->size = size;
	new->next = NULL;
	return (new);
}

t_token	*token_addback(t_token **token_lst, t_token *new)
{
	t_token	*last;

	if (!(*token_lst))
	{
		*token_lst = new;
		return (*token_lst);
	}
	last = token_last(token_lst);
	last->next = new;
	return (*token_lst);
}

t_token	*token_last(t_token **token_lst)
{
	t_token	*last;

	last = *token_lst;
	while (last->next)
		last = last->next;
	return (last);
}
