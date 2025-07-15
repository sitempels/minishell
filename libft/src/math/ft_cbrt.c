/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cbrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:48:14 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Returns the cube root of x (x^(1/3)).
 *
 * @param x The number to take the cube root of.
 *
 * @return The cube root of x.
 */
double	ft_cbrt(double x)
{
	double	epsilon;
	double	guess;
	double	result;

	if (x < 0)
		return (-ft_cbrt(-x));
	guess = x / 3.0;
	epsilon = 0.00001;
	while (1)
	{
		result = (2.0 * guess + (x / (guess * guess))) / 3.0;
		if (result - guess < epsilon && result - guess > -epsilon)
			break ;
		guess = result;
	}
	return (result);
}
