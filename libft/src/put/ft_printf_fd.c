/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:17:16 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/10 21:40:14 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Handles a single fmt specifier and prints the corresponding value
 *
 * @param specifier (char) : fmt character (e.g. 's', 'd', 'x', etc.)
 * @param args (va_list) : variadic argument list
 * @param fd (int) : output file descriptor
 *
 * @return (int) : number of characters printed
 */
static int	handle_specifier_fd(char specifier, va_list args, int fd)
{
	if (specifier == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (specifier == 'x' || specifier == 'X')
		return (ft_puthex_fd(va_arg(args, unsigned int), specifier, fd));
	else if (specifier == '%')
		return (ft_putchar_fd('%', fd));
	else
		return (0);
}

/**
 * @brief Custom printf that outputs fmtted text to a file descriptor
 *
 * @param fd (int) : target file descriptor
 * @param fmt (const char *) : fmt string containing specifiers
 *
 * @return (int) : total number of characters written
 */
int	ft_printf_fd(int fd, const char *fmt, ...)
{
	int		printed;
	va_list	args;
	int		len;

	len = 0;
	printed = 0;
	va_start(args, fmt);
	while (fmt[len])
	{
		if (fmt[len] == '%' && fmt[len + 1])
		{
			len++;
			printed += handle_specifier_fd(fmt[len], args, fd);
		}
		else
			printed += ft_putchar_fd(fmt[len], fd);
		len++;
	}
	va_end(args);
	return (printed);
}
