/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:30:00 by user              #+#    #+#             */
/*   Updated: 2025/07/04 13:17:28 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_without(char *dst, char *src, int nbr);

char	**expand(t_shell *shell, t_token *arg)
{
	char	**argv;

	argv = get_arg(shell, arg, 0);
	argv = word_splitting(argv[0], 0);
	argv = quote_removal(argv);
	return (argv);
}

char	**get_arg(t_shell *shell, t_token *arg, int nbr)
{
	char	**argv;

	if (!arg)
	{
		argv = (char **)ft_calloc(nbr + 1, sizeof(char *));
		if (!argv)
			return (NULL);
		return (argv);
	}
	argv = get_arg(shell, arg->next, nbr + 1);
	if (!argv)
		return (NULL);
	argv[nbr] = process_arg(shell, arg->start, arg->size);
	if (!argv[nbr])
		return (NULL);
	return (argv);
}

char	**quote_removal(char **str)
{
	int		i;
	int		j;
	int		nbr;
	char	*res;

	j = 0;
	while (str[j])
	{
		i = 0;
		while (str[j][i])
		{
			if (str[j][i] == '&'
			&& (str[j][i + 1] == '\'' || str[j][i + 1] == '\"'))
			{
				nbr++;
				i++;
			}
			i++;
		}
		res = (char *)malloc(sizeof(char) * (i - (2 * nbr)));
		if (!res)
			return (NULL);
		res[i] = '\0';
		res = copy_without(res, str[j], i);
		free(str[j]);
		str[j] = res;
		j++;
	}
	return (str);
}

static char	*copy_without(char *dst, char *src, int nbr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < nbr)
	{
		if (src[i + j] != '&'
			&& (src[i + j + 1] != '\'' || src[i + j + 1] != '\"'))
		{
			dst[i] = src[i + j];
			i++;
		}
		else
			j = j + 2;
	}
	return (dst);
}
