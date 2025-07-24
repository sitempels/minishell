/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:23:10 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/29 06:41:44 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Prints the address of a pointer in hexadecimal fmt to stdout
 *
 * @param ptr (void *) : pointer whose address is to be printed
 * @param fmt (char) : fmt specifier ('x' or 'X')
 *
 * @return (int) : total number of characters printed
 */
int	ft_putaddr(void *ptr, char fmt)
{
	unsigned long	addr;
	int				len;

	addr = (unsigned long)ptr;
	len = ft_putstr("0x");
	if (addr == 0)
		len += ft_putchar('0');
	else
		len += ft_puthex(addr, fmt);
	return (len);
}
