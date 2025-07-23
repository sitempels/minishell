/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:16:54 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:58 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

/**
 * @brief Converts an integer to a string.
 *
 * @param n (int) : The integer to be converted.
 *
 * @return (char*) : The string representing the integer.
 */
char	*ft_itoa(int n)
{
	long	num;
	char	*str;
	int		len;
	int		i;

	num = (long)n;
	len = ft_numlen(num, 10);
	str = (char *)ft_calloc(1, len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
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
