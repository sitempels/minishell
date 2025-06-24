/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:37:45 by stempels          #+#    #+#             */
/*   Updated: 2025/06/24 17:45:15 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match(char c, char *match_lst);
static int	token_found(t_shell *shell, t_token **new, char *cli, int *i);
static int	handle_word(char *cli);
static int	handle_case(t_shell *shell, t_token **new, char *cli, int *i);

t_token	*lexer(t_shell *shell, t_token **token_lst, char *cli)
{
	int		i;
	t_token	*new;

	i = 0;
	new = NULL;
	while (cli[i])
	{
		if (token_found(shell, &new, cli, &i))
			break ;
		handle_case(shell, &new, cli, &i);
		token_addback(token_lst, new);
	}
	if (!cli[i])
	{
		new = token_create(EOL, &cli[i], 1);
		if (!new)
			ft_error(shell, 0, 2, "LEXER: TOKEN", get_errnum(N_CREAT));
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

static int	token_found(t_shell *shell, t_token **new, char *cli, int *i)
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
		ft_error(shell, 0, 3, "LEXER", "TOKEN", get_errnum(N_CREAT));
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

static int	handle_case(t_shell *shell, t_token **new, char *cli, int *i)
{
	t_token	*next;

	next = NULL;
	if (*new && (*new)->type == IF)
		ft_error(shell, 0, 3, "LEXER", "&", get_errnum(NOT_H));
	if (*new && (*new)->type == DLESS)
	{
		token_found(shell, &next, cli, i);
		if (!next || next->type != WORD)
		{
			free(*new);
			if (next)
				free(next);
			ft_error(shell, 0, 2, "<<", get_errnum(I_MISS));
		}
		(*new)->next = handle_heredoc(shell, next);
		if (!(*new)->next)
			ft_error(shell, 0, 2, "<<", get_errnum(I_MISS));
	}
	return (0);
}
