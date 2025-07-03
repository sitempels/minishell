/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:30:00 by user              #+#    #+#             */
/*   Updated: 2025/07/03 05:21:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	quote;

	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == '\'' || str[i + j] == '\"')
		{
			quote = str[i + j++];
			while (str[i + j] && str[i + j] != quote)
			{
				str[i] = str[i + j];
				i++;
			}
			j++;
			continue ;
		}
		str[i] = str[i + j];
		i++;
	}
	str = (char *)realloc(str, i);
	str[i] = '\0';
	return (str);
}
