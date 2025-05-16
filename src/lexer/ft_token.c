/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:05:30 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 14:17:23 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(t_type type, char *value)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->token = ft_strdup(value);
	if (!token->token)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*ft_last_token(t_token **tokens)
{
	t_token	*last;

	if (!tokens || !*tokens)
		return (NULL);
	last = *tokens;
	while (last->next)
		last = last->next;
	return (last);
}

int	ft_add_token(t_token **tokens, t_token *token)
{
	t_token	*last;

	if (!token)
		return (FAILURE);
	if (!*tokens)
	{
		*tokens = token;
		return (SUCCESS);
	}
	last = ft_last_token(tokens);
	last->next = token;
	return (SUCCESS);
}
