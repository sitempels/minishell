/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ceil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:42:10 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Returns the smallest integer greater than or equal to x.
 *
 * @param x The number to ceil.
 *
 * @return The smallest integer greater than or equal to x.
 */
int	ft_ceil(double x)
{
	int	int_part;

	int_part = (int)x;
	if (x > 0 && x != int_part)
		return (int_part + 1);
	return (int_part);
}
