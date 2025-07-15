/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterfact.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the factorial of a non-negative integer `nb` iteratively.
 *
 * @param nb (int) : The integer whose factorial is to be computed.
 *
 * @return (int) : The factorial of `nb`, or 0 if `nb` is negative.
 */
int	ft_iterfact(int nb)
{
	int	i;
	int	result;

	i = 1;
	result = 1;
	if (nb < 0)
		return (0);
	while (++i <= nb)
		result *= i;
	return (result);
}
