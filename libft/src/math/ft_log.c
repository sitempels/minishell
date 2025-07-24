/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:30:17 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the natural logarithm of a number.
 *
 * @param x (double) : The number to compute the natural logarithm for.
 *
 * @return (double) : The natural logarithm of the input number, or
 *	-1 if the input is less than or equal to 0.
 */
double	ft_log(double x)
{
	double	result;
	double	term;
	double	y;
	int		n;

	if (x <= 0)
		return (-1);
	y = (x - 1) / (x + 1);
	result = 0;
	term = y;
	n = 1;
	while (ft_abs(term) > 0.000001)
	{
		result += term / n;
		term *= y * y;
		n += 2;
	}
	return (2 * result);
}
