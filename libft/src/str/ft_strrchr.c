/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:11:27 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/30 15:06:17 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Finds the last occurrence of a character in a string.
 *
 * @param str (const char *) : The string to search.
 * @param c (int) : The character to find (passed as an integer).
 *
 * @return (char *) : Pointer to the last occurrence of `c` or `NULL`.
 */
char	*ft_strrchr(const char *str, int c)
{
	char	*res;
	char	cc;

	cc = (char)c;
	res = NULL;
	while (*str)
	{
		if (*str == cc)
			res = (char *)str;
		str++;
	}
	if (cc == '\0')
		return ((char *)str);
	return (res);
}
