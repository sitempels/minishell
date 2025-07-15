/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the power of a base raised to an exponent.
 *
 * @param base (unsigned long) : The base value.
 * @param exp (unsigned int) : The exponent.
 *
 * @return (unsigned long) : The result of `base` raised to the power of `exp`.
 */
unsigned long	ft_pow(unsigned long base, unsigned int exp)
{
	unsigned long	result;

	result = 1;
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	return (result);
}
