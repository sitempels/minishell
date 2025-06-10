/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:16:13 by stempels          #+#    #+#             */
/*   Updated: 2025/06/09 16:22:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_cli(const char *cli)
{
	size_t	i;
	char	quote;

	if (!cli || !*cli)
		return (1);
	i = 0;
	quote = 0;
	while (cli[i])
	{
		if (!quote && (cli[i] == '\'' || cli[i] == '\"'))
			quote = cli[i];
		else if (quote && cli[i] == quote)
			quote = 0;
		i++;
	}
	return (quote == 0);
}

t_token	*token_create(int type, char *start, size_t size)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->start = start;
	new->size = size;
	new->next = NULL;
	return (new);
}

// No need to return the new token, as it is added to the list
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
	new->next = NULL;
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
