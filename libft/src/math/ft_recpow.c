/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recpow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:36:26 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the power of a number using recursion.
 *
 * @param nb (int) : The base number.
 * @param power (int) : The exponent.
 *
 * @return (int) : The result of `nb` raised to the power of `power`,
 * or 0 if `power` is negative.
 */
int	ft_recpow(int nb, int power)
{
	if ((power == 0 && nb == 0) || power == 0)
		return (1);
	if (power < 0)
		return (0);
	if (power == 1)
		return (nb);
	return (nb * ft_recpow(nb, power - 1));
}
