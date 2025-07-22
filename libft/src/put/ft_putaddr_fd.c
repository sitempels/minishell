/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:23:10 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/29 06:41:42 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Prints the address of a pointer in hexadecimal fmt
 *	to a file descriptor
 *
 * @param ptr (void *) : pointer whose address is to be printed
 * @param fmt (char) : fmt specifier ('x' or 'X')
 * @param fd (int) : file descriptor where the address will be printed
 *
 * @return (int) : total number of characters printed
 */
int	ft_putaddr_fd(void *ptr, char fmt, int fd)
{
	unsigned long	addr;
	int				len;

	addr = (unsigned long)ptr;
	len = ft_putstr_fd("0x", fd);
	if (addr == 0)
		len += ft_putchar_fd('0', fd);
	else
		len += ft_puthex_fd(addr, fmt, fd);
	return (len);
}
