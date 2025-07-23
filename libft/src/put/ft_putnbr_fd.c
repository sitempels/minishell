/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:20:35 by sjacquet          #+#    #+#             */
/*   Updated: 2024/11/04 14:20:35 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Prints an integer to the specified file descriptor.
 *
 * @param n (int) : The number to be printed.
 * @param fd (int) : The file descriptor where the number will be printed.
 *
 * @return (int) : The total number of characters printed.
 */
int	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	int		len;

	len = 0;
	if (n == -2147483648)
		len += ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		len += ft_putchar_fd('-', fd);
		n = -n;
		len += ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		len += ft_putnbr_fd(n / 10, fd);
		len += ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		digit = n + '0';
		len += ft_putchar_fd(digit, fd);
	}
	return (len);
}
