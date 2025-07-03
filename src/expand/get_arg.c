/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:30:00 by user              #+#    #+#             */
/*   Updated: 2025/07/03 16:24:01 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_without(char *dst, char *src, int nbr);

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
	argv[nbr] = process_arg(shell, arg);
	if (!argv[nbr])
		return (NULL);
	argv[nbr] = quote_removal(argv[nbr]);
	return (argv);
}

// 
char	*quote_removal(char *str)
{
	int		i;
	int		j;
	char	*res;
	char	quote;

	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == '\'' || str[i + j] == '\"')
		{
			quote = str[i + j++];
			while (str[i + j] && str[i + j] != quote)
				i++;
			j++;
		}
		i++;
	}
	res = (char *) malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	res[i] = '\0';
	res = copy_without(res, str, i);
	free(str);
	return (res);
}


static char	*copy_without(char *dst, char *src, int nbr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < nbr)
	{
		if (src[i + j] != '\'' && src[i + j] != '\"')
		{
			dst[i] = src[i + j];
			i++;
		}
		else
			j++;
	}
	return (dst);
}
