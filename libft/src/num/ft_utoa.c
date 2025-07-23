/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:51:57 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:58 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

/**
 * @brief Converts an unsigned integer to a string.
 *
 * @param n (unsigned int) : The unsigned integer to be converted.
 *
 * @return (char*) : A string representation of the unsigned integer.
 */
char	*ft_utoa(unsigned int n)
{
	unsigned int	num;
	char			*str;
	int				len;
	int				i;

	num = n;
	len = ft_numlen(n, 10);
	str = (char *)ft_calloc(1, len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = len - 1;
	while (num > 9)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	str[i] = num + '0';
	return (str);
}
