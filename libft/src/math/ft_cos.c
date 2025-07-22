/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:30:17 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the cosine of a value using its Taylor series expansion.
 *
 * @param x (double) : The angle in radians for which to compute the cosine.
 *
 * @return (double) : The cosine of the input angle x.
 */
double	ft_cos(double x)
{
	double	result;
	double	term;
	int		n;

	result = 1;
	term = 1;
	n = 1;
	while (ft_abs(term) > 0.000001)
	{
		term *= -x * x / (2 * n * (2 * n - 1));
		result += term;
		n++;
	}
	return (result);
}
