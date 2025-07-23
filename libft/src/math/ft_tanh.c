/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tanh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:30:17 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the hyperbolic tangent of a number.
 *
 * @param x (double) : Input value for which to compute the hyperbol tangent
 *
 * @return (double) : The hyperbolic tangent of the input value.
 */
double	ft_tanh(double x)
{
	return (ft_sinh(x) / ft_cosh(x));
}
