/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:00:00 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Calculates the secant of the angle.
 *
 * @param x The angle in radians.
 *
 * @return The secant of the angle.
 */
double	ft_sec(double x)
{
	if (ft_cos(x) == 0)
		return (0);
	return (1 / ft_cos(x));
}
