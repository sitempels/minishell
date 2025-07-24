/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:11:27 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:58 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

/**
 * @brief Checks if the result exceeds the bounds of a long integer.
 *
 * @param result (long) : The result to be checked.
 * @param sign (int) : The sign of the result (1 for positive, -1 for negative).
 *
 * @return (long) : Returns LONG_MAX or LONG_MIN if the result overflows,
 * or 1 if the result is within valid bounds.
 */
long	ft_checkover_underflow(long result, int sign)
{
	if (sign == 1 && result > LONG_MAX)
		return (LONG_MAX);
	if (sign == -1 && result < LONG_MIN)
		return (LONG_MIN);
	return (1);
}

/**
 * @brief Converts a string to a long integer.
 *
 * @param str (const char *) : The string to be converted.
 *
 * @return (long) : The converted long integer value.
 */
long	ft_atol(const char *str)
{
	long	result;
	long	check;
	int		sign;

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
		check = ft_checkover_underflow(result, sign);
		if (check != 1)
			return (check);
		str++;
	}
	return (result * sign);
}
