/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:37:45 by stempels          #+#    #+#             */
/*   Updated: 2025/06/03 16:32:15 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match(char c, char *match_lst);
static int	token_found(t_token **token_lst, char *cli, int *i);
static int	handle_word(char *cli);

t_token	*lexer(t_token **token_lst, char *cli)
{
	int		i;
	t_token	*new;

	i = 0;
	while (cli[i])
	{
		while (cli[i] && match(cli[i], SEPARATOR))
			i++;
		if (token_found(token_lst, cli, &i))
			return (NULL);
	}
	new = token_create(EOL, "\0", 1);
	token_addback(token_lst, new);
	return (*token_lst);
}

static int	match(char c, char *match_lst)
{
	int	i;

	i = 0;
	while (match_lst[i])
	{
		if (match_lst[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

static int	token_found(t_token **token_lst, char *cli, int *i)
{
	int		type;
	int		size;
	t_token	*new;

	size = 1;
	type = match(cli[*i], OPERATOR);
	if (type > 0 && cli[*i + 1] && cli[*i] == cli[*i + 1])
	{
		type = type + DOUBLE_ADJUST;
		size++;
	}
	if (type == 2)
		return (write(1, "& not handled\n", 14), 1);
	if (type == 0)
		size = handle_word(&cli[*i]);
	new = token_create(type, &cli[*i], size);
	if (!new)
		return (FAILURE);
	token_addback(token_lst, new);
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
