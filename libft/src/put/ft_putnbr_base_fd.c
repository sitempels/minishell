/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/29 06:42:18 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Prints an integer in a specified base to the specified fd.
 *
 * @param n (int) : The number to be printed.
 * @param base (int) : The base for the number
 * @param fd (int) : The file descriptor to print the number to.
 *
 * @return (int) : The total number of characters printed.
 */
int	ft_putnbr_base_fd(int n, int base, int fd)
{
	char	*digits;
	int		len;

	len = 0;
	digits = "0123456789ABCDEF";
	if (n < 0 && base == 10)
	{
		len += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= base)
		len += ft_putnbr_base_fd(n / base, base, fd);
	len += ft_putchar_fd(digits[n % base], fd);
	return (len);
}
