/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:32:47 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/10 21:05:31 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

/**
 * @brief Converts a string to an integer.
 *
 * @param str (const char *) : The string to be converted.
 *
 * @return (int) : The converted integer value.
 */
int	ft_atoi(const char *str)
{
	long	result;
	int		check;
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
		check = ft_isintflow(result, sign);
		if (check != 1)
			return (check);
		str++;
	}
	return (result * sign);
}
