/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:54:06 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:35:22 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

/**
 * @brief Converts a string to an unsigned long integer.
 *
 * @param str (const char*) : The string to be converted.
 *
 *
 * @return (unsigned long) : The unsigned long integer resulting
 * from the conversion.
 */
unsigned long	ft_atoul(const char *str)
{
	unsigned long	result;
	int				sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (ft_issign(*str))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (sign == -1)
		return (0);
	return (result);
}
