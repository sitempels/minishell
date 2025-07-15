/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:00:00 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Calculates the cotangent of the angle.
 *
 * @param x The angle in radians.
 *
 * @return The cotangent of the angle.
 */
double	ft_cot(double x)
{
	if (x == 0)
		return (0);
	return (1 / ft_tan(x));
}
