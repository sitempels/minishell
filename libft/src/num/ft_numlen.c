/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:51:46 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/12 23:29:53 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

/**
 * @brief Calculate the number of digits in a number for a given base.
 *
 * @param num (int) : The number to be evaluated.
 * @param base (int) : The base for conversion (usually 10 for decimal).
 *
 * @return (int) : The number of digits in the number.
 */
int	ft_numlen(int num, int base)
{
	int	len;

	len = 1;
	if (num < 0)
	{
		num = -num;
		len++;
	}
	while (num >= base)
	{
		num /= base;
		len++;
	}
	return (len);
}
