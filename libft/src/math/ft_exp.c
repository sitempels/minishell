/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:17:16 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the value of `x` raised to the power of `n` (x^n).
 *
 * @param x (double) : The base value.
 * @param n (int) : The exponent value.
 *
 * @return (double) : The result of `x` raised to the power of `n` (x^n).
 */
double	ft_exp(double x, int n)
{
	double	result;
	int		i;

	result = 1;
	if (n == 0)
		return (1);
	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			result *= x;
			i++;
		}
	}
	else
	{
		while (i < -n)
		{
			result *= x;
			i++;
		}
		result = 1 / result;
	}
	return (result);
}
