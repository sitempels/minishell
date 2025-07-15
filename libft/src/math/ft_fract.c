/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fract.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:42:55 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Returns the fractional part of x (x - floor(x)).
 *
 * @param x The number to get the fractional part of.
 *
 * @return The fractional part of x.
 */
double	ft_fract(double x)
{
	int	int_part;

	int_part = (int)x;
	return (x - (double)int_part);
}
