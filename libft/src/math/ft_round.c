/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:43:48 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Returns the integer closest to x, rounding half away from zero.
 *
 * @param x The number to round.
 *
 * @return The rounded integer.
 */
int	ft_round(double x)
{
	int		int_part;
	double	frac_part;

	int_part = (int)x;
	frac_part = x - int_part;
	if (frac_part >= 0.5)
		return (int_part + 1);
	else if (frac_part <= -0.5)
		return (int_part - 1);
	return (int_part);
}
