/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterpow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the value of `nb` raised to the power of `power` iteratively.
 *
 * @param nb (int) : The base value.
 * @param power (int) : The exponent value.
 *
 * @return (int) : The result of `nb` raised to the power of `power`.
 */
int	ft_iterpow(int nb, int power)
{
	int	result;
	int	i;

	result = 1;
	i = 1;
	if (power < 0)
		return (0);
	if (power == 0 && nb == 0)
		return (1);
	while (power >= i)
	{
		result = result * nb;
		i++;
	}
	return (result);
}
