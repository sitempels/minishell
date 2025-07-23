/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:50:45 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/12 19:51:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	**ft_stradup(char **arr)
{
	size_t	i;
	size_t	count;
	char	**dup;

	count = ft_stralen(arr);
	dup = ft_calloc(count + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
		{
			while (i--)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
