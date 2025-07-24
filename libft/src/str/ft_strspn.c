/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:17:16 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/30 15:06:17 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 *
 * @brief Gets the length of the initial segment of `s`
 * containing only `accept` chars.
 *
 * @param s (const char *) : The string to scan.
 * @param accept (char *) : The set of accepted characters.
 *
 * @return (size_t) : Length of the matching initial segment.
 */
size_t	ft_strspn(const char *s, char *accept)
{
	size_t	len;
	char	*tmp;

	tmp = accept;
	len = 0;
	while (s[len])
	{
		while (*tmp)
		{
			if (s[len] == *tmp)
				break ;
			tmp++;
		}
		if (*tmp == '\0')
			break ;
		len++;
	}
	return (len);
}
