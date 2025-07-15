/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:02:07 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the square root of a number using the Babylonian method.
 *
 * @param n (double) : The number to compute the square root of.
 *
 * @return (double) : The square root of `n`, or -1 if `n` is negative.
 */
double	ft_sqrt(double n)
{
	double	x;
	double	y;

	if (n < 0)
		return (-1);
	x = n;
	y = (x + n / x) / 2;
	while (x - y > 0.000001)
	{
		x = y;
		y = (x + n / x) / 2;
	}
	return (y);
}
