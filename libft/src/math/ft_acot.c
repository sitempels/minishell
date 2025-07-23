/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:38:45 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:36:29 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Calculates the inverse cotangent (arccotangent) of a value.
 *
 * @param x The value for which we want to calculate the inverse cotangent.
 *
 * @return The inverse cotangent in radians.
 */
double	ft_acot(double x)
{
	return (ft_atan(1 / x));
}
