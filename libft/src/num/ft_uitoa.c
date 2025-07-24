/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:12:47 by sjacquet         #+#    #+#             */
/*   Updated: 2025/05/12 23:12:52 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

/**
 * @brief Converts an unsigned integer to a string.
 *
 * @param n (unsigned int) : The unsigned integer to be converted.
 *
 * @return (char*) : The string representation of the unsigned integer.
 */
char	*ft_uitoa(unsigned int n)
{
	unsigned int	num;
	char			*str;
	int				len;
	int				i;

	num = n;
	len = ft_numlen(num, 10);
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
