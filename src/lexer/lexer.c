/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:37:45 by stempels          #+#    #+#             */
/*   Updated: 2025/06/16 13:08:43 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match(char c, char *match_lst);
static int	token_found(t_token **new, char *cli, int *i);
static int	handle_word(char *cli);
static int	handle_case(t_token **new, char *cli, int *i);

t_token	*lexer(t_token **token_lst, char *cli)
{
	int		i;
	t_token	*new;

	i = 0;
	new = NULL;
	while (cli[i])
	{
		if (token_found(&new, cli, &i))
			break ;
		if (handle_case(&new, cli, &i))
			return (NULL);
		token_addback(token_lst, new);
	}
	if (!cli[i])
	{
		new = token_create(EOL, &cli[i], 1);
		token_addback(token_lst, new);
	}
	return (*token_lst);
}

static int	match(char c, char *match_lst)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (EOL);
	while (match_lst[i])
	{
		if (match_lst[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

static int	token_found(t_token **new, char *cli, int *i)
{
	int	type;
	int	size;

	while (cli[*i] && match(cli[*i], SEPARATOR))
		*i = *i + 1;
	if (!cli[*i])
		return (1);
	size = 1;
	type = match(cli[*i], OPERATOR);
	if (type > 0 && cli[*i + 1] && cli[*i] == cli[*i + 1])
	{
		type = type + (OR_IF - OR);
		size++;
	}
	if (type == 0)
		size = handle_word(&cli[*i]);
	*new = token_create(type, &cli[*i], size);
	if (!new)
		return (1);
	*i = *i + size;
	return (0);
}

static int	handle_word(char *cli)
{
	int	i;

	i = 0;
	while (cli[i] && !match(cli[i], DELIMITERS))
	{
		if (cli[i] == '\'')
			while (cli[++i] && cli[i] != '\'')
				continue ;
		if (cli[i] == '\"')
			while (cli[++i] && cli[i] != '\"')
				continue ;
		i++;
	}
	return (i);
}

static int	handle_case(t_token **new, char *cli, int *i)
{
	t_token	*next;

	if (*new && (*new)->type == IF)
		return (write(1, "& not handled\n", 14));
	if (*new && (*new)->type == DLESS)
	{
		token_found(&next, cli, i);
		if (next->type != WORD)
			return (1);
		(*new)->next = handle_heredoc(next);
	}
	return (0);
}
