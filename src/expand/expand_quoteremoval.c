/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quoteremoval.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:11:02 by stempels          #+#    #+#             */
/*   Updated: 2025/07/14 20:05:32 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_size(char *str, int *i);
static char	*copy_without(char *dst, char *src, int nbr);

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
		nbr = calc_size(str[j], &i);
		res = (char *)malloc(sizeof(char) * (i - (2 * nbr) + 1));
		if (!res)
			return (NULL);
		res[i - (2 * nbr)] = '\0';
		res = copy_without(res, str[j], i - (2 * nbr));
		free(str[j]);
		str[j] = res;
		j++;
	}
	return (str);
}

static int	calc_size(char *str, int *i)
{
	int	nbr;

	nbr = 0;
	while (str[*i])
	{
		if (str[*i] == '&' && (str[*i + 1] == '\'' || str[*i + 1] == '\"'))
		{
			nbr++;
			(*i)++;
		}
		(*i)++;
	}
	return (nbr);
}

static char	*copy_without(char *dst, char *src, int nbr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < nbr)
	{
		if (src[i + j] && src[i + j] == '&' && (src[i + j + 1] == '\'' || src[i
					+ j + 1] == '\"'))
			j = j + 2;
		else if (src[i + j])
		{
			dst[i] = src[i + j];
			i++;
		}
	}
	return (dst);
}
