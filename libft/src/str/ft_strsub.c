/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:02:35 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/30 15:06:17 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Creates a substring from `s` starting at `start` with length `len`.
 *
 * @param s (const char *) : Source string.
 * @param start (unsigned int) : Start index.
 * @param len (size_t) : Max length of substring.
 *
 * @return (char *) : New substring, or NULL on error.
 */
char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	size_t	strlen;
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (ft_strdup(""));
	if (len > strlen - start)
		len = strlen - start;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}
