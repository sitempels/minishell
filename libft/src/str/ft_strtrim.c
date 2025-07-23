/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:04:22 by sjacquet          #+#    #+#             */
/*   Updated: 2024/11/04 14:04:22 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Allocates and copies `len` chars from `s1` starting at `start`.
 *
 * @param s1 (const char *) : Source string.
 * @param start (size_t) : Start index.
 * @param len (size_t) : Number of characters.
 *
 * @return (char *) : New substring or empty string.
 */
static char	*new_str(const char *s1, size_t start, size_t len)
{
	char	*str;
	size_t	i;

	if (len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[start + i];
		i++;
	}
	return (str);
}

/**
 * @function to_trim
 * @brief Checks if `c` is in `set`.
 *
 * @param set (const char *) : Characters to trim.
 * @param c (char) : Character to check.
 *
 * @return (int) : 1 if found, 0 otherwise.
 */
static int	to_trim(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * @function ft_strtrim
 * @brief Trims characters in `set` from start and end of `s1`.
 *
 * @param s1 (const char *) : String to trim.
 * @param set (const char *) : Characters to remove.
 *
 * @return (char *) : Trimmed new string or NULL.
 */
char	*ft_strtrim(const char *s1, const char *set)
{
	int	i;
	int	j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (to_trim(set, s1[i]))
		i++;
	while (to_trim(set, s1[j]))
		j--;
	return (new_str(s1, i, j - (i - 1)));
}
