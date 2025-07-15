/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:09:25 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:23:50 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Finds the first occurrence of `c` in `str`.
 *
 * @param str (const char *) : String to search.
 * @param c (int) : Character to find.
 *
 * @return (char *) : Pointer to `c` in `str`, or NULL if not found.
 */
char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == cc)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == cc)
		return ((char *)&str[i]);
	return (NULL);
}
