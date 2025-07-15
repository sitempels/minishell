/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:25:00 by user              #+#    #+#             */
/*   Updated: 2025/07/15 16:59:55 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cpy_and_add(char *raw, char *start, size_t size);
static void	cpy_between_quotes(char *raw, char *start, size_t *i, size_t *j);
static void	calc_size(char *start, int size, int *i, int *j);

char	*process_arg(t_shell *shell, char *start, size_t size)
{
	int		i;
	int		j;
	char	*raw;

	i = 0;
	j = 0;
	calc_size(start, (int)size, &i, &j);
	raw = (char *) malloc(sizeof(char) * (i + (2 * j) + 1));
	if (!raw)
		return (NULL);
	raw[i + (2 * j)] = '\0';
	cpy_and_add(raw, start, (i + (2 * j)));
	start = expand_string(shell, raw);
	return (start);
}

static void	calc_size(char *start, int size, int *i, int *j)
{
	char	quote;

	while (*i + *j < size)
	{
		if (start[*i + *j] == '\'' || start[*i + *j] == '\"')
		{
			quote = start[*i + (*j)++];
			while (start[*i + *j] && start[*i + *j] != quote)
				(*i)++;
			(*j)++;
			continue ;
		}
		if (start[*i + *j] != '\'' || start[*i + *j] != '\"')
			(*i)++;
	}
}

static void	cpy_and_add(char *raw, char *start, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i + j < size)
	{
		if (start[i] && (start[i] == '\'' || start[i] == '\"'))
			cpy_between_quotes(raw, start, &i, &j);
		else
			raw[i + j] = start[i];
		i++;
	}
}

static void	cpy_between_quotes(char *raw, char *start, size_t *i, size_t *j)
{
	char	quote;

	quote = start[*i];
	raw[*i + (*j)++] = '&';
	raw[*i + (*j)] = start[*i];
	(*i)++;
	while (start[*i] && start[*i] != quote)
	{
		raw[*i + *j] = start[*i];
		(*i)++;
	}
	raw[*i + (*j)++] = '&';
	raw[*i + *j] = start[*i];
}
