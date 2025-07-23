/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:37:45 by stempels          #+#    #+#             */
/*   Updated: 2025/07/15 18:11:30 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_found(t_shell *shell, t_token **new, char *cli, int *i);
static int	handle_word(char *cli);

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
		if (new && new->type == IF)
			if (ft_error(shell, 0, 2, "& ", get_errnum(NOT_H)))
				return (NULL);
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

int	match(char c, char *match_lst)
{
	int	i;

	if (c == '\0')
		return (EOL);
	i = 0;
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
	{
		shell->status = 1;
		return (ft_error(shell, 0, 2, "LEXER TOKEN", get_errnum(N_CREAT)));
	}
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
