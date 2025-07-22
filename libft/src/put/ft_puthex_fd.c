/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:17:16 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/29 06:42:05 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Prints an unsigned integer in hexadecimal format to the specified fd.
 *
 * @param n (unsigned int) : The number to be printed in hexadecimal.
 * @param fmt (char) : Format specifier ('x' for lowercase, 'X' for uppercase).
 * @param fd (int) : The file descriptor where the number will be printed.
 *
 * @return (int) : The total number of characters printed.
 */
int	ft_puthex_fd(unsigned int n, char fmt, int fd)
{
	const char	*hex;
	int			len;

	hex = ft_gethex(fmt);
	len = 0;
	if (n == 0)
		return (ft_putchar_fd('0', fd));
	while (n > 0)
	{
		ft_putchar_fd(hex[n % 16], fd);
		n /= 16;
		len++;
	}
	return (len);
}
