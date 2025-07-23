/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:08:59 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:58 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

/**
 * @brief Converts an unsigned long integer to a string.
 *
 * @param n (unsigned long) : The number to be converted.
 *
 * @return (char*) : The string representing the number.
 */
char	*ft_ultoa(unsigned long n)
{
	char	*str;
	int		len;

	len = ft_numlen(n, 10);
	str = (char *)ft_calloc(1, len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (n > 9)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	str[--len] = n + '0';
	return (str);
}
