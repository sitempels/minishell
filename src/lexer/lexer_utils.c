/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:16:13 by stempels          #+#    #+#             */
/*   Updated: 2025/07/23 14:45:51 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pass_quote(const char *cli, size_t *i)
{
	char	quote;

	quote = 0;
	quote = cli[(*i)++];
	while (cli[*i] && cli[*i] != quote)
		(*i)++;
	if (cli[*i])
		return (0);
	return (1);
}

int	is_valid_cli(t_shell *shell, const char *cli)
{
	int		paren;
	size_t	i;

	if (!cli || !*cli)
		return (1);
	i = 0;
	paren = 0;
	while (cli[i])
	{
		if (cli[i] == '\'' || cli[i] == '\"')
			if (pass_quote(cli, &i))
				return (ft_error(shell, 0, 1, "Unclosed quote"));
		if (cli[i] == '(')
			paren = 1;
		if (paren == 1 && cli[i] == ')')
			paren = 0;
		if (paren != 1 && cli[i] == ')')
			return (ft_error(shell, 0, 2, get_errnum(NEAR), "')'"));
		if (cli[i])
			i++;
	}
	if (paren == 1)
		return (ft_error(shell, 0, 2, get_errnum(NEAR), "'('"));
	return (paren);
}

t_token	*token_create(int type, char *start, size_t size)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token) * 1);
	if (!token)
		return (NULL);
	token->type = type;
	token->start = start;
	token->size = size;
	token->next = NULL;
	return (token);
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
