/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acsc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:38:12 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:36:22 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Calculates the inverse cosecant (arccosecant) of a value.
 *
 * @param x The value for which we want to calculate the inverse cosecant.
 *
 * @return The inverse cosecant in radians.
 */
double	ft_acsc(double x)
{
	if (x < 1 && x > -1)
		return (0);
	return (ft_asin(1 / x));
}
