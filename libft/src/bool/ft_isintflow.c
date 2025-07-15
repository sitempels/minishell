/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isintflow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:32:32 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 05:08:10 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

/**
 * @brief Check if the result overflows or underflows the int range.
 *
 * @param result (long) : The result to check.
 * @param sign (int) : The sign of the result.
 *
 * @return (int) : Returns INT_MAX if result is greater than INT_MAX,
 *                 INT_MIN if result is less than INT_MIN,
 *                 1 if the result is within the valid range.
 */
int	ft_isintflow(long result, int sign)
{
	if (sign == 1 && result > INT_MAX)
		return (INT_MAX);
	if (sign == -1 && result < (long)INT_MIN)
		return (INT_MIN);
	return (1);
}
