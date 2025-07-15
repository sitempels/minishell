/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wordsplitting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:10:49 by stempels          #+#    #+#             */
/*   Updated: 2025/07/15 12:35:17 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_count(char *str, int *nbr, char *match_lst);
static void	arg_fill(char **argv, char *str, int start, int end);
static void	handle_quote(char *str, int *k, int *j);

char	**word_splitting(char **arr, int index, int len)
{
	int		arg_nbr;
	char	**res;

	if (!arr[index])
	{
		res = (char **) malloc(sizeof(char *) * (len + 1));
		if (!res)
			return (NULL);
		res[len] = NULL;
		return (res);
	}
	arg_nbr = 0;
	arg_count(arr[index], &arg_nbr, IFS);
	res = word_splitting(arr, index + 1, len + arg_nbr);
	if (!res)
		return (NULL);
	arg_fill(res, arr[index], len, arg_nbr);
	free(arr[index]);
	if (index == 0)
		free(arr);
	return (res);
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
		if (str[i])
			(*nbr)++;
		while (str[i] && !match(str[i], match_lst))
		{
		//	if (str[i] != '&')
		//		i++;
			if (str[i] && str[i] == '&' && ((str[i + 1] == '\''
						|| str[i + 1] == '\"')))
			{
				quote = str[i + 1];
				i = i + 2;
				while (str[i] && str[i] != quote)
					i++;
			//	i++;
			}
			i++;
		}
	}
}

static void	arg_fill(char **argv, char *str, int start, int end)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (i < end)
	{
		k = 0;
		while (str[j] && match(str[j], IFS))
			j++;
		while (str[j + k] && !match(str[j + k], IFS))
		{
			if (str[j + k] && str[j + k] == '&' && ((str[j + k + 1] == '\''
						|| str[j + k + 1] == '\"')))
				handle_quote(str, &k, &j);
			k++;
		}
		argv[start + i] = (char *)malloc(sizeof(char) * (k + 1));
		if (!argv[start + i])
			return ;
		ft_strlcpy(argv[start + i], &str[j], k + 1);
		j = j + k + 1;
		i++;
	}
}

static void	handle_quote(char *str, int *k, int *j)
{
	char	quote;

	quote = str[*j + *k + 1];
	*k = *k + 2;
	while (str[*j + *k] && (str[*j + *k] != quote))
		(*k)++;
	//(*k)++;
}
