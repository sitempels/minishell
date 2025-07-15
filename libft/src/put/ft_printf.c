/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:17:16 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:37:09 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Handles a single fmt specifier and prints the corresponding value
 *
 * @param specifier (char) : fmt character (e.g. 's', 'd', 'x', etc.)
 * @param args (va_list) : variadic argument list
 *
 * @return (int) : number of characters printed
 */
static int	handle_specifier(char specifier, va_list args)
{
	if (specifier == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (specifier == 'x' || specifier == 'X')
		return (ft_puthex(va_arg(args, unsigned int), specifier));
	else if (specifier == '%')
		return (ft_putchar('%'));
	else
		return (0);
}

/**
 * @brief Custom printf that prints fmtted output to stdout
 *
 * @param fmt (const char *) : fmt string containing specifiers
 *
 * @return (int) : total number of characters written
 */
int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(args, fmt);
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			i++;
			len += handle_specifier(fmt[i], args);
		}
		else
			len += ft_putchar(fmt[i]);
		i++;
	}
	va_end(args);
	return (len);
}
