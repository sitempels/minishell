/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:12:22 by sjacquet          #+#    #+#             */
/*   Updated: 2025/07/24 16:15:11 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Prints a long long integer to the standard output.
 *
 * @param num (long long) : The number to be printed.
 *
 * @return (int) : The total number of characters printed.
 */
int	ft_putnbr(long long num)
{
	int		len;
	char	digit;

	len = 0;
	if (num == -9223372036854775807LL - 1)
		return (ft_putstr("-9223372036854775808"));
	if (num < 0)
	{
		len += ft_putchar('-');
		num *= -1;
	}
	if (num >= 10)
		len += ft_putnbr(num / 10);
	digit = (num % 10) + '0';
	len += ft_putchar(digit);
	return (len);
}
