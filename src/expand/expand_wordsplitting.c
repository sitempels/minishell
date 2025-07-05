/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:10:49 by stempels          #+#    #+#             */
/*   Updated: 2025/07/05 10:07:58 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_count(char *str, int *nbr, char *match_lst);
static void	arg_fill(char **argv, char *str, int start, int end);

char	**word_splitting(char **arr, int index, int len)
{
	char	**argv;
	int		arg_nbr;

	if (!arr[index] || !*arr[index])
	{
		argv = malloc(sizeof(char *) * (len + 1));
		if (!argv)
			return (NULL);
		argv[len] = NULL;
		return (argv);
	}
	arg_nbr = 0;
	arg_count(arr[index], &arg_nbr, IFS);
	argv = word_splitting(arr, index + 1, len + arg_nbr);
	if (!argv)
		return (NULL);
	arg_fill(argv, arr[index], len, arg_nbr);
	return (argv);
}

static void	arg_count(char *str, int *nbr, char *match_lst)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		while (str[i] && match(str[i], match_lst))
			i++;
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
		}
		if (str[i])
			(*nbr)++;
		while (str[i] && !match(str[i], match_lst))
			i++;
	}
}

static void	arg_fill(char **argv, char *str, int start, int end)
{
	int		i;
	int		j;
	int		k;
	char	quote;

	i = -1;
	j = 0;
	while (++i < end)
	{
		while (str[j] && match(str[j], IFS))
			j++;
		if (str[j] && (str[j] == '\'' || str[j] == '\"'))
		{
			quote = str[j++];
			while (str[j] && str[j] != quote)
				j++;
		}
		k = 0;
		while (str[j + k] && !match(str[j + k], IFS))
			k++;
		argv[start + i] = (char *)malloc(sizeof(char) * (k + 1));
		if (!argv[start + i])
			return ;
		ft_strlcpy(argv[start + i], &str[j], k + 1);
	}
}
