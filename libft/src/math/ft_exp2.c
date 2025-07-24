/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:49:20 by kerberos          #+#    #+#             */
/*   Updated: 2025/07/22 13:49:55 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Returns 2 raised to the power of x (exp2(x)).
 *
 * @param x The exponent.
 *
 * @return 2 raised to the power of x.
 */
double	ft_exp2(double x)
{
	double	result;
	int		i;

	i = 0;
	if (x == 0)
		return (1.0);
	result = 1.0;
	while (i < x)
	{
		result *= 2;
		i++;
	}
	return (result);
}
