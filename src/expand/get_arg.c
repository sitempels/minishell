/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:30:00 by user              #+#    #+#             */
/*   Updated: 2025/07/04 19:28:53 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_without(char *dst, char *src, int nbr);
static char	**get_arg_str(t_shell *shell, char *start);

char	**expand(t_shell *shell, t_token *arg, char *str)
{
	char	**argv;

	if (arg)
		argv = get_arg(shell, arg, 0);
	if (str)
		argv = get_arg_str(shell, str);
	argv = word_splitting(argv, 0, 0);
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

static char	**get_arg_str(t_shell *shell, char *arg)
{
	char	**argv;
	
	argv = (char **) malloc(sizeof(char *) * (2));
	if (!argv)
		return (NULL);
	argv[1] = NULL;
	argv[0] = process_arg(shell, arg, ft_strlen(arg));
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
			nbr = 0;
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
		res[i - (2 * nbr) - 1] = '\0';
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
		if (src[i + j] == '&'
			&& (src[i + j + 1] == '\'' || src[i + j + 1] == '\"'))
			j = j + 2;
		else
		{
			dst[i] = src[i + j];
			i++;
		}
	}
	return (dst);
}
