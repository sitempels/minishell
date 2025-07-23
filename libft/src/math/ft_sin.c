/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:30:17 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the sine of a number.
 *
 * @param x (double) : The angle in radians for which to compute the sine.
 *
 * @return (double) : The sine of the input angle.
 */
double	ft_sin(double x)
{
	double	result;
	double	term;
	int		n;

	result = x;
	term = x;
	n = 1;
	while (ft_abs(term) > 0.000001)
	{
		term *= -x * x / (2 * n * (2 * n + 1));
		result += term;
		n++;
	}
	return (result);
}
