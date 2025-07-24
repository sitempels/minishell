/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:44:54 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Returns the base-2 logarithm of x (log2(x)).
 *
 * @param x The number to calculate the log2 of.
 *
 * @return The base-2 logarithm of x.
 */
double	ft_log2(double x)
{
	double	prox;
	double	res;
	int		i;

	if (x <= 0)
		return (0.0);
	prox = x;
	res = 0.0;
	i = 0;
	while (i < 100)
	{
		res = prox - 1;
		prox *= (1 - res);
		i++;
	}
	return (res);
}
