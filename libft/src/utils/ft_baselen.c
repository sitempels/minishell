/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baselen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:23:10 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:04:10 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Returns the number of digits of `nbr` in a given base length.
 *
 * @param nbr (unsigned long) : The number to evaluate.
 * @param base_len (int) : The base length (e.g., 2 for binary, 16 for hex).
 *
 * @return (int) : Number of digits needed to represent `nbr` in that base.
 */
int	ft_baselen(unsigned long nbr, int base_len)
{
	int	len;

	len = 1;
	while (nbr >= (unsigned long)base_len)
	{
		nbr /= base_len;
		len++;
	}
	return (len);
}
