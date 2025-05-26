/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:47:25 by stempels          #+#    #+#             */
/*   Updated: 2025/05/26 10:50:23 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		match(char c, char *match_lst);
static int		token_found(t_token **token_lst, char *cli, int *i);
static int		token_addback(t_token **tokens, t_token *new);
static t_token	*token_create(int type, char *start, size_t size);

t_token	**lexer(t_token **token_lst, char *cli)
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
	return (token_lst);
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

	type = match(cli[*i], OPERATOR);
	size = 1;
	if (type > 0 && cli[*i + 1] && cli[*i] == cli[*i + 1])
	{
		type = type + DOUBLE_ADJUST;
		size++;
	}
	if (type == 0)
		while (cli[*i + size] && !match(cli[*i + size], DELIMITERS))
			size++;
	new = token_create(type, &cli[*i], size);
	if (!new)
		return (FAILURE);
	token_addback(token_lst, new);
	*i = *i + size;
	return (0);
}

static t_token	*token_create(int type, char *start, size_t size)
{
	t_token	*new;

	new = (t_token *) malloc(1 * sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->start = start;
	new->size = size;
	new->next = NULL;
	return (new);
}

static int	token_addback(t_token **token_lst, t_token *new)
{
	t_token	*last;

	if (!token_lst)
		return (FAILURE);
	if (!(*token_lst))
	{
		*token_lst = new;
		return (SUCCESS);
	}
	last = *token_lst;
	while (last->next)
		last = last->next;
	last->next = new;
	return (SUCCESS);
}
