/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:25:00 by user              #+#    #+#             */
/*   Updated: 2025/07/04 13:32:51 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cpy_and_add(char *raw, char *start, size_t size);

char	*process_arg(t_shell *shell, char *start, size_t size)
{
	int	i;
	int	j;
	char	quote;
	char	*raw;

	i = 0;
	j = 0;
	while (i + j < (int)size)
	{
		if (start[i + j] == '\'' || start[i + j] == '\"')
		{
			quote = start[i + j++];
			while (start[i + j] && start[i + j] != quote)
				i++;
			j++;
		}
		i++;
	}
	raw = (char *)ft_calloc(i + (2 * j) + 1, sizeof(char));
	if (!raw)
		return (NULL);
	raw[i + (2 * j)] = '\0';
	cpy_and_add(raw, start, size);
	start = expand_string(raw, shell->env, shell->status);
	free(raw);
	return (start);
}

static void	cpy_and_add(char *raw, char *start, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (start[i] == '\'' || start[i] == '\"')
		{
			raw[i + j] = '&';
			j++;
		}
		raw[i + j] = start[i];
		i++;
	}
}
