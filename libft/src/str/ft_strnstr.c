/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:35:20 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/30 15:09:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Locates a substring within a string,
 *        searching up to a specified length.
 *
 * @param haystack (const char *) : The string in which to search.
 * @param needle (const char *) : The substring to search for.
 * @param len (size_t) : The maximum number of characters
 *                       to search in `haystack`.
 *
 * @return (char *) : A pointer to the first occurrence of `needle`
 *                    in `haystack` within the first
 *                    `len` characters, or `NULL` if `needle` is not found.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *)haystack + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
