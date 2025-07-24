/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fact.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the factorial of a non-negative integer `n`.
 *
 * @param n (int) : The integer whose factorial is to be computed.
 *
 * @return (long) : The factorial of `n`, or 1 if `n` is 0.
 */
long	ft_fact(int n)
{
	long	result;

	if (n == 0)
		return (1);
	result = 1;
	while (n > 1)
	{
		result *= n;
		n--;
	}
	return (result);
}
