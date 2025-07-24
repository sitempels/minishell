/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:17:16 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/29 06:42:07 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Prints an unsigned integer in hexadecimal format to the specified fd.
 *
 * @param n (unsigned int) : The number to be printed in hexadecimal.
 * @param fmt (char) : Format specifier ('x' for lowercase, 'X' for uppercase).
 *
 * @return (int) : The total number of characters printed.
 */
int	ft_puthex(unsigned int n, char fmt)
{
	const char	*hex;
	int			len;

	hex = ft_gethex(fmt);
	len = 0;
	if (n == 0)
		return (ft_putchar('0'));
	while (n > 0)
	{
		ft_putchar(hex[n % 16]);
		n /= 16;
		len++;
	}
	return (len);
}
