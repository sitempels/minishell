/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atan2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:30:17 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the arctangent of the quotient of two values & quadrant.
 *
 * @param y (double) : The numerator value.
 * @param x (double) : The denominator value.
 *
 * @return (double) : The arctangent of y/x, in radians considering the quadrant
 */
double	ft_atan2(double y, double x)
{
	double	result;

	if (x == 0)
	{
		if (y > 0)
			result = 1.570796326794897;
		else if (y < 0)
			result = -1.570796326794897;
		else
			result = 0;
	}
	else
	{
		result = ft_atan(y / ft_sqrt(x * x + y * y));
		if (x < 0)
			result += 3.14159265358979;
	}
	return (result);
}
